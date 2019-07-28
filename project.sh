#!/bin/bash

printf "Note: this script is supposed to run on Ubuntu-18.04\n"
printf "...\n"
sleep 4

printf "Student: Junchao Mei\n"
printf "Course: ECE-531 [Internet of Things] (Summer 2019)\n"
printf "Final Project: IoT-simulated Thermostat\n"
printf "...\n"
sleep 8

if [ ! -d "./buildroot-2019.02.3/" ]; then
printf "Start downloading VM archive\n"
printf "...\n"
sleep 2
wget --load-cookies /tmp/cookies.txt "https://docs.google.com/uc?export=download&confirm=$(wget --quiet --save-cookies /tmp/cookies.txt --keep-session-cookies --no-check-certificate 'https://docs.google.com/uc?export=download&id=1DDtxQjgtam6R9T6aApxJ502SW6XW2OWa' -O- | sed -rn 's/.*confirm=([0-9A-Za-z_]+).*/\1\n/p')&id=1DDtxQjgtam6R9T6aApxJ502SW6XW2OWa" -O buildroot-2019.02.3.tgz && rm -rf /tmp/cookies.txt
printf "Finish downloading VM archive\n"
printf "...\n"
sleep 2
printf "Start extracting VM archive\n"
printf "...\n"
tar -xzf buildroot-2019.02.3.tgz
printf "Finish extracting VM archive\n"
printf "...\n"
sleep 2
fi

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