#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlibint.h>
#include <X11/Xlib.h>
#include <errno.h>
#include <time.h>
#include <X11/Xlibint.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <X11/keysymdef.h>
#include <X11/keysym.h>
#include <X11/extensions/record.h>
#include <xosd.h>
#include "getkey.h"
unsigned int QuitKey;
Bool HasQuitKey;

typedef struct
{
	Display* local_dpy;
	Bool doit;
}x_state;

int findQuitKey(Display *Dpy, int Screen)
{

	XEvent Event;
	XKeyEvent EKey;
	Window  Root;
	int Loop = true;
	int Error;

	/* get the root window */
	Root = RootWindow (Dpy, Screen);

	/* grab the keyboard */
	Error = XGrabKeyboard (Dpy, Root, false, GrabModeSync, GrabModeAsync, CurrentTime);

	/* did we succeed in grabbing the keyboard?*/
	if (Error != GrabSuccess)
	{
		/* nope, abort */
		fprintf (stderr, "Could not grab the keyboard, aborting.");
		exit (EXIT_FAILURE);
	}

	while (Loop)
	{
		/* allow one more event */
		XAllowEvents (Dpy, SyncPointer, CurrentTime);
		XWindowEvent (Dpy, Root, KeyPressMask, &Event);

		/* what did we get? */
		if (Event.type == KeyPress)
		{
			/* a key was pressed, don't loop more */
			EKey = Event.xkey;
			Loop = false;
		}
	}

	/* we're done with pointer and keyboard */
	XUngrabPointer (Dpy, CurrentTime);
	XUngrabKeyboard (Dpy, CurrentTime);

	/* return the found key */
	return EKey.keycode;
}

/*--------------------------------------------------
* Prints the string on the OSD using the XOSD library
*--------------------------------------------------*/

void display_osd(char *display_string)
{
	static xosd *osd;

	xosd_hide(osd);
	osd = xosd_create (1);
	xosd_set_font(osd, "-adobe-courier-medium-r-normal--34-240-100-100-m-200-iso8859-1");
	xosd_set_colour(osd, "LawnGreen");
	xosd_set_timeout(osd, 1);
	xosd_set_shadow_offset(osd, 1);
	xosd_set_pos(osd,XOSD_top);
	xosd_set_align(osd,XOSD_center);
	xosd_display (osd, 0, XOSD_string, display_string);
}

typedef struct
{
	struct list_node* prev;
	struct list_node* next;
	unsigned int key;
}list_node;

typedef struct list
{
	list_node* first_node;
	list_node* last_node;
}list;


void insertAfter(list* key_list, list_node* node, list_node* new_node)
{
	new_node->prev = node;
	new_node->next = node->next;
	if (node->next == NULL)
		key_list->last_node = new_node;
	else
		((list_node*)(node->next))->prev = new_node;
	node->next = new_node;
}

void insertBefore(list* key_list, list_node* node, list_node* new_node)
{
	new_node->prev = node->prev;
	new_node->next = node;
	if (node->prev == NULL)
		key_list->first_node = new_node;
	else
		((list_node*)(node->prev))->next = new_node;
	node->prev = new_node;

}

void insertBeginning(list* key_list, unsigned int key)
{
	list_node *new_node = (list_node*)malloc(sizeof(list_node));
	new_node->key = key;
	if(key_list->first_node == NULL)
	{
		key_list->first_node = new_node;
		key_list->last_node = new_node;
		new_node->prev = NULL;
		new_node->next = NULL;
	}
	else
		insertBefore(key_list, key_list->first_node, new_node);
}

void insertEnd(list* key_list, unsigned int key)
{
	if(key_list->first_node == NULL)
		insertBeginning(key_list, key);
	else
	{
		list_node *new_node = malloc(sizeof(list_node));
		new_node->key = key;
		insertAfter(key_list, key_list->first_node, new_node);
	}
}
void removeNode(list* key_list, list_node *node)
{
	if (node->next == NULL)// last node
	{
		key_list->last_node = node->prev;
		if(node->prev)
			((list_node*)(node->prev))->next = NULL;
	}
	else
		((list_node*)(node->next))->prev = node->prev;
	if (node->prev == NULL) // first node
	{
		key_list->first_node = node->next;
		if(node->next)
			((list_node*)(node->next))->prev = NULL;
	}
	else
		((list_node*)(node->prev))->next = node->next;
	free(node);
}
void removeKey(list* key_list, unsigned int key)
{
	list_node* node = key_list->last_node;
	while(node) // loop until head of list
	{
		if(node->key == key)
		{
			removeNode(key_list, node);
			break;
		}
		node = node->prev;
	}
}

