#include <SPI.h>

// SX1276 registerlar
#define REG_FRF_MSB 0x06
#define REG_FRF_MID 0x07
#define REG_FRF_LSB 0x08
#define REG_OPMODE 0x01

// LoRa frekans ayarı için
#define LORA_FREQUENCY 915000000


void writeRegister(byte address, byte value) {
  digitalWrite(SS, LOW);
  SPI.transfer(address | 0x80);
  SPI.transfer(value);
  digitalWrite(SS, HIGH);
}

void setup() {
  
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.setDataMode(SPI_MODE0);

  // frekans bandını ayarla
  byte msb = (LORA_FREQUENCY >> 16) & 0xFF;
  byte mid = (LORA_FREQUENCY >> 8) & 0xFF;
  byte lsb = LORA_FREQUENCY & 0xFF;
  writeRegister(REG_FRF_MSB, msb);
  writeRegister(REG_FRF_MID, mid);
  writeRegister(REG_FRF_LSB, lsb);

  // kanalı ayarla
  byte channel = 0;
  writeRegister(REG_OPMODE, channel << 4 | 0x80);
}

void loop() {
  
}
