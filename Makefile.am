AUTOMAKE_OPTIONS = foreign
CFLAGS=-Wall -I/usr/local/include -DVERSION=\"$(VERSION)\" -DPROG="\"$(PACKAGE)\"" 
LDFLAGS=-L/usr/local/lib -lX11 -lXtst -lxosd

bin_PROGRAMS = getkey
getkey_SOURCES = getkey.c circ_list.c
