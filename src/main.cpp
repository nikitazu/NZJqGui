#include <stdio.h>

#include "lib/fltk-1.3.9/FL/Fl.H"
#include "lib/fltk-1.3.9/FL/Fl_Window.H"
#include "lib/fltk-1.3.9/FL/Fl_Box.H"

#include "Fl_WindowEx.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, char** argv)
{
    printf("[INIT] FLTK -- START\n");

    auto window = Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT);
    auto box = Fl_Box(20, 40, 300, 100, "Hello, FLTK!");

    Fl_WindowEx::set_position_center_screen(window);
    window.color(FL_CYAN);

    box.box(FL_UP_BOX);
    box.labelfont(FL_BOLD + FL_ITALIC);
    box.labelsize(36);
    box.labeltype(FL_NORMAL_LABEL);
    box.color(FL_RED);

    window.end();
    window.show(argc, argv);

    printf("[INIT] FLTK -- OK\n");

    return Fl::run();
}
