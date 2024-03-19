#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include "Fl_WindowEx.h"
#include "NZ_MainWindow.h"
#include "NZ_MainWindowController.h"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

int main(int argc, char** argv)
{
    auto window = NZ_MainWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "NZ JQ GUI [ v0.1.0 ]");
    Fl_WindowEx::set_position_center_screen(window);
    window.color(FL_WHITE);
    window.end();
    window.show(argc, argv);

    NZ_MainWindowModel model;
    NZ_MainWindowController controller;

    controller.init(&window, &model);

    return Fl::run();
}
