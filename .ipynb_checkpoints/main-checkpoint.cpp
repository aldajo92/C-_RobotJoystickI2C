#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/joystick.h>

// Here I define all function and variables related with i2c
int ADDRESS = 0x04;
char *filename = (char*)"/dev/i2c-1";
int file_i2c;
int length;
unsigned char buffer[60] = {0};

void openI2CBus();
void writeBytes(unsigned char* buffer, int size);

// Here I define all functions associated with joystick.
char *device = (char*)"/dev/input/js0";
struct axis_state {
    short x, y;
};

int read_event(int fd, struct js_event *event);
size_t get_axis_count(int fd);
size_t get_axis_state(struct js_event *event, struct axis_state axes[3]);
void handleAxis(size_t size, struct axis_state axes[3]);


int main()
{
    openI2CBus();
    
    const char *device;
    int js;
    struct js_event event;
    struct axis_state axes[3] = {0};
    size_t axis;
    
    device = "/dev/input/js0";
    
    js = open(device, O_RDONLY);

    if (js == -1)
        perror("Could not open joystick");

    /* This loop will exit if the controller is unplugged. */
    while (read_event(js, &event) == 0)
    {
        switch (event.type)
        {
            case JS_EVENT_AXIS:
                axis = get_axis_state(&event, axes);
                if (axis < 3)
                    handleAxis(axis, axes);
//                     printf("Axis %zu at (%6d, %6d)\n", axis, axes[axis].x, axes[axis].y);
                break;
            default:
                /* Ignore init events. */
                break;
        }
        
        fflush(stdout);
    }

    close(js);
    return 0;
}

void handleAxis(size_t axis, struct axis_state axes[3])
{
    switch(axis)
    {
        case 0:
            printf("axis0 (%6d, %6d)\n", axes[axis].x, axes[axis].y);
            break;
        case 1:
        case 2:
            printf("axis1 (%6d, %6d)\n", axes[axis].x, axes[axis].y);
            break;
    }
}

// I2C functions
void openI2CBus()
{
    if ((file_i2c = open(filename, O_RDWR)) < 0)
    {
        //ERROR HANDLING: check error
        printf("Failed to open i2c bus.\n");
        return;
    }

    if (ioctl(file_i2c, I2C_SLAVE, ADDRESS) < 0)
    {
        printf("Failed to acquire bus access and/or talk to slave.\n");
        return;
    }
}

void writeBytes (unsigned char* buffer, int size)
{
    if(write(file_i2c, buffer, size) != size)
    {
        printf("Failed to write to the i2c bus.\n");
    }
}

// joystic functions
int read_event(int fd, struct js_event *event)
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
size_t get_axis_count(int fd)
{
    __u8 axes;

    if (ioctl(fd, JSIOCGAXES, &axes) == -1)
        return 0;

    return axes;
}

size_t get_axis_state(struct js_event *event, struct axis_state axes[3])
{
    size_t axis = event->number / 2;

    if (axis < 3)
    {
        if (event->number % 2 == 0)
            axes[axis].x = event->value;
        else
            axes[axis].y = event->value;
    }

    return axis;
}
