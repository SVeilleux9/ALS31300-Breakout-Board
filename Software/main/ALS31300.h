struct Reg{
    const uint8_t 
        address,
        numBits,
        offset;
    
};

struct Field{
    uint16_t x, y, z;
};

namespace RegMap{

    uint8_t addresses[8]{0x02, 0x03, 0x0D, 0x0E, 0x0F, 0x27, 0x28, 0x29};    

    // Address, Length, Offset
    constexpr Reg
        // 0x02 address
        BW_Select           {RegMap::addresses[0], 3, 21},
        Hall_Mode           {RegMap::addresses[0], 2, 19},
        I2C_CRC_Enable      {RegMap::addresses[0], 1, 18},
        Disable_Slave_ADC   {RegMap::addresses[0], 1, 17},
        Slave_Address       {RegMap::addresses[0], 7, 10},
        I2C_Threshold       {RegMap::addresses[0], 1,  9},
        Channel_Z_Enable    {RegMap::addresses[0], 1,  8},
        Channel_Y_Enable    {RegMap::addresses[0], 1,  7},
        Channel_X_Enable    {RegMap::addresses[0], 1,  6},
        NINT_Latch_Enable   {RegMap::addresses[0], 1,  5},
        Customer_EEPROM1    {RegMap::addresses[0], 1,  0},

        // 0x03 address
        Signed_NINT_Enable  {RegMap::addresses[1], 1, 24},
        NINT_Mode           {RegMap::addresses[1], 1, 23},
        NINT_EEPROM         {RegMap::addresses[1], 1, 22},
        NINT_EEPROM_Status  {RegMap::addresses[1], 1, 21},
        NINT_EEPROM_Enable  {RegMap::addresses[1], 1, 20},
        Z_NINT_Enable       {RegMap::addresses[1], 1, 19},
        Y_NINT_Enable       {RegMap::addresses[1], 1, 18},
        X_NINT_Enable       {RegMap::addresses[1], 1, 17},
        Z_NINT_Threshold    {RegMap::addresses[1], 6, 12},
        Y_NINT_Threshold    {RegMap::addresses[1], 6,  6},
        X_NINT_Threshold    {RegMap::addresses[1], 6,  0},

        // 0x0D address
        Customer_EEPROM2    {RegMap::addresses[2], 26, 0},

        // 0x0E address
        Customer_EEPROM3    {RegMap::addresses[3], 26, 0},
        
        // 0x0F address
        Customer_EEPROM4    {RegMap::addresses[4], 26, 0},

        // 0x27 address
        Low_Power_Mode_Count_Max {RegMap::addresses[5], 1, 23},
        I2C_Loop_Mode       {RegMap::addresses[5], 1, 22},
        Sleep               {RegMap::addresses[5], 1, 21},

        // 0x28 address
        X_Axis_MSB          {RegMap::addresses[6], 8, 24},
        Y_Axis_MSB          {RegMap::addresses[6], 8, 16},
        Z_Axis_MSB          {RegMap::addresses[6], 8, 8},
        New_Data            {RegMap::addresses[6], 1, 7},
        Interrupt           {RegMap::addresses[6], 1, 6},
        Temperature_MSB     {RegMap::addresses[6], 6, 0},

        // 0x28 address
        Interrupt_Write     {RegMap::addresses[7], 1, 20},
        X_Axis_LSB          {RegMap::addresses[7], 4, 16},
        Y_Axis_LSB          {RegMap::addresses[7], 4, 12},
        Z_Axis_LSB          {RegMap::addresses[7], 4, 8},
        Hall_Mode_Status    {RegMap::addresses[7], 2, 6},
        Temperature_LSB     {RegMap::addresses[7], 6, 0};
    
}

uint32_t i2c_read(const uint16_t address);
void     i2c_write(const uint16_t address, const uint32_t val);

template <class X, class V>
constexpr auto find(X& x, V key) {
    std::size_t i = 0;
    while(i < x.size()) {
        if(x[i] == key) return i;
        ++i;
    }
    return i;
}

class ALS31300{
private: 
    uint8_t m_deviceAddress;

    std::array<uint32_t, 8> RegMap{0x00000000, 0x00000000, 0x00000000, 0x00000000,
                                   0x00000000, 0x00000000, 0x87654321, 0x87654321};

    constexpr uint32_t getMask(uint8_t numBits, uint8_t offset){
        return ((1 << numBits) - 1) << offset;
    }

    template <typename T, size_t size>
    constexpr T splitRegDecode(std::array<Reg,size> regs){
        size_t runningOffset = 0;
        T output = 0;
        for(size_t i=0; i<size; i++){
            output += static_cast<T>(getValue(regs[i]) << runningOffset);
            runningOffset += regs[i].numBits;
        }
        return output;
    }

public: 
    ALS31300(uint8_t deviceAddress) : m_deviceAddress(deviceAddress){
    };

    void read(uint32_t address){
        auto loc = find(RegMap::addresses, address);
        if(loc != RegMag.addresses.size()){
            RegMap[loc] = i2c_read(address));
        }
    }
    
    void write(uint8_t address, uint32_t value){
        i2c_write(RegMap::addresses[i], RegMap[i]);
    }

    void unlock(){
        write(0x35, 0x2C413534);
    }

    constexpr uint32_t getValue(Reg reg){
        auto loc = find(RegMap::addresses, reg.address);
        if(loc != RegMag.addresses.size()){
            auto mask = getMask(reg.numBits, reg.offset);
            return (RegMap[loc] & mask) >> reg.offset;
        }
        return 0;
    }

    constexpr void setValue(Reg reg, uint32_t value){
        auto loc = find(RegMap::addresses, reg.address);
        if(loc != RegMag.addresses.size()){
            auto mask = getMask(reg.numBits, reg.offset);
            RegMap[loc] &= !mask; // clear bits
            RegMap[loc] |= value;
        }
    }

    constexpr Field getField(){
        return Field{
            splitRegDecode<uint16_t,2>(std::array<Reg,2>{RegMap::X_Axis_LSB, RegMap::X_Axis_MSB}),
            splitRegDecode<uint16_t,2>(std::array<Reg,2>{RegMap::Y_Axis_LSB, RegMap::Y_Axis_MSB}),
            splitRegDecode<uint16_t,2>(std::array<Reg,2>{RegMap::Z_Axis_LSB, RegMap::Z_Axis_MSB})
        };
    }

    constexpr uint16_t getTemperature(){
        return splitRegDecode<uint16_t,2>(std::array<Reg,2>{RegMap::Temperature_LSB, RegMap::Temperature_MSB});
    }
};

