#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_window.H>
#include <FL/Fl_Button.H>
using namespace std;

void button_cb( Fl_Widget*, void* );  

void make_window()
{
   Fl_Window* win= new Fl_Window( 200,200, "Hello world" );
   win->begin();
	  Fl_Button* but = new Fl_Button( 0, 0, 40, 40, "hello world" );
   win->end();
   but -> callback( ( Fl_Callback* ) button_cb );
   win->show();
}

void button_cb( Fl_Widget* obj , void* )
{
   obj->label( "its me" );
   obj->resize( 0,0,40,40 );
   obj->redraw();
}

int main( int argc, char* argv[] )
{
   make_window();
   return Fl::run();
}

