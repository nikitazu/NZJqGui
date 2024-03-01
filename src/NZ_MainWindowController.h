#pragma once

#include "NZ_MainWindow.h"
#include "NZ_MainWindowModel.h"

class NZ_MainWindowController
{
private:
    NZ_MainWindow* _window = nullptr;
    NZ_MainWindowModel* _model = nullptr;

public:
    void init(NZ_MainWindow* window, NZ_MainWindowModel* model)
    {
        _window = window;
        _model = model;
        _window->controller = this;
        _window->submit_button->callback(submit_cb);
    }

private:
    void update_model()
    {
        _model->output = _window->output->value();
        _model->input = _window->input->value();
    }

    void update_ui()
    {
        _window->title_box->color(_model->is_title_toggled ? FL_RED : FL_WHITE);
        _window->title_box->redraw();

        _window->output->value(_model->output.c_str());
        _window->input->value(_model->input.c_str());
    }

    void on_submit_button_click()
    {
        _model->toggle_title();
        _model->submit_input();
    }

    static void submit_cb(Fl_Widget* w, void* v)
    {
        auto window = (NZ_MainWindow*)w->window();
        auto controller = (NZ_MainWindowController*)window->controller;

        controller->update_model();
        controller->on_submit_button_click();
        controller->update_ui();
    }
};