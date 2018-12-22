#!/bin/bash

sudo apt-get update -y
echo -e $TEXT_YELLOW
echo 'APT update finished...'
echo -e $TEXT_RESET

sudo apt-get dist-upgrade -y
echo -e $TEXT_YELLOW
echo 'APT distributive upgrade finished...'
echo -e $TEXT_RESET

sudo apt-get upgrade -y
echo -e $TEXT_YELLOW
echo 'APT upgrade finished...'
echo -e $TEXT_RESET

sudo apt-add-repository ppa:webupd8team/java
echo -e $TEXT_YELLOW
echo 'Added Repository...'
echo -e $TEXT_RESET
sudo apt-get update -y
echo -e $TEXT_YELLOW
echo 'APT update finished...'
echo -e $TEXT_RESET
sudo apt-get install oracle-java8-installer
echo -e $TEXT_YELLOW
echo 'finished installing Java 8'
echo -e $TEXT_RESET

sudo apt install python3-pip
echo -e $TEXT_YELLOW
echo 'finished installing Python3'
echo -e $TEXT_RESET


sudo pip install feedparser
echo -e $TEXT_YELLOW
echo 'finished installing Feedparser'
echo -e $TEXT_RESET

sudo apt-get autoremove
echo -e $TEXT_YELLOW
echo 'APT auto remove finished...'
echo -e $TEXT_RESET
echo -e $TEXT_BLUE
echo 'Your device is ready for Battle'
echo -e $TEXT_RESET

if [ -f /var/run/reboot-required ]; then
    echo -e $TEXT_RED_B
    echo 'Reboot required!'
    echo -e $TEXT_RESET
fi
