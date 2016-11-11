CC = gcc
XX = g++
CFLAGS = -Wall -O 
TARGET = ./myping
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
%.o:%.cpp
	$(XX) $(CFLAGS) -c $< -o $@

SOURCES = $(wildcard *.c *.cpp)
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))
$(TARGET) : $(OBJS)
	$(XX) $(OBJS) -o $(TARGET)

clean:
	rm -rf *.o myping

