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
#include "list.h"

unsigned int QuitKey;
Bool HasQuitKey = false;
Bool EnableDelimiters = false;
unsigned int Len=3, XosdTimeout = 0;
unsigned int delimiter[] = {9, 36, 65, -1};


void usage(const int exitCode)
{
	fprintf (stderr, "%s %s\n", PROG, VERSION);
	fprintf (stderr, "Usage: %s [option]\n",PROG );
	fprintf (stderr, "Options:\n");
	fprintf (stderr,
			"  -l  <NUM>\n"\
		    "      Number of keys to display. Default: 3\n"\
			"      Set this to -1 for unlimited length. \n"\
			"  -t  <NUM>\n"
		    "      Number of seconds to display the OSD. Default: 0\n"\
			"      Set this number to 0 to stick the OSD always.\n"\
			"  -d  Enable delimiters. Delimiters are special keys that will clear the current keylist history.\n"\
		    "      Default: Enter, Esc, Space\n"\
			"  -q  <NUM>\n"\
		    "      Specify the key code for the quit key.\n"\
			"     (Don't use this unless you know the key code for your quit key)\n"\
			"  -v  show version. \n"\
			"  -h  Display this help. \n"\
			);
	exit(exitCode);
}

void version()
{
	fprintf(stderr, "%s %s\n", PROG, VERSION);
	exit(EXIT_SUCCESS);
}

void parseCommand(int argc, char *argv[])
{
	int index = 1;
	while (index < argc)
	{
		/* is this '-v'? */
		if ( ( 0 == strcmp (argv[index], "--version") ) || ( 0 == strcmp (argv[index], "-v") ) )
		{
			version();
		}
		/* is this '-h'? */
		if ( ( 0 == strcmp(argv[index], "--help") ) ||  ( 0 == strcmp(argv[index], "-h") ) )
		{
			usage(EXIT_SUCCESS);
		}
		if ( 0 == strcmp(argv[index], "-l") )
		{
			if ( (argc <= index + 1) || (sscanf (argv[index+1], "%u", &Len) != 1) )
			{
				// Check if valid integer
				fprintf (stderr, "Invalid parameter for '-l'.\n");
				usage (EXIT_FAILURE);
			}
			index++;
		}
		else if( 0 == strcmp(argv[index], "-t") )
		{
			// Check if valid integer
			if ( (argc <= index + 1) || (sscanf (argv[index+1], "%u", &XosdTimeout) != 1) )
			{
				fprintf (stderr, "Invalid parameter for '-t'.\n");
				usage (EXIT_FAILURE);
			}
			index++;
		}
		else if( 0 == strcmp(argv[index], "-d") )
		{
			EnableDelimiters = true;
		}
		else if( 0 == strcmp(argv[index], "-q") )
		{
			if ( (argc <= index + 1) || (sscanf (argv[index+1], "%u", &QuitKey) != 1) )
			{
				// Check if valid integer
				fprintf (stderr, "Invalid parameter for '-q'.\n");
				usage (EXIT_FAILURE);
			}
			HasQuitKey = true;
			index++;
		}
		else
		{
			fprintf(stderr, "Invalid option '%s'\n",argv[index]);
			usage(EXIT_FAILURE);
		}
		index++;
	}
}

