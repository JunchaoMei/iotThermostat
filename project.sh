#!/bin/bash

printf "Note: this script is supposed to run on Ubuntu-18.04\n"
printf "...\n"
sleep 4

printf "Student: Junchao Mei\n"
printf "Course: ECE-531 [Internet of Things] (Summer 2019)\n"
printf "Final Project: IoT-simulated Thermostat\n"
printf "...\n"
sleep 8

cat credentials.txt
printf "\n...\n"
sleep 8
printf "After login to VM, type \"thermostat --help\" to show help info\n"
printf "...\n"
sleep 8
printf "Thank you!\n"
printf "...\n"
sleep 2

printf "Booting VM\n"
printf "...\n"
sleep 2
cd buildroot-2019.02.3/
./qemu_versatile.sh