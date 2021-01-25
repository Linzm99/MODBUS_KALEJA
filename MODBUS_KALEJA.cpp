#include "MODBUS_KALEJA.h"

#define BAUD0 19200
#define BAUD1 38400
#define BAUD_INVALID -2

#define PARITY0 SERIAL_8E1
#define PARITY1 SERIAL_8N1
#define PARITY_INVALID -3

#define R 0x04
#define RH 0x03
#define W 0x06


#define ERR_FC 0x81
#define ERR_ADDR 0x82
#define ERR_COUNT 0x83
#define ERR_EXEC 0x84



uint16_t ModRTU_CRC(uint8_t *buf, uint8_t len)
{
  uint16_t crc = 0xFFFF;
  
  for (int pos = 0; pos < len; pos++) {
    crc ^= (uint16_t)*(buf+pos);          
  
    for (int i = 8; i != 0; i--) {    
      if ((crc & 0x0001) != 0) {      
        crc >>= 1;                    
        crc ^= 0xA001;
      }
      else                            
        crc >>= 1;                    
    }
  }
  return crc;  
}

int8_t MODBUS_KALEJA::begin(){
  if( getStat() == 1){
    return -1;
  }
  pinMode(EnPin,OUTPUT);
  uint32_t baud = 0;
  if(baudrate == 0){
    baud = BAUD0;
  }
  else if(baudrate == 1){
    baud = BAUD1;
  }
  else{
    return BAUD_INVALID;
  }
  if(parity == 0){
    SerPort.begin(baud,PARITY0);
  }
  else if(parity == 1){
    SerPort.begin(baud,PARITY1);
  }
  else{
    return PARITY_INVALID;
  }
  setStat(1);
  return 0;
}

uint8_t MODBUS_KALEJA::getStat(void){
  return serialStarted;
}

void MODBUS_KALEJA::setStat(uint8_t s){
  serialStarted = s;
  return;
}

int8_t MODBUS_KALEJA::end(){
  if(getStat() == 0){
    return -1;
  }
  SerPort.end();
  return 0;
}

int64_t MControl::transcieve(uint8_t RW, uint16_t addr, uint16_t data){
  uint8_t output[8] = {0};
  output[0] = address;
  output[1] = RW;
  output[2] = (uint8_t)(addr>>8);
  output[3] = (uint8_t)addr;
  output[4] = (uint8_t)(data>>8);
  output[5] = (uint8_t)data;
  uint16_t CRC = (uint16_t)ModRTU_CRC(output,6);
  output[6] = (uint8_t)CRC;
  output[7] = (uint8_t)(CRC>>8);
  while(bus.SerPort.available()){
    bus.SerPort.read();
  }
  digitalWrite(bus.EnPin, HIGH);
  for(int i = 0; i<8; i++){
    bus.SerPort.write(output[i]);
  }
  bus.SerPort.flush();
  delayMicroseconds(5);
  
  digitalWrite(bus.EnPin, LOW);
  delay(30);
  uint8_t input[12] = {0};
  uint8_t in_len = 0;
  for(int i = 0; bus.SerPort.available(); i++){
    input[i] = bus.SerPort.read();
    in_len++;
  }
  delayMicroseconds(5);
  
  CRC = (uint16_t)ModRTU_CRC(input,in_len-2);
  if(input[in_len-2] != (uint8_t)CRC || input[in_len-1] != (uint8_t)(CRC>>8)){
    return -2;
  }

  if(input[1] >= 0x81 && input[1] <= 0x84){
    return -input[1];
  }
  
  
  if(RW == W){
    if(input[1] == 0x86){
      return -0x86;
    }
    
    return 0;
  }
  else if(RW == RH || RW == R){
    uint8_t count = input[2];
    int64_t reply = 0;
    for(int i = 0; i < count; i++){
      reply |= (input[3+i]<<(8*(count-i-1)));
    }
    return reply;
  }

  return -1;
}


//
int8_t MControl::EEPROM_SAVE(void){
  return transcieve(W,0x0000,0x4B4C);
}

int8_t MControl::EEPROM_RELOAD(void){
  return transcieve(W,0x0000,0x4552);
}

int8_t MControl::DEVICE_RESET(void){
  return transcieve(W,0x0000,0x5253);
}

int8_t MControl::FACTORY_DEFAULTS(void){
  return transcieve(W,0x0000,0x4644);
}

int8_t MControl::WATCHDOG_OFF(void){
  return transcieve(W,0x0003,0x0000);
}

