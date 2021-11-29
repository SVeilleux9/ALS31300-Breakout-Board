#include "Arduino.h"
#include <Wire.h> 

struct Reg{
    const uint8_t 
        address,
        numBits,
        offset; 
};

struct FullRMA{
    int16_t x, y, z, temperature;
};

namespace RegMap{

    // Address, Length, Offset
    constexpr Reg
        // 0x02 address
        BW_Select           {0x02, 3, 21},
        Hall_Mode           {0x02, 2, 19},
        I2C_CRC_Enable      {0x02, 1, 18},
        Disable_Slave_ADC   {0x02, 1, 17},
        Slave_Address       {0x02, 7, 10},
        I2C_Threshold       {0x02, 1,  9},
        Channel_Z_Enable    {0x02, 1,  8},
        Channel_Y_Enable    {0x02, 1,  7},
        Channel_X_Enable    {0x02, 1,  6},
        NINT_Latch_Enable   {0x02, 1,  5},
        Customer_EEPROM1    {0x02, 1,  0},

        // 0x03 address
        Signed_NINT_Enable  {0x03, 1, 24},
        NINT_Mode           {0x03, 1, 23},
        NINT_EEPROM         {0x03, 1, 22},
        NINT_EEPROM_Status  {0x03, 1, 21},
        NINT_EEPROM_Enable  {0x03, 1, 20},
        Z_NINT_Enable       {0x03, 1, 19},
        Y_NINT_Enable       {0x03, 1, 18},
        X_NINT_Enable       {0x03, 1, 17},
        Z_NINT_Threshold    {0x03, 6, 12},
        Y_NINT_Threshold    {0x03, 6,  6},
        X_NINT_Threshold    {0x03, 6,  0},

        // 0x0D address
        Customer_EEPROM2    {0x0D, 26, 0},

        // 0x0E address
        Customer_EEPROM3    {0x0E, 26, 0},
        
        // 0x0F address
        Customer_EEPROM4    {0x0F, 26, 0},

        // 0x27 address
        Low_Power_Mode_Count_Max {0x27, 1, 23},
        I2C_Loop_Mode       {0x27, 1, 22},
        Sleep               {0x27, 1, 21},

        // 0x28 address
        X_Axis_MSB          {0x28, 8, 24},
        Y_Axis_MSB          {0x28, 8, 16},
        Z_Axis_MSB          {0x28, 8, 8},
        New_Data            {0x28, 1, 7},
        Interrupt           {0x28, 1, 6},
        Temperature_MSB     {0x28, 6, 0},

        // 0x28 address
        Interrupt_Write     {0x29, 1, 20},
        X_Axis_LSB          {0x29, 4, 16},
        Y_Axis_LSB          {0x29, 4, 12},
        Z_Axis_LSB          {0x29, 4, 8},
        Hall_Mode_Status    {0x29, 2, 6},
        Temperature_LSB     {0x29, 6, 0};
    
}

class ALS31300{
private: 
    uint8_t m_deviceAddress;

    constexpr uint32_t getMask(uint8_t numBits, uint8_t offset){
        return (((uint32_t)1 << numBits) - 1) << offset;
    }

    constexpr uint16_t splitRegDecode(Reg regLow, uint32_t lsb, Reg regHigh, uint32_t msb){
        return static_cast<uint16_t>((getValue(regHigh, msb) << regLow.numBits) + getValue(regLow, lsb));
    }

    constexpr int16_t signExtend(uint32_t data, int width){
        int16_t mask = 1L << (width - 1);
        data = data & ((1 << width) - 1);
        return static_cast<int16_t>((data ^ mask) - mask);
    }

public: 
    ALS31300(uint8_t deviceAddress) : m_deviceAddress(deviceAddress){};

    uint32_t read(uint8_t address){
        Wire.beginTransmission(m_deviceAddress);
        Wire.write(address);
        Wire.endTransmission(false);

        Wire.requestFrom(static_cast<int>(m_deviceAddress), 4);
        uint32_t value = static_cast<uint32_t>(Wire.read() & 0xFF) << 24;
        value += static_cast<uint32_t>(Wire.read() & 0xFF) << 16;
        value += static_cast<uint32_t>(Wire.read() & 0xFF) << 8;
        value += static_cast<uint32_t>(Wire.read() & 0xFF);
        delay(10);

        return value;
    }

    uint32_t read(Reg reg){
        return read(reg.address);
    }
    
    void write(uint8_t address, uint32_t value){
        Wire.beginTransmission(m_deviceAddress);
        Wire.write(address);
        Wire.write(static_cast<uint8_t>(value >> 24));
        Wire.write(static_cast<uint8_t>(value >> 16));
        Wire.write(static_cast<uint8_t>(value >> 8));
        Wire.write(static_cast<uint8_t>(value));    
        Wire.endTransmission();
        delay(100);
    }

    void write(Reg reg, uint32_t value){
        write(reg.address, value);
    }

    void unlock(){
        write(0x35, 0x2C413534);
    }

    constexpr uint32_t getValue(Reg reg, uint32_t value){
        auto mask = getMask(reg.numBits, reg.offset);
        return (value & mask) >> reg.offset;
    }

    constexpr void setValue(Reg reg, uint32_t &regValue, uint32_t value){
        auto mask = getMask(reg.numBits, reg.offset);
        regValue &= ~mask; // clear bits
        regValue |= value << reg.offset;
    }

    FullRMA readFull(){
        uint32_t lsb = read(RegMap::X_Axis_LSB.address);
        uint32_t msb = read(RegMap::X_Axis_MSB.address);

        auto X = splitRegDecode(RegMap::X_Axis_LSB, lsb, RegMap::X_Axis_MSB, msb);
        auto Y = splitRegDecode(RegMap::Y_Axis_LSB, lsb, RegMap::Y_Axis_MSB, msb);
        auto Z = splitRegDecode(RegMap::Z_Axis_LSB, lsb, RegMap::Z_Axis_MSB, msb);
        auto T = splitRegDecode(RegMap::Temperature_LSB, lsb, RegMap::Temperature_MSB, msb);

        return FullRMA{
            signExtend(X, RegMap::X_Axis_LSB.numBits + RegMap::X_Axis_MSB.numBits),
            signExtend(Y, RegMap::Y_Axis_LSB.numBits + RegMap::Y_Axis_MSB.numBits),
            signExtend(Z, RegMap::Z_Axis_LSB.numBits + RegMap::Z_Axis_MSB.numBits),
            signExtend(T, RegMap::Temperature_LSB.numBits + RegMap::Temperature_MSB.numBits)
        };
    }
};

