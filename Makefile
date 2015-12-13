## ------------------------------------------------------------------------- ##
##                             ENVIRONMENT SETUP                             ##
## ------------------------------------------------------------------------- ##

# Location of the AVR toolchain (Be mindful of spaces).
AVRBIN_DIR = C:\PROGRA~2\Arduino\hardware\tools\avr\bin
AVRETC_DIR = C:\PROGRA~2\Arduino\hardware\tools\avr\etc

# The serial port number (Linux: /dev/ttyACM0, Windows: COMx).
SERIAL_PORT = COM3

## ------------------------------------------------------------------------- ##
##                               PROJECT SETUP                               ##
## ------------------------------------------------------------------------- ##

# Name of your project.
TARGET = test

# Project layout.
SRC_DIR = src
LIB_DIR = lib
BUILD_DIR = build

## ------------------------------------------------------------------------- ##
##                             PROGRAMMER SETUP                              ##
## ------------------------------------------------------------------------- ##

# Baud rate.
UPLOAD_SPEED = 57600

# Programmer protocol.
UPLOAD_PROTOCOL = arduino

# CPU Speed in hz.
CPU_FREQ = 16000000L

# Board type.
MCU = atmega328p

## ------------------------------------------------------------------------- ##
##                     BEYOND HERE LIES MAKEFILE SORCERY                     ##
## ------------------------------------------------------------------------- ##

# AVR Toolchain.
CC		=$(AVRBIN_DIR)/avr-gcc
CPP		=$(AVRBIN_DIR)/avr-g++
AR		=$(AVRBIN_DIR)/avr-ar
OBJCOPY	=$(AVRBIN_DIR)/avr-objcopy
SIZE	=$(AVRBIN_DIR)/avr-size
AVRDUDE	=$(AVRBIN_DIR)/avrdude

# Library source files.
CLIB_FILES	= $(wildcard $(LIB_DIR)/*.c)
CLIB_OBJS 	= $(patsubst $(LIB_DIR)/%.c, $(BUILD_DIR)/%.o, $(CLIB_FILES))

CPPLIB_FILES= $(wildcard $(LIB_DIR)/*.cpp)
CPPLIB_OBJS = $(patsubst $(LIB_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CPPLIB_FILES))

# Project source files.
C_FILES		= $(wildcard $(SRC_DIR)/*.c)
C_OBJS		= $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_FILES))

CPP_FILES	= $(wildcard $(SRC_DIR)/*.cpp)
CPP_OBJS	= $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CPP_FILES))

# Compiler flags.
LDFLAGS		= -Wl,--gc-sections -Wl,-s -Wl,-static
OPT_FLAGS	= -Os -g
CFLAGS		= $(OPT_FLAGS) -ffunction-sections -fdata-sections -mmcu=$(MCU) -DF_CPU=$(CPU_FREQ) -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=10606 -I$(SRC_DIR) -I$(LIB_DIR)
CPPFLAGS	= -fno-exceptions $(CFLAGS)

# Build targets.
all: build $(BUILD_DIR)/$(TARGET)

$(C_OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(CPP_OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CPP) -c $(CPPFLAGS) $< -o $@

$(CLIB_OBJS): $(BUILD_DIR)/%.o: $(LIB_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(CPPLIB_OBJS): $(BUILD_DIR)/%.o: $(LIB_DIR)/%.cpp
	$(CPP) -c $(CPPFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(C_OBJS) $(CPP_OBJS) $(CLIB_OBJS) $(CPPLIB_OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/$(TARGET): $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $< $@
	$(OBJCOPY) -O ihex -R .eeprom $< $@
	$(SIZE) $@

.PHONY: build
build: 
	mkdir -p build
	
.PHONY: upload
upload: $(BUILD_DIR)/$(TARGET)
	$(AVRDUDE) -C$(AVRETC_DIR)/avrdude.conf -v -v -p$(MCU) -c$(UPLOAD_PROTOCOL) -P$(SERIAL_PORT) -b$(UPLOAD_SPEED) -D -Uflash:w:$(BUILD_DIR)/$(TARGET):i

.PHONY: clean
clean:
	rm build/*
