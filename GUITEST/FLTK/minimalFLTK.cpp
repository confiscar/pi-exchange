
#include <FL/Fl.H>              /* FLTK main       FLTK  */
#include <FL/Fl_Window.H>       /* FLTK window     FLTK  */

#include <stdio.h>              /* I/O lib         ISOC  */
#include <stdlib.h>             /* Standard Lib    ISOC  */

int main() {
  Fl_Window win(500, 500, "Hello World!"); /* set window size with window name */
  win.show(); /*display window */
  return Fl::run();  
}
