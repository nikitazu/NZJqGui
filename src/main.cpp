#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include "Fl_WindowEx.h"
#include "NZ_MainWindow.h"
#include "NZ_MainWindowController.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, char** argv)
{
    auto window = NZ_MainWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Привет, FLTK [ v0.1.0 ]");
    Fl_WindowEx::set_position_center_screen(window);
    window.color(FL_CYAN);
    window.end();
    window.show(argc, argv);

    NZ_MainWindowModel model;
    NZ_MainWindowController controller;

    controller.init(&window, &model);

    return Fl::run();
}
