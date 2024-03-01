#include <stdio.h>
#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Window.H>

#include "Fl_WindowEx.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void submit_cb(Fl_Widget* w, void* v);

Fl_Box* gpBox = nullptr;
Fl_Multiline_Output* gpOutput = nullptr;
Fl_Input* gpInput = nullptr;

int main(int argc, char** argv)
{
    auto window = Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Привет, FLTK [ v0.1.0 ]");
    auto box = Fl_Box(20, 20, 300, 100, "Привет, FLTK!");

    gpBox = &box;

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

    gpOutput = &output;
    gpInput = &input;

    submit.callback(submit_cb);

    window.end();
    window.show(argc, argv);

    return Fl::run();
}

void submit_cb(Fl_Widget* w, void* v)
{
    if (gpBox != nullptr) {
        auto new_color = gpBox->color() == FL_RED ? FL_WHITE : FL_RED;
        gpBox->color(new_color);
        gpBox->redraw();
    }

    if (gpInput != nullptr && gpOutput != nullptr) {
        auto input_string = std::string(gpInput->value());
        auto output_string = std::string(gpOutput->value());

        auto combined_string =
            output_string.length() > 0
            ? output_string + "\n" + input_string
            : input_string;

        gpOutput->value(combined_string.c_str());
        gpInput->value("");
    }
}
