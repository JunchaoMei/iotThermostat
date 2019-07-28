/* Compilation Commands
[x86] gcc -o thermostat thermostat.c -fstack-protector-all
[arm] ${BUILDROOT_HOME}/output/host/usr/bin/arm-linux-gcc --sysroot=${BUILDROOT_HOME}/output/staging  thermostat.c -o thermostat
*/
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>

#define OK          0
#define INIT_ERR    1

void printHelp()
{
	printf("Student:  Junchao Mei\n");
	printf("Course:  ECE-531:Internet of Things   Summer2019\n");
	printf("Final Project:  IoT-simulated Thermostat\n");
	printf("Usage:  thermostat [OPTION]\n");
	printf("[OPTION] list:\n");
	printf("  -h  or --help      display this help info\n");
	printf("  install            (re)install the thermostat device, pre-req for the followings\n");
	printf("                         Notice: already installed on QEMU-ARM embedded system\n");
	printf("  on                 turn on the thermostat switch\n");
	printf("  off                turn off the thermostat switch\n");
	printf("  target <number>    set the target temperature of the thermostat as <number> in celsius\n");
	printf("  check {newest|recent|all}     check the thermostat log (stauses & temperatures)\n");
	printf("  uninstall          uninstall the thermostat device (root only)\n");
	printf("Notice: settings will take effect from next log entry (once per 5 minutes)\n");
	printf("Exit status:\n");
	printf(" 0      OK\n");
	printf(" 1      Initializing Error\n");
	printf(" others Requesting Error\n");
}

char parseArg(int argc, char **argv, char **input)
{
	if (strcmp(argv[1],"-h")==0 || strcmp(argv[1],"--help")==0)
	{
		return 'h';
	} else if (strcmp(argv[1],"install")==0)
	{
		return 'i';
	} else if (strcmp(argv[1],"on")==0)
	{
		return 'n';
	} else if (strcmp(argv[1],"off")==0)
	{
		return 'f';
	} else if (strcmp(argv[1],"uninstall")==0)
	{
		return 'u';
	} else if (strcmp(argv[1],"target")==0)
	{
		if (argc < 3 || strspn(argv[2],"0123456789.-") != strlen(argv[2]))
		{
			return 'e';
		} else
		{
			input[0] = argv[2];
			return 't';
		}
	} else if (strcmp(argv[1],"check")==0)
	{
		if (argc < 3 || (strcmp(argv[2],"newest")!=0 && strcmp(argv[2],"recent")!=0 && strcmp(argv[2],"all")!=0))
		{
			return 'e';
		} else
		{
			input[0] = argv[2];
			return 'c';
		}
	} else
	{
		return 'e';
	}
}

int main(int argc, char **argv)
{
	char *input[1] = {"(something)"};
	char operation = parseArg(argc, argv, input); //initialize input[]

	switch (operation)
	{
		case 'i':
			return system("S80thermostatd start");
		case 'n':
			return system("hw2 -u http://18.222.58.97/IoT/project/switch -p \"on\"");
		case 'f':
			return system("hw2 -u http://18.222.58.97/IoT/project/switch -p \"off\"");
		case 'u':
			return system("S80thermostatd stop");
		case 't':
		{
			char *part1 = "hw2 -u http://18.222.58.97/IoT/project/tempTarget -p \"";
			char *part2 = "\"";
			char *tcommand = (char *) malloc(strlen(part1) + strlen(input[0]) + strlen(part2));
			sprintf(tcommand, "%s%s%s", part1, input[0], part2);
			return system(tcommand);
		}
		case 'c':
		{
			char *part1 = "hw2 -u http://18.222.58.97/IoT/project/checkThermostat.php?timerange=";
			char *part2 = " -g";
			char *ccommand = (char *) malloc(strlen(part1) + strlen(input[0]) + strlen(part2));
			sprintf(ccommand, "%s%s%s", part1, input[0], part2);
			return system(ccommand);
		}
		case 'h':
			printHelp();
			break;
		case 'e':
		default:
			printf("inappropriate command!  Type \"thermostat -h\" to see help info\n");
			return INIT_ERR;
	}

    return OK;
}
