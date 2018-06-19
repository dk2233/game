// Simple Xlib application drawing a box in a window.
// gcc hello.c -o output -lX11

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

 struct timespec reqT = { 2, 0};
 struct timespec remainT;

int main() 
{
  Display *display;
  Window window, window2;
  XEvent event;
  char *msg = "Hello, World! \n aaa";
  char *msg2 = " second window";
  int s;
  

  /* open connection with the server */
  display = XOpenDisplay(NULL);
  if (display == NULL) 
  {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }
 //XSync();
  s = DefaultScreen(display);

  /* create window */
  window = XCreateSimpleWindow(display, RootWindow(display, s), 0, 0, 400,
      400, 1, BlackPixel(display, s), WhitePixel(display, s));

  
  
  window2 = XCreateSimpleWindow(display, RootWindow(display, s), 30, 200, 50,
      50, 1, BlackPixel(display, s), WhitePixel(display, s));

 printf(" window %ld %ld \n",window, window2);
  /* select kind of events we are interested in */
  XSelectInput(display, window, ExposureMask | KeyPressMask | FocusChangeMask);
 XSelectInput(display, window2, ExposureMask );
  /* map (show) the window */
  XMapWindow(display, window);
  XMapWindow(display, window2);

  /* event loop */
  while (1) {
    XNextEvent(display, &event);

    /* draw or redraw the window */
    if (event.type == Expose) {
      XFillRectangle(display, window, DefaultGC(display, s), 20, 20, 50, 50);
      
      XFillRectangle(display, window2, DefaultGC(display, s), 10, 10, 50, 10);
      
      XDrawString(display, window, DefaultGC(display, s), 50, 50, msg,
          strlen(msg));
          
      XDrawString(display, window2, DefaultGC(display, s), 10, 90, msg2,
          strlen(msg2));    
          
          //printf(" Expose \n" );
    }
    if (FocusOut == event.type )
    {
		printf(" Focus \n");
	}
    /* exit on key press */
    if (event.type == KeyPress) {
      break;
    }
  }

 nanosleep(&reqT,NULL);
  /* close connection to server */
  XCloseDisplay(display);
  
  return 0;
}

