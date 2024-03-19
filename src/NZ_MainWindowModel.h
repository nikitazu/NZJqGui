#pragma once

#include <string>

#include "NZ_JqProcess.h"

class NZ_MainWindowModel
{
public:
    std::string json_input = "";
    std::string query_input = "";
    std::string output = "";
    bool is_title_toggled = false;

    void toggle_title()
    {
        is_title_toggled = !is_title_toggled;
    }

    void submit_input()
    {
        if (json_input.length() > 0 && query_input.length() > 0) {

            if (json_input == "[]" && query_input == ".[]") {
                output = "[WRN] Не надо такое вводить, если JQ не напечатает в выходной пайп, то программа зависнет :(";
            }
            else {
                output = NZ_JqProcess::run(json_input, query_input);
            }
        }
    }
};
