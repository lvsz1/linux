CC = gcc
XX = g++
CFLAGS = -Wall -O 
TARGET = ./ioctl_arp
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
%.o:%.cpp
	$(XX) $(CFLAGS) -c $< -o $@

SOURCES = $(wildcard *.c *.cpp)
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))
$(TARGET) : $(OBJS)
	$(XX) $(OBJS) -o $(TARGET)

clean:
	rm -rf *.o ioctl_arp

