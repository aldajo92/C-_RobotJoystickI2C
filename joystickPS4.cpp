#include "joystickPS4.h"

JoystickPS4::JoystickPS4(char* deviceName)
{
    _deviceName = deviceName;
}

void JoystickPS4::connect(){
    js = open(_deviceName, O_RDONLY);
    if (js == -1)
        perror("Could not open joystick");
}

int JoystickPS4::read_event(int fd, struct js_event *event)
{
    ssize_t bytes;

    bytes = read(fd, event, sizeof(*event));

    if (bytes == sizeof(*event))
        return 0;

    /* Error, could not read full event. */
    return -1;
}

/**
 * Returns the number of axes on the controller or 0 if an error occurs.
 */
size_t JoystickPS4::get_axis_count(int fd)
{
    __u8 axes;

    if (ioctl(fd, JSIOCGAXES, &axes) == -1)
        return 0;

    return axes;
}

size_t JoystickPS4::get_axis_state(struct js_event *event, struct axis_state axes[3])
{
    size_t axis = event -> number / 2;

    if (axis < 3)
    {
        if (event->number % 2 == 0)
            axes[axis].x = event->value;
        else
            axes[axis].y = event->value;
    }

    return axis;
}

void JoystickPS4::listenInput(void (*callback)(int*))
{
    // void (*handle)(int) = callback;

    while(read_event(js, &event) == 0){
        
        int data[4];
        switch (event.type)
        {
            case JS_EVENT_AXIS:
                get_axis_state(&event, _axes);
                data[0] = _axes[0].x;
                data[1] = _axes[0].y;
                data[2] = _axes[1].y;
                data[3] = _axes[2].x;
                callback(data);
                    // handleAxis(_axis, _axes);
                break;
            default:
                /* Ignore init events. */
                break;
        }
        
        fflush(stdout);
    }
}

void JoystickPS4::handleAxis(size_t axis, struct axis_state axes[3])
{
    int i = 0;
    printf(" axis%d (%6d, %6d)", i, axes[i].x, axes[i].y);
    printf(" axis%d (%6d, %6d)", 1, axes[1].y, axes[2].x);
    printf("\n");
}