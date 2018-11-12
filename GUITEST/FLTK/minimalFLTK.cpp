// -*- Mode:C++; Coding:us-ascii-unix; fill-column:132 -*-
/**********************************************************************************************************************************/
/**
   @file      minimalFLTK.cpp
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 2003 by Mitch Richling.  All rights reserved.
   @brief     Minimal FLTK program@EOL
   @Keywords  fltk minimal
   @Std       C++98 FLTKv1.3
***********************************************************************************************************************************/

/**********************************************************************************************************************************/
#include <FL/Fl.H>              /* FLTK main       FLTK  */
#include <FL/Fl_Window.H>       /* FLTK window     FLTK  */

#include <stdio.h>              /* I/O lib         ISOC  */
#include <stdlib.h>             /* Standard Lib    ISOC  */

/**********************************************************************************************************************************/
int main() {
  Fl_Window win(500, 500, "Hello World!");
  win.show();
  return Fl::run();
}