int8_t MControl::WATCHDOG_ON(uint16_t ms){
  return transcieve(W,0x0003,ms);
}

int32_t MControl::WATCHDOG_GET(void){
  return transcieve(RH,0x0003,0x0001);
}

int8_t MControl::CURRENT_LIMIT_OFF(void){
  return transcieve(W,0x000C,0x0000);
}

int8_t MControl::CURRENT_LIMIT_ON(uint16_t mA){
  return transcieve(W,0x000C,mA);
}

int32_t MControl::CURRENT_LIMIT_GET(void){
  return transcieve(RH,0x000C,0x0001);
}

int8_t MControl::START_RAMP_OFF(void){
  return transcieve(W,0x0012,0x0000);
}

int8_t MControl::START_RAMP_ON(uint16_t ms){
  return transcieve(W,0x0012,ms);
}

int32_t MControl::START_RAMP_GET(void){
  return transcieve(RH,0x0012,0x0001);
}

int8_t MControl::STOP_RAMP_OFF(void){
  return transcieve(W,0x0014,0x0000);
}

int8_t MControl::STOP_RAMP_ON(uint16_t ms){
  return transcieve(W,0x0014,ms);
}

int32_t MControl::STOP_RAMP_GET(void){
  return transcieve(RH,0x0014,0x0001);
}

int8_t MControl::PWM_OFF(void){
  return transcieve(W,0x0018,0x0000);
}

int8_t MControl::PWM_ON(uint16_t pwm){
  return transcieve(W,0x0018,pwm);
}

int32_t MControl::PWM_GET(void){
  return transcieve(RH,0x0018,0x0001);
}

int8_t MControl::CM_DELAY_OFF(void){
  return transcieve(W,0x001E,0x0000);
}

int8_t MControl::CM_DELAY_ON(uint16_t ms){
  return transcieve(W,0x001E,ms);
}

int32_t MControl::CM_DELAY_GET(void){
  return transcieve(RH,0x001E,0x0001);
}

int8_t MControl::IXR_COMP_OFF(void){
  return transcieve(W,0x0020,0x0000);
}

int8_t MControl::IXR_COMP_ON(uint16_t mOhm){
  return transcieve(W,0x0020,mOhm);
}

int32_t MControl::IXR_COMP_GET(void){
  return transcieve(RH,0x0020,0x0001);
}

int8_t MControl::DIR_LEFT_OFF(void){
  return transcieve(W,0x0050,0x0000);
}

int8_t MControl::DIR_LEFT_ON(void){
  return transcieve(W,0x0050,0x0001);
}

int8_t MControl::DIR_LEFT_GET(void){
  return transcieve(RH,0x0050,0x0001);
}

int8_t MControl::DIR_RIGHT_OFF(void){
  return transcieve(W,0x0051,0x0000);
}

int8_t MControl::DIR_RIGHT_ON(void){
  return transcieve(W,0x0051,0x0001);
}

int8_t MControl::DIR_RIGHT_GET(void){
  return transcieve(RH,0x0051,0x0001);
}

int8_t MControl::BRAKE_OFF(void){
  return transcieve(W,0x0055,0x0000);
}

int8_t MControl::BRAKE_ON(void){
  return transcieve(W,0x0055,0x0001);
}

int16_t MControl::BRAKE_GET(void){
  return transcieve(RH,0x0055,0x0001);
}

int8_t MControl::OVERCURRENT_SET_SHUTOFF(void){
  return transcieve(W,0x005B,0x0000);
}

int8_t MControl::OVERCURRENT_SET_LIMIT(void){
  return transcieve(W,0x005B,0x0001);
}

int16_t MControl::OVERCURRENT_GET(void){
  return transcieve(RH,0x005B,0x0001);
}

int64_t MControl::PROD_NUMBER(void){
  return transcieve(R,0x4000,0x0002);
}

int32_t MControl::HARDWARE_VERSION(void){
  return transcieve(R,0x4002,0x0001);
}

int32_t MControl::SOFTWARE_VERSION(void){
  return transcieve(R,0x4003,0x0001);
}

int64_t MControl::SERIAL_NUMBER(void){
  return transcieve(R,0x4004,0x0003);
}

int32_t MControl::CURRENT(void){
  return transcieve(R,0x4028,0x0001);
}

int32_t MControl::PWM(void){
  return transcieve(R,0x4029,0x0001);
}

int16_t MControl::DIR(void){
  return transcieve(R,0x402A,0x0001);
}

int32_t MControl::TEMP(void){
  return transcieve(R,0x402B,0x0001);
}
