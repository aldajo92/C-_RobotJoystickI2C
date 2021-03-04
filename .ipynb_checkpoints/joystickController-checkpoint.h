#ifndef JOYSTICKCONTROLLER_H
#define JOYSTICKCONTROLLER_H


class JoystickController
{
    public:
        JoystickController(char* deviceName);
    private:
        char* _deviceName;
};

#endif
