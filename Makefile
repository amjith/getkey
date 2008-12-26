CC=gcc
#CFLAGS=-c -Wall -I/usr/X11R6/include -lX11 -lXtst
OBJECTS=getkey.o circ_list.o
EXECUTABLE=getkey
SOURCE=getkey.c circ_list.c
CFLAGS=-c -g -Wall -I/usr/local/include
LDFLAGS=-L/usr/local/lib -lX11 -lXtst -lxosd

all: getkey.c
	$(CC) $(CFLAGS) $(SOURCE)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(EXECUTABLE)
clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)

