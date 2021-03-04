// #include "i2cArduino.h"
// #include "joystickPS4.h"
#include "robotController.h"

#include <thread>


int main(void)
{
    char* jdeviceName = (char*)"/dev/input/js0";
    int i2cAddress = 0x04;

    I2CArduino i2c(i2cAddress);
    JoystickPS4 ps4(jdeviceName);

    RobotController robot(&ps4, &i2c);

    robot.initDevices();
    robot.initInput();

    // ps4.connect();
    // i2c.connect();

    return 0;
}