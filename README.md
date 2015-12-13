Arduino in Pure C Template Project
==================================

Skeleton for an Arduino project (Based on deweerdt's skeleton project). 

* https://github.com/deweerdt/arduino-uno-project

Overview
========

This project contains sources from the Arduino IDE v1.6. 

How to
======

1. Checkout this repository:
	git clone https://github.com/mparuzel/ArduinoCTemplate.git
4. Edit the `Makefile` file to suit your environment
	There are two variables that you will need to edit:
	* `AVRBIN_DIR` and `AVRETC_DIR`: the installtion path of your AVR toolkit or 
	Arduino install (ie. C:\Program Files (x86)\Arduino\hardware\tools\avr).
	* `SERIAL_PORT`: The port where your Arduino is tethered to. On Windows this
	is most likely `COM3`, on Linux it can reside in `/dev/tty*`.
5. Add your files into the `./src` directory.
6. `make` and then `make upload`

Notes
=====

* This has only been tested with the Arduino Nano board.
* The Makefile supports three commands:
	* `all`: build and link the main binary
	* `upload`: upload the binary to the board
	* `clean`: remove the intermediary files
