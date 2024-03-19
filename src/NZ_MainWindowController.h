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
        _model->json_input = _window->json_input->value();
        _model->query_input = _window->query_input->value();
        _model->output = _window->output->value();
    }

    void update_ui()
    {
        _window->output->value(_model->output.c_str());
        _window->json_input->value(_model->json_input.c_str());
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