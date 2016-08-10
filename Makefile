PWD     	:= $(shell pwd)
TARGET		?=
CROSS_COMPILE   ?= $(TARGET)-
CPP     	:= $(CROSS_COMPILE)g++
CC      	:= $(CROSS_COMPILE)gcc
AR      	:= $(CROSS_COMPILE)ar

SRC_PATH   := .
CFLAGS		= -Os
IOT_OBJS	= $(wildcard $(SRC_PATH)/*.c)
LDFLAGS		+=
targets = gw_daemon

#INC     	+=-I$(NVLIB)/include
LINC		+= -I$(PWD)

all:$(targets)

$(targets): $(IOT_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(IOT_OBJS) $(LINC) -o $@ 

clean:
	rm -f *.o gw_daemon
	
install:

