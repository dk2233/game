// Simple Xlib application drawing a box in a window.
// gcc hello.c -o output -lX11

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "icon_bitmap"


#define MACRO_TO_SET_TEXTPROPERTY(string_pointer,text_property)        \
  if (True != XStringListToTextProperty(&string_pointer,1,&text_property))\
  {   printf(" not worked to make text property from string: %s \n",string_pointer);\
      exit(1);}
      

void getGC(Window win, GC *gc, XFontStruct *font_info, Display *display);

struct timespec reqT = { 2, 0};
struct timespec remainT;
//(win, gc, font_info);


void getGC(Window win, GC *gc, XFontStruct *font_info, Display *display)
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

		/* Create default Graphics Context */
		*gc = XCreateGC(display, win, valuemask, &values);
		/* Specify font */
		if (NULL != font_info)
		{
		//XSetFont(display, *gc, font_info−>fid);
		}

/* Specify black foreground since default window background
* is white and default foreground is undefined */
//XSetForeground(display, *gc, BlackPixel(display,screen_num));
/* Set line attributes */
XSetLineAttributes(display, *gc, line_width, line_style,
cap_style, join_style);
/* Set dashes */
XSetDashes(display, *gc, dash_offset, dash_list, list_length);
}





int main(int argc, char **argv) 
{
    Display *display;
    Window window, window2;
    XEvent event;
    char *msg = "Hello, World! aaa";
    char *msg2 = " second window";
    char *textIcon = "ikonka";
    char *textWindow = "okienko";
    char *text;
    char *progName;
    int screen, nr;
    XVisualInfo  xvInfo;
    XVisualInfo  *xv_info_p ;
    Pixmap icon_pixmap;
    XTextProperty windowName, iconName ;
    XClassHint *windowClasHint;
    XSizeHints *windowSizeHint;
    XWMHints   *windowWMHints;
	GC graphContent;
    
    windowClasHint = XAllocClassHint();
    windowSizeHint = XAllocSizeHints();
    windowWMHints = XAllocWMHints();
    if (NULL == windowWMHints)
    {
        printf(" problem alocating WM hints");
        exit(1);
    }
    
    if (1< argc)
    {
        progName = argv[0];
        
    }
    else
    {
        progName = " Default Name";
    }
    
    MACRO_TO_SET_TEXTPROPERTY(textIcon, iconName);
    MACRO_TO_SET_TEXTPROPERTY( textWindow, windowName);
    
    text = malloc(100);

    /* open connection with the server */
    display = XOpenDisplay(NULL);
    if (display == NULL) 
    {
        fprintf(stderr, "Cannot open display \n");
;
        exit(1);
    }
    //need to use here macro
    printf(" diplay name %s \n",DisplayString(display));
    
        //printf(" screen %d \n",display->default_screen);
 //XSync();
    screen = DefaultScreen(display);
    
    /* create window */
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0, 400,
      400, 10, BlackPixel(display, screen), WhitePixel(display, screen));
    
    window2 = XCreateSimpleWindow(display, RootWindow(display, screen), 80, 200, 80,
      80, 1, BlackPixel(display, screen), WhitePixel(display, screen));
    
    printf(" window %ld %ld \n",window, window2);
    /* select kind of events we are interested in */
    XSelectInput(display, window, ExposureMask | KeyPressMask | FocusChangeMask);
    XSelectInput(display, window2, ExposureMask | LeaveWindowMask);
    
    xv_info_p = XGetVisualInfo(display, VisualNoMask, &xvInfo, &nr);
    
    printf(" how many %d \n ",nr);
    printf(" address %ld \n",(long)xv_info_p);
    //xv_info_p;
    if (NULL != xv_info_p)
    {
        printf(" depth %d ",xv_info_p->screen);
    }
    else
    {
        printf(" not get anything \n");
    }
    
    icon_pixmap = XCreateBitmapFromData(display,window, icon_bitmap_bits , icon_bitmap_width, icon_bitmap_height);
    //TODO
    windowClasHint->res_name  = progName;
    windowClasHint->res_class = "Window1";
    
    windowSizeHint->flags = PPosition | PSize | PMinSize ;
    windowSizeHint->min_width = 200;
    windowSizeHint->min_height = 200;
    
    windowWMHints->icon_pixmap = icon_pixmap;
	windowWMHints->icon_window = window;
    windowWMHints->input = True;
    windowWMHints->initial_state = NormalState;
    windowWMHints->flags = IconPixmapHint | StateHint | InputHint;
    
    XSetWMProperties(display,window, &windowName, &iconName,argv,argc,windowSizeHint, windowWMHints, windowClasHint);
	
	getGC(window,&graphContent,NULL, display );    
	//XGetGCValues();
    
/* map (show) the window */
    XMapWindow(display, window);
    XMapWindow(display, window2);
    
  /* event loop */
    while (1) 
    {
        XNextEvent(display, &event);
	  
          /* draw or redraw the window */
          if (event.type == Expose) 
          {
              XFillRectangle(display, window, DefaultGC(display, screen), 20, 20, 50, 50);
              
              XFillRectangle(display, window2, DefaultGC(display, screen), 10, 10, 50, 10);
              
              XDrawString(display, window, DefaultGC(display, screen), 20, 90, msg,
              strlen(msg));
              
              XDrawString(display, window2, DefaultGC(display, screen), 10, 90, msg2,
              strlen(msg2));
              
              sprintf(text,"height is %d",DisplayHeight(display,screen)); 
              XDrawString(display, window, DefaultGC(display,screen),10,130,text,strlen(text));   
              sprintf(text,"width is %d",DisplayWidth(display,screen));
              XDrawString(display, window, DefaultGC(display,screen),10,150,text,strlen(text));   
              
              //XWriteBitmapFile(display, window,icon_pixmap,icon_bitmap_width, icon_bitmap_height, 10,200);
              
              //printf(" Expose \n" );
          }
        if (FocusOut == event.type )
        {
            printf(" Focus \n");
        }
        /* exit on key press */
        if (event.type == KeyPress) 
        {
            break;
        }
        if (LeaveNotify == event.type)
        {
            printf(" leaving 2 window \n");
        }
    }
    
    nanosleep(&reqT,NULL);
    /* close connection to server */
    XCloseDisplay(display);

    return 0;
}
