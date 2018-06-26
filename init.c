
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>


void initGC(Window win, GC *gc, XFontStruct *font_info, Display *display, int screen_nr)
{
    unsigned long valuemask = 0; /* Ignore XGCvalues and
    * use defaults */
    XGCValues values;
    unsigned int line_width = 6;
    int line_style = LineOnOffDash;
    int cap_style = CapRound;
    int join_style = JoinRound;
    int dash_offset = 0;
    static char dash_list[] = {12, 24};
    int list_length = 2;
    char *fontname = "9x15";

	/* Create default Graphics Context */
    *gc = XCreateGC(display, win, valuemask, &values);

	/* Load font and get font information structure */
	//if  (NULL != font_info) 
	if (1)
	{
		font_info = XLoadQueryFont(display,fontname);

		if  (NULL == font_info)  
		{
			printf(" Cannot open 9x15 font\n");
			exit(1);
		}
		else
		{
			printf("font %ld \n",font_info->fid);
			XSetFont(display, *gc, font_info->fid);
		}
	}
	
    
    /* Specify black foreground since default window background
    * is white and default foreground is undefined */
    XSetForeground(display, *gc, BlackPixel(display,screen_nr));
    /* Set line attributes */
    XSetLineAttributes(display, *gc, line_width, line_style,
    cap_style, join_style);
    /* Set dashes */
    XSetDashes(display, *gc, dash_offset, dash_list, list_length);
}

