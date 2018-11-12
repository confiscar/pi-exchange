#include <qapplication.h>
#include <qpushbutton.h>


int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    QPushButton hello( "Hello world!", 0 ); /*create button that says hello */
    hello.resize( 100, 30 ); /*size of button*/

    
    hello.show(); /*show the window */
    return a.exec(); 
}

