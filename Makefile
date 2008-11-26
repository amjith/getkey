CC=gcc
#CFLAGS=-c -Wall -I/usr/X11R6/include -lX11 -lXtst
SOURCES=getkey.c
OBJECTS=getkey.o
EXECUTABLE=getkey

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -c -Wall -I/usr/X11R6/include $(SOURCES)
	$(CC) $(OBJECTS) -o $@ -L/usr/X11R6/lib -lX11 -lXtst -lxosd

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
#-I/usr/X11R6/include
