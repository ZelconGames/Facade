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
    void onInitialize();
    
    void updateStateFrame(double simulationFrameTime);

    void onOptionClick(MyGUI::Widget* sender);

    void onSelectLevelClick(MyGUI::Widget* sender);

private:
    std::shared_ptr<GuiButton> mOptionButton;
    std::shared_ptr<GuiButton> mSelectLevelButton;
};

#endif
