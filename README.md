# Modbus Library for KALEJA Devices

!This Version is not ready to use!

This Library brings support for KALEJA Devices using MODBUS to the Arduino Environment. It lets you use all functionalities that you could have used with plain MODBUS commands, but you only have to call the functions and library does the rest.

All you need is a Hardware serial port on your controller to drive the RS485 Chip.

There are no additional libraries required that are not allready included into the Arduino IDE.

# Contents

- [How to install](#How-to-install)
- [Documentation](#documentation)
	- [How to setup a Serial Connection](#how-to-setup-a-serial-connection)
	- [How to setup a Motor Controller Object](#how-to-setup-a-motor-controller-object)
	- [Classes and Functions](#classes-and-functions)
		- [{Class} MODBUS_KALEJA](#{class}-modbus_kaleja)
			- [Class Functions](#class-functions)
		- [{Class} MControl](#{class}-mcontrol)
			- [Class Functions](#class-functions)
			- [Error Codes](#error-codes)
	- [Additional Information](#additional-information)

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

Next you have to setup a Serial Connection. This is done by creating an object of the class [MODBUS_KALEJA](# {Class} MODBUS_KALEJA) and feeding it the necessary parameters.
To start the Serial Connection you also have to call the begin() function of your MODBUS_KALEJA object.

```c
MODBUS_KALEJA bus1(Serial,1,1,2); 
```

## How to setup a Motor Controller Object


## Classes and Functions

### {Class} MODBUS_KALEJA

Class for setting up a Serial Connection

#### Input parameters

| Parameter | Type | Input/Example | Value | Description |
| --------- | ---- | ------------ | ----- | ----------- |
| Serial Port | HardwareSerial | Serial, Serial1, ... | - | Defines the Serial port that the RS485 Driver is connected to |
| Baudrate | uint8_t | 0/1 | 19200/38400 | Defines the Baudrate at which the RS485 net is running |
| Parity | uint8_t | 0/1 | Even/None | Defines the Parity used in the RS485 net |
| R/W-Pin | PIN | 0,1,2, ... | - | Defines the pin that the R/W Pin of the RS485 Driver is connected to |

#### Class Functions

| Function | Description | Returns |
| -------- | ----------- | ------- |
| begin() | Starts the Serial Connection | 0 -> Success, -1 -> Port already open |
| end() | Closes the Serial Connection | 0 -> Success, -1 -> Port was not open |

### {Class} MControl

Class for setting up a Motor Controller Object with its unique address.

#### Input parameters

| Parameter | Type | Input/Example | Description |
| --------- | ---- | ------------- | ----------- |
| Device Address | uint8_t | 0x01, 0x05, ... | Defines the Address of the MODBUS RTU device which is set by the DIP Switch |
| Bus | MODBUS_KALEJA | - | Asigns the Motor Controllor to the RS485 Net of a certain Serial Connection |

#### Class Functions

| Function | Input | Returns | Description |
| -------- | ----- | ------- | ----------- |
| EEPROM_SAVE | - | 0/-1 | Save MODBUS Settings to EEPROM |
| EEPROM_RELOAD | - | 0/-1 | Load MODBUS Settings from EEPROM |
| DEVICE_RESET | - | 0/-1 | Softreset Device |
| FACTORY_DEFAULTS | - | 0/-1 | Reload Factory Settings |
| -------- | ----- | ------- | ----------- |
| WATCHDOG_OFF | - | 0/-1 | Disable Modbus Watchdog |
| WATCHDOG_ON | uint16_t | 0/-1 | Enable Watchdog, Timer set to Time in ms(1-65535) |
| WATCHDOG_GET | - | int32_t | Get Watchdog Time in ms |
| -------- | ----- | ------- | ----------- |
| CURRENT_LIMIT_OFF | - | 0/-1 | Disable Current Limit |
| CURRENT_LIMIT_ON | uint16_t | 0/-1 | Enable Current Limit. Set Current Limit to Current in mA(1-4000) |
| CURRENT_LIMIT_GET | - | int32_t | Get Current Limit in mA|
| -------- | ----- | ------- | ----------- |
| START_RAMP_OFF | - | 0/-1 | Disable Start Ramp |
| START_RAMP_ON | uint16_t | 0/-1 | Enable Start Ramp. Set Ramp Time to Time in ms(1-4000) |
| START_RAMP_GET | - | int32_t | Get Start Ramp in ms |
| -------- | ----- | ------- | ----------- |
| STOP_RAMP_OFF | - | 0/-1 | Disable Stop Ramp |
| STOP_RAMP_ON | uint16_t | 0/-1 | Enable Stop Ramp. Set Ramp Time to Time in ms(1-4000) |
| STOP_RAMP_GET | - | int32_t | Get Stop Ramp in ms |
| -------- | ----- | ------- | ----------- |
| PWM_OFF | - | 0/-1 | Set Motor Speed to 0 |
| PWM_ON | uint16_t | 0/-1 | Set Motor Speed to pwm/10 in Percent(50-1000) |
| PWM_GET | - | int32_t | get Motor PWM Settings in 10*Percent |
| -------- | ----- | ------- | ----------- |
| CM_DELAY_OFF | - | 0/-1 | Disable current monitoring delay |
| CM_DELAY_ON | uint16_t | 0/-1 | Enable current monitoring delay. Set Time in ms(1-1000) |
| CM_DELAY_GET | - | int32_t | Get current monitoring delay in ms |
| -------- | ----- | ------- | ----------- |
| IXR_COMP_OFF | - | 0/-1 | Disable IxR Compensation |
| IXR_COMP_ON | - | 0/-1 | Enable IxR Compensation, Set Motor Internal Resistance to mOhm(1-4000) |
| IXR_COMP_GET | - | int32_t | Get Motor Internal Resistance in mOhm |
| -------- | ----- | ------- | ----------- |
| MOTOR_OFF | - | 0/-1 | Disable Motor |
| MOTOR_ON | uint16_t | 0/-1 | Enable Motor |
| MOTOR_GET | - | int32_t | Get Motor State |
| -------- | ----- | ------- | ----------- |
| DIR_SET | uint8_t | 0/-1 | Set Motor Direction 0-->Direction1 / 1-->Direction2 |
| DIR_GET | uint16_t | 0/-1 | Get Motor Direction Setting |
| -------- | ----- | ------- | ----------- |
| BRAKE_OFF | - | 0/-1 | Disable Motor Breaking |
| BRAKE_ON | - | 0/-1 | Enable Motor Breaking |
| BRAKE_GET | - | int32_t | Get Brake Settings |
| -------- | ----- | ------- | ----------- |
| OVERCURRENT_SET_SHUTOFF | - | 0/-1 | Set Behaviour to Overcurrent Shutoff |
| OVERCURRENT_SET_LIMIT | uint16_t | 0/-1 | Set Behaviour to Overcurrent Limiting |
| OVERCURRENT_GET | - | int16_t | get Overcurrent Behaviour |
| -------- | ----- | ------- | ----------- |
| PROD_NUMBER | - | int64_t | Retruns Product Number |
| HARDWARE_VERSION | - | int32_t | Returns Hardware Version |
| SOFTWARE_VERSION | - | int32_t | Returns Software Version |
| SERIAL_NUMBER | - | int64_t | Returns Serial Number |
| CURRENT | - | int32_t | Returns the current being drawn by the Motor right now(0-65535) |
| PWM | - | int32_t | Returns the pwm at which the motor is running right now |
| DIR | - | int16_t | Returns the direction in which the motor is running right now |
| TEMP | - | int32_t | Returns the Temperature of the Module |

#### Error Codes

## Additional Information

If you want more information on any of the functions or about the error codes, there is in depth information in the datasheet of each Motor controller.