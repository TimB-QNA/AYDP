AYDP
====

The Autonomous Yacht Development Platform project. A project to develop a fully autonomous sailing yacht which can safely navigate between pre-defined waypoints.

Setting up AYDP:

You will need:
  A model yacht
  A Raspberry PI and SDCard
  A USB wifi dongle (which works in access point mode) - or a PI3
  An MPU-9150 IMU board
  An AYDP Interface board (see the hardware directory)
  And a variety of wires, power supplies etc. to put them all together.

First install a copy of Raspbian to the PI by downloading the latest image from http://www.raspberrypi.org/downloads there are loads of examples of how to burn the image to an SD Card, but you'll end up with a command something like:

dd bs=32K if=2014-01-07-wheezy-raspbian.img  of=/dev/sdb

Next, boot and log into the pi, then expand the partitions on the SD Card and enable the SSH server at bootup. Ensure that your PI has internet connection over a wired network link and install your wifi dongle (wired internet helps when you need to download packages). With the PI still connected to the internet, turn it into a wifi access point by following the instructions at http://elinux.org/RPI-Wireless-Hotspot except that there is no need to set up IPTables for NAT (unless you want to augment AYDP with network devices, in which case, you're probably smart enough to work out that you'll probably need NAT for any sensible debugging). The next major installation is I2C. This is disabled by default, but can by enabled by following the tutorial at https://learn.adafruit.com/adafruits-raspberry-pi-lesson-4-gpio-setup/configuring-i2c except for the bits about python (because this project is written in C++).

To get the i2c functionality to work, comment any lines in /etc/modprobe.d/raspi-blacklist.conf. and ensure the following modules are in /etc/modules:

snd-bcm2835
i2c-bcm2708
i2c-dev

At present, however, you'll only be able to run the code as root. Given that this is an utterly hideous idea (for a number of security reasons), we need to enable user access to the parts we need for the code to run. To avoid this, you need to add your user to the i2c group thus:

useradd -g i2c pi

Install sshfs for development work...
apt-get install sshfs
add "pi" user to the fuse group.

For development work you will need to install the following packages:

apt-get install qt4-dev-tools
apt-get install libusb-1.0-0-dev
