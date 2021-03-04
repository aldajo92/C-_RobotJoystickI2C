#ifndef ROBOTCONTROLLER_H

#include "i2cArduino.h"
#include "joystickPS4.h"

class RobotController
{
    public:
        RobotController(JoystickPS4*, I2CArduino*);
        void initDevices();

        void initInput();
        static void handleData(int*);
        // void listenInput();
        // void handleAxis(size_t, struct axis_state)
    private:
        JoystickPS4 * _joystickPS4;
        I2CArduino * _i2cArduino;

};

#endif