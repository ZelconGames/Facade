#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H
#pragma once

#include <Scene/State.hpp>
#include <Gui/GuiButton.hpp>

#include <memory>

using namespace dt;
using namespace std;

class MainMenuState : public State
{
    Q_OBJECT
public:
    void OnInitialize();
    
    void UpdateStateFrame(double simulationFrameTime);

    void OnOptionClick(MyGUI::Widget* sender);

    void OnSelectLevelClick(MyGUI::Widget* sender);

private:
    shared_ptr<GuiButton> mOptionButton;
    shared_ptr<GuiButton> mSelectLevelButton;
};

#endif