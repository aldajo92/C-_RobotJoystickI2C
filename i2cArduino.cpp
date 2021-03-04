#include "i2cArduino.h"

I2CArduino::I2CArduino(int address)
{
    _address = address;
}

void I2CArduino::connect()
{
    if ((file_i2c = open(filename, O_RDWR)) < 0)
    {
        //ERROR HANDLING: check error
        printf("Failed to open i2c bus.\n");
        return;
    }

    if (ioctl(file_i2c, I2C_SLAVE, _address) < 0)
    {
        printf("Failed to acquire bus access and/or talk to slave.\n");
        return;
    }
}

void I2CArduino::writeBytes(unsigned char* buffer, int size)
{
    if(write(file_i2c, buffer, size) != size)
    {
        printf("Failed to write to the i2c bus.\n");
    }
}