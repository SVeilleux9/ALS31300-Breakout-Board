
#include <Wire.h>
#include "ALS31300.h"

int hall_mode = 0;

void setup()
{
  Wire.begin();
  Wire.setClock(100000);
  Serial.begin(115200);

  uint16_t error = write(96, 0x35, 0x2C413534);

  uint32_t eeprom;
  
  read(96, 0x02, eeprom);
  Serial.println(eeprom);
  delay(100);
  
  eeprom = 0x000801E0;
  error = write(96, 0x02, eeprom);
  delay(100);

  read(96, 0x02, eeprom);
  Serial.println(eeprom);
  delay(100);

  char a = bitRead(eeprom,20);
  char b = bitRead(eeprom,19);
  hall_mode |= a << 0;
  hall_mode |= b << 1;

  Serial.println(hall_mode);
}

byte val = 0;

void loop()
{
  readALS31300ADC_FullLoop(96);
  delay(500);
}

uint16_t write(int busAddress, uint8_t address, uint32_t value)
{
    // Write the address that is to be written to the device
    // and then the 4 bytes of data, MSB first
    Wire.beginTransmission(busAddress);
    Wire.write(address);
    Wire.write((byte)(value >> 24));
    Wire.write((byte)(value >> 16));
    Wire.write((byte)(value >> 8));
    Wire.write((byte)(value));    
    return Wire.endTransmission();
}

uint16_t read(int busAddress, uint8_t address, uint32_t& value)
{
    // Write the address that is to be read to the device
    Wire.beginTransmission(busAddress);
    Wire.write(address);
    int error = Wire.endTransmission(false);

    // if the device accepted the address,
    // request 4 bytes from the device
    // and then read them, MSB first

    Wire.requestFrom(busAddress, 4);
    value = Wire.read() << 24;
    value += Wire.read() << 16;
    value += Wire.read() << 8;
    value += Wire.read();

    return error;
}

long SignExtendBitfield(uint32_t data, int width)
{
    long x = (long)data;
    long mask = 1L << (width - 1);

    if (width < 32)
    {
        x = x & ((1 << width) - 1); // make sure the upper bits are zero
    }

    return (long)((x ^ mask) - mask);
}

void readALS31300ADC_FullLoop(int busAddress){
    uint32_t value0x27;

    // Read the register the I2C loop mode is in
    uint16_t error = read(busAddress, 0x27, value0x27);

    // I2C loop mode is in bits 2 and 3 so mask them out
    // and set them to the full loop mode
    value0x27 = (value0x27 & 0xFFFFFFF3) | (0x2 << 2);

    // Write the new values to the register the I2C loop mode is in
    error = write(busAddress, 0x27, value0x27);

    // Write the address that is going to be read from the ALS31300
    Wire.beginTransmission(busAddress);
    Wire.write(0x28);
    error = Wire.endTransmission(false);

    int x;
    int y;
    int z;

    // Start the read and request 8 bytes
    // which is the contents of register 0x28 and 0x29
    Wire.requestFrom(busAddress, 8);
    
    // Read the first 4 bytes which are the contents of register 0x28
    x = Wire.read() << 4;
    y = Wire.read() << 4;
    z = Wire.read() << 4;
    Wire.read();    // Temperature and flags not used

    // Read the next 4 bytes which are the contents of register 0x29
    Wire.read();    // Upper byte not used
    x |= Wire.read() & 0x0F;
    byte d = Wire.read();
    y |= (d >> 4) & 0x0F;
    z |= d & 0x0F;
    Wire.read();    // Temperature not used

    // Sign extend the 12th bit for x, y and z.
    x = SignExtendBitfield((uint32_t)x, 12);
    y = SignExtendBitfield((uint32_t)y, 12);
    z = SignExtendBitfield((uint32_t)z, 12);

    Serial.print("Magnetic field [z]: ");
    Serial.println(z);
}
