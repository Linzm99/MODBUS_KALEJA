//Header File for MODBUS_KALEJA
//
//Library for controlling MODBUS related motorcontrollers from KALEJA
//
//Author: Jan Linzmaier
//Date: 01/24/2021

#ifndef __MODBUS_KALEJA__
#define __MODBUS_KALEJA__

#include <stdint.h>
#include <HardwareSerial.h>
#include <Arduino.h>

//Variables:



//Classes:
class MODBUS_KALEJA{
  private:
    uint8_t baudrate;
    uint8_t parity;
    
    
    
  public:
    
    MODBUS_KALEJA(HardwareSerial& refSer, uint8_t baud, uint8_t par, uint8_t pin):SerPort(refSer), baudrate(baud), parity(par), EnPin(pin){};
    HardwareSerial& SerPort;
    uint8_t EnPin;
    int8_t begin();
    int8_t end();
    bool serialStarted;
    
};




class MControl{
  private:
    uint8_t address;
    int64_t transcieve(uint8_t RW, uint16_t addr, uint16_t data);
    MODBUS_KALEJA bus;
    
  public:
    MControl(uint8_t device_address, MODBUS_KALEJA Ser): address(device_address), bus(Ser){};

    //System Control:
    int8_t EEPROM_SAVE(void); //Save Settings to EEPROM
    int8_t EEPROM_RELOAD(void); //Load Settings from EEPROM
    int8_t DEVICE_RESET(void); //SoftReset Device
    int8_t FACTORY_DEFAULTS(void); //Reload Factory Settings

    //MODBUS Watchog:
    int8_t WATCHDOG_OFF(void); //Disable Modbus Watchdog
    int8_t WATCHDOG_ON(uint16_t ms); //Enable Watchdog, Timer set to Time in ms(1-65535)
    int32_t WATCHDOG_GET(void); //get Watchdog Time in ms

    //Current:    
    int8_t CURRENT_LIMIT_OFF(void); //Disable Current Limit
    int8_t CURRENT_LIMIT_ON(uint16_t mA); //Enable Current Limit. Set Current Limit to Current in mA(1-4000)
    int32_t CURRENT_LIMIT_GET(void); //Get Current Limit in mA

    //Start Ramp:
    int8_t START_RAMP_OFF(void); //Disable Start Ramp
    int8_t START_RAMP_ON(uint16_t ms); //Enable Start Ramp. Set Ramp Time to Time in ms(1-4000)
    int32_t START_RAMP_GET(void); //Get Start Ramp in ms

    //Start Ramp:
    int8_t STOP_RAMP_OFF(void); //Disable Stop Ramp
    int8_t STOP_RAMP_ON(uint16_t ms); //Enable Stop Ramp. Set Ramp Time to Time in ms(1-4000)
    int32_t STOP_RAMP_GET(void); //Get Stop Ramp in ms

    //Rotational Speed(PWM):
    int8_t PWM_OFF(void); //Set Motor Speed to 0
    int8_t PWM_ON(uint16_t pwm); //Set Motor Speed to pwm/10 in Percent(50-1000)
    int32_t PWM_GET(void); //get Motor PWM Settings in 10*Percent

    //Current monitoring delay
    int8_t CM_DELAY_OFF(void); //Disable current monitoring delay
    int8_t CM_DELAY_ON(uint16_t ms); //Enable current monitoring delay. Set Time in ms(1-1000)
    int32_t CM_DELAY_GET(void); //Get current monitoring delay in ms

    //Motor Internal Resistance for IxR Compensation
    int8_t IXR_COMP_OFF(void); //Disable IxR Compensation
    int8_t IXR_COMP_ON(uint16_t mOhm); //Enable IxR Compensation, Set Motor Internal Resistance to mOhm(1-4000)
    int32_t IXR_COMP_GET(void); //Get Motor Internal Resistance in mOhm

    //Motor Control:
    int8_t MOTOR_OFF(void); //Disable Motor
    int8_t MOTOR_ON(void); //Enable Motor
    int16_t MOTOR_GET(void); //Get Motor State

    //Motor Direction:
    int8_t DIR_SET(uint8_t dir); //Set Motor Direction 0-->Direction1 / 1-->Direction2
    int16_t DIR_GET(void); //get Motor Direction Setting

    //Brake Selection:
    int8_t BRAKE_OFF(void); //Disable Motor Breaking
    int8_t BRAKE_ON(void); //Enable Motor Breaking
    int16_t BRAKE_GET(void); //get Brake Settings

    //Overcurrent Settings
    int8_t OVERCURRENT_SET_SHUTOFF(void); //Set Behaviour to Overcurrent Shutoff(0)
    int8_t OVERCURRENT_SET_LIMIT(void); //Set Behaviour to Overcurrent Limiting(1)
    int16_t OVERCURRENT_GET(void); //get Overcurrent Behaviour

    //READ_ONLY:
    
    //Product Number:
    int64_t PROD_NUMBER(void); //Returns Product Number

    //Harware Version:
    int32_t HARDWARE_VERSION(void); //Returns Hardware Version

    //Software Version:
    int32_t SOFTWARE_VERSION(void); //Returns Software Version

    //Serial number:
    int64_t SERIAL_NUMBER(void); //Returns Serial Number

    //Current:
    int32_t CURRENT(void); //Returns the current being drawn by the Motor right now(0-65535)

    //PWM:
    int32_t PWM(void); //Returns the pwm at which the motor is running right now

    //Direction:
    int16_t DIR(void); //Returns the direction in which the motor is running right now
        
    //Module Temperature:
    int32_t TEMP(void); //Returns the Temperature of the Module
    
    
    
};


#endif
