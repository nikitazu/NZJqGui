#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Window.H>

#include "Fl_WindowEx.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, char** argv)
{
    auto window = Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Привет, FLTK [ v0.1.0 ]");
    auto box = Fl_Box(20, 20, 300, 100, "Привет, FLTK!");

    Fl_WindowEx::set_position_center_screen(window);
    window.color(FL_CYAN);

    box.box(FL_UP_BOX);
    box.labelfont(FL_BOLD + FL_ITALIC);
    box.labelsize(36);
    box.labeltype(FL_NORMAL_LABEL);
    box.color(FL_RED);

    auto output = Fl_Multiline_Output(100, 140, 800 - 200, 200, "Журнал");
    auto input = Fl_Input(100, 340, 800 - 200, 25, "Ввод");
    auto submit = Fl_Button(100, 380, 300, 25, "Отправить");

    window.end();
    window.show(argc, argv);

    return Fl::run();
}
