#ifndef JOYSTICKPS4_H
#define JOYSTICKPS4_H

#include <linux/joystick.h>
#include "commonlibs.h"

struct axis_state {
    short x, y;
};

class JoystickPS4
{
    public:
        JoystickPS4(char* deviceName);
        void connect();
        int read_event(int, struct js_event*);
        size_t get_axis_state(struct js_event*, struct axis_state*);
        size_t get_axis_count(int);

        void listenInput(void(*callback)(int*));
        void handleAxis(size_t, struct axis_state*);
    private:
        char* _deviceName;
        int js;
        struct js_event event;
        struct axis_state _axes[3] = {0};
        size_t _axis;
};

#endif
