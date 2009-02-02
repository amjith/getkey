#ifndef __screenkey_h__
#define __screenkey_h__

/* Define True and false */
#ifndef false
#define false 0
#endif
#ifndef true
#define true 1
#endif

#define KEY_STR_PRESS		"KeyStrPress"
#define KEY_STR_RELEASE		"KeyStrRelease"

char keyCode[120][20];

typedef struct
{
	Display* local_dpy;
	Bool doit;
}x_state;



#endif
