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
    Fl_Box* json_label = nullptr;
    Fl_Multiline_Input* json_input = nullptr;
    Fl_Pack* query_pack = nullptr;
    Fl_Box* query_label = nullptr;
    Fl_Input* query_input = nullptr;
    Fl_Button* submit_button = nullptr;
    Fl_Box* output_label = nullptr;
    Fl_Multiline_Output* output = nullptr;

    NZ_MainWindow(int width, int height, const char* title)
        : Fl_Double_Window(width, height, title)
    {
        int main_margin = 8;
        int main_width = width - main_margin * 2;
        int main_height = height - main_margin * 2;

        int line_height = 25;
        int multiline_height = 300;
        int last_multiline_height = main_height - line_height * 4 - multiline_height;

        main_pack = new Fl_Pack(main_margin, main_margin, main_width, main_height);
        json_label = new Fl_Box(0, 0, 100, line_height, "JSON");
        json_input = new Fl_Multiline_Input(0, 0, 0, multiline_height);

        query_label = new Fl_Box(0, 0, 100, line_height, "Запрос");
        query_pack = new Fl_Pack(0, 0, main_width, line_height);
        query_input = new Fl_Input(0, 0, main_width - 100, line_height);
        submit_button = new Fl_Button(0, 0, 100, line_height, "Отправить");
        query_pack->end();
        query_pack->type(Fl_Pack::HORIZONTAL);
        query_pack->spacing(4);

        output_label = new Fl_Box(0, 0, 100, line_height, "Результат");
        output = new Fl_Multiline_Output(0, 0, 0, last_multiline_height);
        main_pack->end();
    }

    ~NZ_MainWindow() {
        if (submit_button != nullptr) { delete submit_button; submit_button = nullptr; }
        if (json_label != nullptr) { delete json_label; json_label = nullptr; }
        if (json_input != nullptr) { delete json_input; json_input = nullptr; }
        if (query_label != nullptr) { delete query_label; query_label = nullptr; }
        if (query_input != nullptr) { delete query_input; query_input = nullptr; }
        if (output_label != nullptr) { delete output_label; output_label = nullptr; }
        if (output != nullptr) { delete output; output = nullptr; }
        if (query_pack != nullptr) { delete query_pack; query_pack = nullptr; }
        if (main_pack != nullptr) { delete main_pack; main_pack = nullptr; }
    }
};
