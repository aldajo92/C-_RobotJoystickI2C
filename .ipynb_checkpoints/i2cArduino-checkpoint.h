#ifndef I2CARDUINO_H
#define I2CARDUINO_H

class I2CArduino
{
    public:
        I2CArduino(int);
        void openI2CBus();
        void writeBytes(unsigned char*, int);
    private:
        int _address;
        char *filename = (char*) "/dev/i2c-1";
        int file_i2c;
        int length;
};

#endif