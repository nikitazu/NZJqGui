#pragma once

#include <string>

class NZ_MainWindowModel
{
public:
    std::string input = "";
    std::string output = "";
    bool is_title_toggled = false;

    void toggle_title()
    {
        is_title_toggled = !is_title_toggled;
    }

    void submit_input()
    {
        if (input.length() > 0) {
            output = output.length() > 0 ? output + "\n" + input : input;
            input.clear();
        }
    }
};
