#!/bin/bash

if [ $(id -u) -eq 0 ]; then
    sudo service ModemManager stop > /dev/null 2>&1
    sudo service NetworkManager stop > /dev/null 2>&1
    sudo ifconfig wlan0 down > /dev/null 2>&1
    sudo service wpa_supplicant stop > /dev/null 2>&1
    sudo ifconfig end0 down > /dev/null 2>&1
    sudo service avahi-daemon stop > /dev/null 2>&1
    sudo service networking stop > /dev/null 2>&1
    vcgencmd display_power 0 > /dev/null 2>&1
else
    echo "ERROR! Please run script as root"
fi