void printList(Display *local_dpy, list* key_list)
{
	Bool first_time = true;
	list_node *node = key_list->first_node;
	char buf[1024];
	int len=0;
	while(node)
	{
		if(first_time)
		{
			len = sprintf(buf,"%s",XKeysymToString(XKeycodeToKeysym(local_dpy,node->key,0)));
			display_osd(buf);
			first_time =false;
		}
		else
		{
			len += sprintf(buf+len,"+%s",XKeysymToString(XKeycodeToKeysym(local_dpy,node->key,0)));
			display_osd(buf);
		}
		node = node->next;
	}
}

struct list *g_key_list;

void eventCallback (XPointer x_data, XRecordInterceptData * d)
{
	x_state* data = (x_state *) x_data;
	unsigned char *ud1;
	unsigned int type, cur_key;
	unsigned char type1, detail1;
	static Bool first_time = true;
	if(first_time)
	{
		first_time = false;
		g_key_list = (struct list*)malloc(sizeof(list));
		g_key_list->first_node = NULL;
		g_key_list->last_node = NULL;
	}

	if (d->category != XRecordFromServer || data->doit == 0)
	{
		XRecordFreeData (d);
		return;
	}
	if (d->client_swapped == true)
		fprintf (stderr, "Client is swapped!!!\n");
	ud1 = (unsigned char *) d->data;

	type1 = ud1[0] & 0x7F;
	type = type1;
	detail1 = ud1[1];
	cur_key = detail1;

	/* what did we get? */
	switch (type)
	{
		case KeyPress:
			/* a key was pressed */
			/* should we stop looping, i.e. did the user press the quitkey? */
			if (HasQuitKey && cur_key == QuitKey)
			{
				/* yep, no more loops */
				data->doit = 0;
			}
			else
			{
				insertEnd(g_key_list, cur_key);
			}
			printList(data->local_dpy,g_key_list);
			break;

		case KeyRelease:
			/* a key was released */
			removeKey(g_key_list, cur_key);
			break;
	}
	XRecordFreeData (d);
}

void eventLoop (Display * LocalDpy, int LocalScreen, Display * RecDpy, unsigned int QuitKey)
{
	Window Root/*, rRoot, rChild*/;
	XRecordContext rc;
	XRecordRange *rr;
	XRecordClientSpec rcs;
	x_state var_state;
	Status sret;

	/* get the root window and set default target */
	Root = RootWindow (LocalDpy, LocalScreen);

	rr = XRecordAllocRange ();
	if (!rr)
	{
		fprintf (stderr, "Could not alloc record range, aborting.\n");
		exit (EXIT_FAILURE);
	}
	rr->device_events.first = KeyPress; // Still haven't figured out why we need this
	rr->device_events.last = MotionNotify;
	rcs = XRecordAllClients;
	rc = XRecordCreateContext (RecDpy, 0, &rcs, 1, &rr, 1);
	if (!rc)
	{
		fprintf (stderr, "Could not create a record context, aborting.\n");
		exit (EXIT_FAILURE);
	}

	var_state.local_dpy = LocalDpy;
	var_state.doit = true;

	if (!XRecordEnableContextAsync(RecDpy, rc, eventCallback, (XPointer) &var_state))
	{
		fprintf (stderr, "Could not enable the record context, aborting.\n");
		exit (EXIT_FAILURE);
	}

	while (var_state.doit)
		XRecordProcessReplies (RecDpy);

	sret = XRecordDisableContext (LocalDpy, rc);
	if (!sret)
		fprintf (stderr, "XRecordDisableContext failed!\n");
	sret = XRecordFreeContext (LocalDpy, rc);
	if (!sret)
		fprintf (stderr, "XRecordFreeContext failed!\n");
	XFree (rr);
}

int main()
{
	Display *LocalDisplay = XOpenDisplay (NULL);
	Display *RecDisplay = XOpenDisplay (NULL);
	if(!LocalDisplay || !RecDisplay)
	{
		fprintf(stderr, "Could not open local display\n");
	}
	int LocalScreen = DefaultScreen (LocalDisplay);
	//initialize_keyCode();
	printf("Press a key to be used as quit key\n");
	QuitKey = findQuitKey(LocalDisplay, LocalScreen);
	HasQuitKey = true;

	printf(XKeysymToString(XKeycodeToKeysym(LocalDisplay, QuitKey,0)));
	
	/* start the main event loop */
	eventLoop (LocalDisplay, LocalScreen, RecDisplay, QuitKey);

	/* we're done with the display */
	XCloseDisplay (LocalDisplay);
	XCloseDisplay ( RecDisplay ); 
	return 0;
}
