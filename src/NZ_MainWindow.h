#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Pack.H>

class NZ_MainWindow : public Fl_Double_Window
{
public:
    void* controller = nullptr;

    Fl_Pack* main_pack = nullptr;
    Fl_Multiline_Input* json_input = nullptr;
    Fl_Input* query_input = nullptr;
    Fl_Button* submit_button = nullptr;
    Fl_Multiline_Output* output = nullptr;

    NZ_MainWindow(int width, int height, const char* title)
        : Fl_Double_Window(width, height, title)
    {
        int main_margin = 8;
        int main_x = 80;

        main_pack = new Fl_Pack(main_x, main_margin, width - main_x - main_margin, height - main_margin * 2, nullptr);
        json_input = new Fl_Multiline_Input(0, 0, 0, 300, "JSON");
        query_input = new Fl_Input(0, 0, 0, 25, "Запрос");
        submit_button = new Fl_Button(0, 0, 0, 25, "Отправить");
        output = new Fl_Multiline_Output(0, 0, 0, 400, "Результат");
        main_pack->end();
    }

    ~NZ_MainWindow() {
        if (submit_button != nullptr) { delete submit_button; submit_button = nullptr; }
        if (json_input != nullptr) { delete json_input; json_input = nullptr; }
        if (query_input != nullptr) { delete query_input; query_input = nullptr; }
        if (output != nullptr) { delete output; output = nullptr; }
    }
};
