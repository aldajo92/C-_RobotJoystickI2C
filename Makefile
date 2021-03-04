CC=g++
CFLAGS = -pthread
# DEPS = ./i2c/i2cArduino.h ./controllers/joystickPS4.h

main: i2cArduino.o joystickPS4.o main.o robotController.o
compilelibs: i2cArduino.o joystickPS4.o robotController.o

clean:
	rm -f i2cArduino.o joystickPS4.o main.o
