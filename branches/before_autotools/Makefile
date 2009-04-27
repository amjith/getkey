VERSION=0.1
CC=gcc
#CFLAGS=-c -Wall -I/usr/X11R6/include -lX11 -lXtst
OBJECTS=getkey.o circ_list.o
PROGRAM=getkey
SOURCE=getkey.c circ_list.c
CFLAGS=-c -g -Wall -I/usr/local/include -DVERSION=\"$(VERSION)\"  -DPROG="\"$(PROGRAM)\""
LDFLAGS=-L/usr/local/lib -lX11 -lXtst -lxosd

all: getkey.c getkey.h
	$(CC) $(CFLAGS) $(SOURCE)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(PROGRAM)
clean:
	rm -rf $(OBJECTS) $(PROGRAM)

