#!/usr/bin/env bash
if [ ! -d bin ] ; then
	echo run this script in the libpynq directory
	exit 1
fi
cd bin
if [ ! -e cat-display -o ! -f boot-startup.sh -o ! -f student-startup.sh ] ; then
	echo cannot upgrade: files missing
	exit 1
fi
if [ -f upgraded-sdcard-image ] ; then
	echo already upgraded
	exit 1
fi
if [ -e cat-display ] ; then
	sudo cp cat-display /boot
	sudo chmod +x /boot/cat-display
fi
sudo cp boot-startup.sh /boot/startup.sh
if [ -f /home/student/startup.sh ] ; then
	echo not overwriting existing /home/student/startup.sh
else
	cp student-startup.sh /home/student/startup.sh
	# doesn't need to be executable
fi
touch upgraded-sdcard-image
