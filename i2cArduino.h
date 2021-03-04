#ifndef I2CARDUINO_H
#define I2CARDUINO_H

#include "commonlibs.h"
#include <linux/i2c-dev.h>

class I2CArduino
{
    public:
        I2CArduino(int);
        void connect();
        void writeBytes(unsigned char*, int);
    private:
        int _address;
        char *filename = (char*) "/dev/i2c-1";
        int file_i2c;
        int length;
};

#endif