void initialize_keyCode()
{
	strcpy(keyCode[9] ,  "Esc");
	strcpy(keyCode[67] ,  "F1");
	strcpy(keyCode[68] ,  "F2");
	strcpy(keyCode[69] ,  "F3");
	strcpy(keyCode[70] ,  "F4");
	strcpy(keyCode[71] ,  "F5");
	strcpy(keyCode[72] ,  "F6");
	strcpy(keyCode[73] ,  "F7");
	strcpy(keyCode[74] ,  "F8");
	strcpy(keyCode[75] ,  "F9");
	strcpy(keyCode[76] ,  "F10");
	strcpy(keyCode[95] ,  "F11");
	strcpy(keyCode[96] ,  "F12");
	strcpy(keyCode[111] ,  "PrtScn");
	strcpy(keyCode[78] ,  "ScrLk");
	strcpy(keyCode[110] ,  "Pause");
	strcpy(keyCode[49] ,  "`");
	strcpy(keyCode[10] ,  "1");
	strcpy(keyCode[11] ,  "2");
	strcpy(keyCode[12] ,  "3");
	strcpy(keyCode[13] ,  "4");
	strcpy(keyCode[14] ,  "5");
	strcpy(keyCode[15] ,  "6");
	strcpy(keyCode[16] ,  "7");
	strcpy(keyCode[17] ,  "8");
	strcpy(keyCode[18] ,  "9");
	strcpy(keyCode[19] ,  "0");
	strcpy(keyCode[20] ,  "-");
	strcpy(keyCode[21] ,  "=");
	strcpy(keyCode[22] ,  "BkSpc");
	strcpy(keyCode[23] ,  "Tab");
	strcpy(keyCode[24] ,  "q");
	strcpy(keyCode[25] ,  "w");
	strcpy(keyCode[26] ,  "e");
	strcpy(keyCode[27] ,  "r");
	strcpy(keyCode[28] ,  "t");
	strcpy(keyCode[29] ,  "y");
	strcpy(keyCode[30] ,  "u");
	strcpy(keyCode[31] ,  "i");
	strcpy(keyCode[32] ,  "o");
	strcpy(keyCode[33] ,  "p");
	strcpy(keyCode[34] ,  "[");
	strcpy(keyCode[35] ,  "]");
	strcpy(keyCode[51] ,  "\\");
	strcpy(keyCode[66] ,  "CapsLk");
	strcpy(keyCode[38] ,  "a");
	strcpy(keyCode[39] ,  "s");
	strcpy(keyCode[40] ,  "d");
	strcpy(keyCode[41] ,  "f");
	strcpy(keyCode[42] ,  "g");
	strcpy(keyCode[43] ,  "h");
	strcpy(keyCode[44] ,  "j");
	strcpy(keyCode[45] ,  "k");
	strcpy(keyCode[46] ,  "l");
	strcpy(keyCode[47] ,  ";");
	strcpy(keyCode[48] ,  "'");
	strcpy(keyCode[36] ,  "Enter");
	strcpy(keyCode[50] ,  "Shift");        // Left Shift
	strcpy(keyCode[52] ,  "z");
	strcpy(keyCode[53] ,  "x");
	strcpy(keyCode[54] ,  "c");
	strcpy(keyCode[55] ,  "v");
	strcpy(keyCode[56] ,  "b");
	strcpy(keyCode[57] ,  "n");
	strcpy(keyCode[58] ,  "m");
	strcpy(keyCode[59] ,  ",");
	strcpy(keyCode[60] ,  ".");
	strcpy(keyCode[61] ,  "/");
	strcpy(keyCode[62] ,  "Shift");       // Right Shift
	strcpy(keyCode[37] ,  "Ctrl");        // Left Ctrl
	strcpy(keyCode[115] , "Win");	      // Left Windows key
	strcpy(keyCode[64] ,  "Alt");	      // Left Alt key
	strcpy(keyCode[65] ,  "Spc");
	strcpy(keyCode[113] ,  "Alt");        // Right
	strcpy(keyCode[116] ,  "Win");        // Right Windows key
	strcpy(keyCode[117] ,  "Menu");
	strcpy(keyCode[109] ,  "Ctrl");       // Right Ctrl
	strcpy(keyCode[106] ,  "Insert");
	strcpy(keyCode[97] ,  "Home");
	strcpy(keyCode[99] ,  "PgUp");
	strcpy(keyCode[107] ,  "Del");
	strcpy(keyCode[103] ,  "End");
	strcpy(keyCode[105] ,  "PgDn");
	strcpy(keyCode[98] ,  "Up");
	strcpy(keyCode[100] ,  "Left");
	strcpy(keyCode[104] ,  "Down");
	strcpy(keyCode[102] ,  "Right");
	strcpy(keyCode[77] ,  "NumLock");
	strcpy(keyCode[112] , "/ (KP)");
	strcpy(keyCode[63] ,  "* (KP)");
	strcpy(keyCode[82] ,  "- (KP)");
	strcpy(keyCode[79] ,  "7 (KP)");
	strcpy(keyCode[80] ,  "8 (KP)");
	strcpy(keyCode[81] ,  "9 (KP)");
	strcpy(keyCode[86] ,  "+ (KP)");
	strcpy(keyCode[83] ,  "4 (KP)");
	strcpy(keyCode[84] ,  "5 (KP)");
	strcpy(keyCode[85] ,  "6 (KP)");
	strcpy(keyCode[87] ,  "1 (KP)");
	strcpy(keyCode[88] ,  "2 (KP)");
	strcpy(keyCode[89] ,  "3 (KP)");
	strcpy(keyCode[108] ,  "Enter (KP)");
	strcpy(keyCode[90] ,  "0  (KP)");
	strcpy(keyCode[91] ,  ".  (KP)"); 
} 


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
	xosd_set_timeout(osd, XosdTimeout);
	xosd_set_shadow_offset(osd, 1);
	xosd_set_pos(osd,XOSD_top);
	xosd_set_align(osd,XOSD_center);
	xosd_display (osd, 0, XOSD_string, display_string);
}

