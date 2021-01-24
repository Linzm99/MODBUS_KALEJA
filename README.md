# Modbus Library for KALEJA Devices

!This Version is not ready to use!

This is a Library brings support for KALEJA Devices using MODBUS to the Arduino Environment. It lets you use all functionalities that you could have used with plain MODBUS commands, but you only have to call the functions and library does the rest.

All you need is a Hardware serial port on your controller to drive the RS485 Chip.

There are no additional libraries required that are not allready included into the Arduino IDE.

# Contents

- [How to install](#How-to-install)
- [Documentation](#documentation)
	- [How to setup a Serial Connection](#how-to-setup-a-serial-connection)

# How to install

To install this library follow these steps:

- (If you already have the Arduino IDE install skip this step) Install the current upstream Arduino IDE at the 1.8 level or later. The current version is on the [Arduino website](https://www.arduino.cc/en/main/software).
- Download the latest version of this library by clicking on the green "Code" button and "Download ZIP" or by using this [link](https://github.com/Linzm99/MODBUS_KALEJA/archive/main.zip).
- Open your Arduino IDE. Go to Sketch>Include Library>Add .ZIP Library. Navigate to the MODBUS_KALEJA-main.zip file's location and select it.
- The Library should now be included.

# Documentation

## How to setup a Serial Connection

This is a short example on how to use the library. To see the actual function descriptions click [here]
To use this library you first have to include the library into your Arduino project.

```c
#include "MODBUS_KALEJA.h"
```

Next you have to setup a Serial Connection. This is done by creating an object of the class [MODBUS_KALEJA] and feeding it the necessary parameters.
To start the Serial Connection you also have to call the begin() function of your MODBUS_KALEJA object.

```c
MODBUS_KALEJA bus1(Serial,1,1,2); 
```

## How to setup a Motor Controller Object


## Classes and Functions

### {Class} MODBUS_KALEJA

Class for setting up a Serial Connection

#### Input parameters

| Parameter | Type |Input | Value |
| --------- | ---- | ---- | ----- |
| Serial Port | HardwareSerial | Serial, Serial1, ... | - |
