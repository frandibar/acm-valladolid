# makefile

# set up compiler and options
CC     = g++-2.95
CFLAGS = -g -Wall --pedantic --ansi

# the name to give the program when built
TARGET = acm

# the .cpp file
OBJ = acm.cpp

# rules
$(TARGET):	$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 
	@echo Target $@ complete.


touch:
	-touch $(OBJ)

clean:
	-rm $(TARGET)
	@echo Target $(TARGET) cleaned.

