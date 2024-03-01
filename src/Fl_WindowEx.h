#pragma once

#include "lib/fltk-1.3.9/FL/Fl.H"
#include "lib/fltk-1.3.9/FL/Fl_Window.H"

class Fl_WindowEx
{
public:
    static void set_position_center_screen(Fl_Window& window)
    {
        int window_w = window.w();
        int window_h = window.h();

        int screen_x;
        int screen_y;
        int screen_w;
        int screen_h;

        Fl::screen_work_area(screen_x, screen_y, screen_w, screen_h);

        int new_window_position_x = screen_w / 2 - window_w / 2;
        int new_window_position_y = screen_h / 2 - window_h / 2;

        window.position(new_window_position_x, new_window_position_y);
    }
};
