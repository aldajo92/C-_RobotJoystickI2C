#include "robotController.h"

RobotController::RobotController(JoystickPS4* joystickPS4, I2CArduino* i2cArduino)
{
    _joystickPS4 = joystickPS4;
    _i2cArduino = i2cArduino;
}

void RobotController::initDevices()
{
    (*_joystickPS4).connect();
    (*_i2cArduino).connect();
}

void RobotController::initInput()
{
    (*_joystickPS4).listenInput(handleData);
}

void RobotController::handleData(int* data)
{
    // (*_i2cArduino);
    // i2c.writeBytes(unsigned char*, int);
    printf("%d\n", data[0]);
}