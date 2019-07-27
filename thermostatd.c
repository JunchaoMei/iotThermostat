/* Compilation Command:
[x86] gcc -o thermostatd thermostatd.c -fstack-protector-all
[arm] ${BUILDROOT_HOME}/output/host/usr/bin/arm-linux-gcc --sysroot=${BUILDROOT_HOME}/output/staging  -c thermostatd.c -o thermostatd
   Check newest system log:
[x86] tail /var/log/syslog
[arm] tail /var/log/messages
*/
#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <signal.h>
#include <stdint.h>

#define OK           0
#define ERR_FORK     28
#define ERR_SETSID   58
#define ERR_CHDIR    37
#define DAEMON_NAME	"thermostatd"

static void _signal_handler(const int signal)
{
	switch(signal)
	{
		case SIGHUP:
			break;
		case SIGTERM:
			syslog(LOG_INFO, "received SIGTERM, exiting.");
			closelog();
			exit(OK);
			break;
		default:
			syslog(LOG_INFO, "received unhandled signal");
	}
}

static void _do_work(void)
{
	for (int i = 1; true; ++i)
	{
		char *geturl = "/home/junchao/Dev/IoT/iotThermostat/hw2 -u http://18.222.58.97/IoT/project/runThermostat5min.php?entryid=";
		char *ending = " -g";
		char *command = (char *) malloc(strlen(geturl) + strlen(ending) + 6);
		sprintf(command, "%s%d%s", geturl, i, ending);
		system(command);
		//syslog(LOG_INFO, "%s\n", command);
		sleep(300);
	}
}

int main(void)
{	
	openlog(DAEMON_NAME, LOG_PID | LOG_NDELAY | LOG_NOWAIT, LOG_DAEMON);
	syslog(LOG_INFO, "starting thermostatd");

	pid_t pid = fork();

	if (pid < 0)
	{
		syslog(LOG_ERR, "Forking Error! '%s'\n", strerror_r(errno,malloc(1024),1024));
		exit(ERR_FORK);
	}

	if (pid > 0)
	{
		exit(OK);
	}

	if (setsid() < -1)
	{
		syslog(LOG_ERR, "Error: not the leader of the session! '%s'\n", strerror_r(errno,malloc(1024),1024));
		exit(ERR_SETSID);
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	umask(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	if (chdir("/") < 0)
	{
		syslog(LOG_ERR, "Error: cannot change to / (root) '%s'\n", strerror_r(errno,malloc(1024),1024));
		exit(ERR_CHDIR);
	}

	signal(SIGTERM, _signal_handler);
	signal(SIGHUP, _signal_handler);

	_do_work();

	exit(OK);
}