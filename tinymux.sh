#!/bin/bash

echo "Testing mux values required by dapm with tinymix"
echo "Starting ADB"

adb root

if [ -n "$(lsusb | grep '04e8:6860')" ]
then
	echo "Device is Connected via Usb in System Mode!"
	echo "$(lsusb | grep '04e8:6860')"
	echo "Ensuring System is ready for operations"
	adb "wait-for-device";
	echo "System is Ready"
else
    echo "Error! Please connect device in system mode and run again!"
    exit 1
fi

echo "___________________________________"
echo "Testing IIR1 INP1 MUX"
echo " "
echo "IIR1 INP1 MUX connection to RX1"
echo "Command: tinymix 485 11"
adb shell tinymix 485 11
echo " "
echo "IIR1 INP1 MUX connection reset to 0"
echo "Command: tinymix 485 0"
adb shell tinymix 485 0
echo "___________________________________"
echo " "

echo "Testing IIR2 INP1 MUX"
echo " "
echo "IIR2 INP1 MUX connection to RX2"
echo "Command: tinymix 481 12"
adb shell tinymix 481 12
echo " "
echo "IIR2 INP1 MUX connection reset to 0"
echo "Command: tinymix 481 0"
adb shell tinymix 481 0
echo "___________________________________"
echo " "

echo "Testing RX1 MIX1 INP1"
echo " "
echo "RX1 MIX1 INP1 connection to RX1"
echo "Command: tinymix 564 5"
adb shell tinymix 564 5
echo " "
echo "RX1 MIX1 INP1 connection to IIR1"
echo "Command: tinymix 564 3"
adb shell tinymix 564 3
echo " "
echo "RX1 MIX1 INP1 connection reset to 0"
echo "Command: tinymix 564 0"
adb shell tinymix 564 0
echo "___________________________________"
echo " "

echo "Testing RX2 MIX1 INP1"
echo " "
echo "RX2 MIX1 INP1 connection to RX2"
echo "Command: tinymix 561 6"
adb shell tinymix 561 6
echo " "
echo "RX2 MIX1 INP1 connection to IIR2"
echo "Command: tinymix 561 4"
adb shell tinymix 561 4
echo " "
echo "RX2 MIX1 INP1 connection reset to 0"
echo "Command: tinymix 561 0"
adb shell tinymix 561 0
echo "___________________________________"
echo " "

echo "Testing RX1 MIX1 INP2"
echo " "
echo "RX1 MIX1 INP2 connection to IIR1"
echo "Command: tinymix 563 3"
adb shell tinymix 563 3
echo " "
echo "RX1 MIX1 INP2 connection reset to 0"
echo "Command: tinymix 563 0"
adb shell tinymix 563 0
echo "___________________________________"
echo " "

echo "Testing RX2 MIX1 INP2"
echo " "
echo "RX2 MIX1 INP2 connection to IIR2"
echo "Command: tinymix 560 4"
adb shell tinymix 560 4
echo " "
echo "RX2 MIX1 INP2 connection reset to 0"
echo "Command: tinymix 560 0"
adb shell tinymix 560 0
echo "___________________________________"
echo " "

[ ! -d "/root/tinymux_tests" ] && mkdir "/root/tinymux_tests"
adb shell dmesg > /root/tinymux_tests/dmesg.log
echo "Finished!"
