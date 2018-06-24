
#include <X11/Xlib.h>


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

    /* Create default Graphics Context */
    *gc = XCreateGC(display, win, valuemask, &values);
    /* Specify font */
    if (NULL != font_info)
    {
    //XSetFont(display, *gc, font_info−>fid);
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

