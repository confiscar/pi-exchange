#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Chart.H>
#include <math.h>
#include <stdio.h>
// Demonstration of how to use Fl_Chart -- erco 11/20/08
int main() {
    Fl_Window *win = new Fl_Window(1000, 480);
    Fl_Chart  *chart0 = new Fl_Chart(20, 20, win->w()-40, win->h()-40, "Chart0           ");
    Fl_Chart  *chart1 = new Fl_Chart(20, 20, win->w()-40, win->h()-40, "           Chart1");
    //chart->type(FL_BAR_CHART);
    //chart->type(FL_HORBAR_CHART);
    chart0->type(FL_LINE_CHART);
    chart1->type(FL_SPIKE_CHART);
    //chart->type(FL_FILLED_CHART);
    chart0->bounds(-125.0, 125.0);
    chart1->bounds(-125.0, 125.0);
    chart1->box(FL_NO_BOX);

    for ( double t=0; t<15; t+=0.5 ) {
        double val0 = sin(t) * 125.0;
        double val1 = cos(t) * 125.0;

        static char val_str0[20];
        static char val_str1[20];
        sprintf(val_str0, "%.0lf", val0);
        sprintf(val_str1, "%.0lf", val1);
        chart0->add(val0, val_str0, (val0<0)?FL_RED:FL_GREEN);
        chart1->add(val1, val_str1, (val1<0)?FL_RED:FL_GREEN);
    }
    win->resizable(win);
    win->show();
    return(Fl::run());
}