void printList(Display *local_dpy, list_node_int** key_list, int new_key)
{
	//Bool first_time = true;
	list_node_int *node = *key_list, *head = *key_list;
	char buf[1024], str_buf[2048];
	int len=0;
	list_node_int* new_key_node;
	static list_node_str* key_str = NULL;
	list_node_str* str_node, *str_head;
	list_node_str* new_node=NULL;
	static int key_str_len = 0;
	char* new_key_str;
	int persist = false; // if the new key is just another special key, don't add it to the str list, just print it once.
	int i = 0;

	// Create a new str buf with the existing list (The list will have only special keys)
	do 
	{
		if(node) // Make sure node is not null
		{
			node = node->prev;
			len += sprintf(buf+len, "%s+", keyCode[node->key]);
		}
	}while(node != head); // Traverse the linked list in the reverse order

	// If incoming key is special key add it to list.
	switch(new_key)
	{
		case 37:   // L-Ctrl
		case 50:   // L-Shift
		case 62:   // R-Shift 
		case 64:   // L-Alt
		case 109:  // R-Ctrl
		case 115:  // L-Win
		case 116:  // R-Win
			if(!(new_key_node = (list_node_int*)malloc(sizeof(list_node_int)) ) )
			{
				printf("Out of Memory!!");
				exit(1);
			}
			new_key_node->prev = NULL;
			new_key_node->prev = NULL;
			new_key_node->key = new_key;
			add_node_int(key_list, new_key_node);
			break;
		default:
			persist = true; // Add it to str list only if the new key is a regular key.
			break;
	}

	len += sprintf(buf+len,"%s",keyCode[new_key]);  // Add the new key to the str_buf.

	if(!(new_key_str = (char*)malloc(sizeof(char) * (strlen(buf) +1) ) ))
	{
		printf("Out of Memory!!");
		exit(1);
	}

	strcpy(new_key_str, buf);

	if(!(new_node = (list_node_str*)malloc(sizeof(list_node_str))))
	{
		printf("Out of Memory!!");
		exit(1);
	}

	new_node->str = new_key_str;

	add_node_str(&key_str, new_node);
	key_str_len++;
	// After key_str_len reaches Len start removing keys from the list
	if(key_str_len > Len)
	{
		key_str_len--;
		delete_node_str(&key_str, key_str->prev);
	}
	str_node = key_str; 
	str_head = key_str; 
	len = 0;
	do
	{
		str_node = str_node->prev;
		len += sprintf(str_buf+len, "%s ",str_node->str);
	}while(str_node != str_head);
	display_osd(str_buf);

	// Ugly hack: Take out the new_node since persist is false.
	// Best method is to not add it to the str_list at all.
	if(!persist)
	{
		key_str_len--;
		delete_node_str(&key_str, new_node);
	}

	if(EnableDelimiters)
	{
		while(delimiter[i]!=-1)
		{
			if(delimiter[i] == new_key)	// delimiter key
			{
				clear_list_str(&key_str);
				key_str_len = 0;
				break;
			}
			i++;
		}
	}

}

void eventCallback (XPointer x_data, XRecordInterceptData * d)
{
	x_state* data = (x_state *) x_data;
	unsigned char *ud1;
	unsigned int type, cur_key;
	unsigned char type1, detail1;
	static list_node_int *keylist = NULL;

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
		case KeyRelease:
			/* a key was released */
			//printList(data->local_dpy,keylist);
			delete_node_int(&keylist, search_node_int(keylist, cur_key));
			break;
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
				/*--------------------------------------------------
				* new_node = (list_node_int*)malloc(sizeof(list_node_int));
				* new_node->prev = NULL;
				* new_node->next = NULL;
				* new_node->key = cur_key;
				* add_node_int(&keylist, new_node);
				*--------------------------------------------------*/
				printList(data->local_dpy,&keylist, cur_key);
			}
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

int main(int argc, char *argv[])
{
	Display *LocalDisplay = XOpenDisplay (NULL);
	Display *RecDisplay = XOpenDisplay (NULL);
	if(!LocalDisplay || !RecDisplay)
	{
		fprintf(stderr, "Could not open local display\n");
		exit(EXIT_FAILURE);
	}
	int LocalScreen = DefaultScreen (LocalDisplay);

	parseCommand(argc, argv);

	initialize_keyCode();
	if (false == HasQuitKey)
	{
		printf("Press a key to be used as quit key\n");
		QuitKey = findQuitKey(LocalDisplay, LocalScreen);
		HasQuitKey = true;
	}

	//fprintf(stderr, XKeysymToString(XKeycodeToKeysym(LocalDisplay, QuitKey,0)));
	fprintf(stderr, "QuitKey: %s(%d)\n", XKeysymToString(XKeycodeToKeysym(LocalDisplay, QuitKey,0)), QuitKey);
	//printf("QuitKey:%d\n",QuitKey);
	
	/* start the main event loop */
	eventLoop (LocalDisplay, LocalScreen, RecDisplay, QuitKey);

	/* we're done with the display */
	XCloseDisplay (LocalDisplay);
	XCloseDisplay ( RecDisplay ); 
	return 0;
}
