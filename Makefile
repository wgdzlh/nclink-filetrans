DIR = bin
TARGET = $(DIR)/ftpdemo
MOBJ = main.o
OBJS = filetrans/filetrans.o filetrans/ftp/ftplib.o json/njdecode.o mqtt/mqtt.o

C = gcc
CC = g++
CINC = -I./include
CLIBS = -L./linux -lmosq -lpthread

CFLAGS = -Wall -Wno-char-subscripts -O3
CPPFLAGS = -std=c++11

$(TARGET): $(OBJS) $(MOBJ)
	@ mkdir -p $(DIR)
	$(CC) -o $@ $^ $(CLIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CINC) -c $^ -o $@

%.o: %.c
	$(C) $(CFLAGS) $(CINC) -c $^ -o $@

all: $(TARGET)

clean:
	rm -rf $(DIR)
	rm -f $(MOBJ) $(OBJS)
