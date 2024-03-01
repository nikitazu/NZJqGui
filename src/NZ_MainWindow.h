#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Output.H>

class NZ_MainWindow : public Fl_Double_Window
{
public:
    void* controller = nullptr;

    Fl_Box* title_box = nullptr;
    Fl_Multiline_Output* output = nullptr;
    Fl_Input* input = nullptr;
    Fl_Button* submit_button = nullptr;

    NZ_MainWindow(int width, int height, const char* title)
        : Fl_Double_Window(width, height, title)
    {
        title_box = new Fl_Box(20, 20, 300, 100, "Привет, FLTK!");

        title_box->box(FL_UP_BOX);
        title_box->labelfont(FL_BOLD + FL_ITALIC);
        title_box->labelsize(36);
        title_box->labeltype(FL_NORMAL_LABEL);
        title_box->color(FL_RED);

        output = new Fl_Multiline_Output(100, 140, 800 - 200, 200, "Журнал");
        input = new Fl_Input(100, 340, 800 - 200, 25, "Ввод");
        submit_button = new Fl_Button(100, 380, 300, 25, "Отправить");
    }

    ~NZ_MainWindow() {
        if (submit_button != nullptr) { delete submit_button; submit_button = nullptr; }
        if (input != nullptr) { delete input; input = nullptr; }
        if (output != nullptr) { delete output; output = nullptr; }
        if (title_box != nullptr) { delete title_box; title_box = nullptr; }
    }
};
