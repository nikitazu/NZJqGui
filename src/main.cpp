#include <stdio.h>
#include "lib/fltk-1.3.9/FL/Fl.H"
#include "lib/fltk-1.3.9/FL/Fl_Window.H"
#include "lib/fltk-1.3.9/FL/Fl_Box.H"

int main(int argc, char** argv)
{
    printf("[INIT] FLTK -- START\n");

    auto window = Fl_Window(800, 600);
    auto box = Fl_Box(20, 40, 300, 100, "Hello, FLTK!");

    box.box(FL_UP_BOX);
    box.labelfont(FL_BOLD + FL_ITALIC);
    box.labelsize(36);
    box.labeltype(FL_SHADOW_LABEL);

    window.end();
    window.show(argc, argv);

    printf("[INIT] FLTK -- OK\n");

    return Fl::run();
}
