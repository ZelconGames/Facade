#ifndef OPTION_STATE_H
#define OPTION_STATE_H
#pragma once

#include <Scene/State.hpp>
#include <Gui/GuiButton.hpp>

#include <memory>

using namespace dt;
using namespace std;

class OptionState : public State
{
    Q_OBJECT
public:
    void onInitialize();

    void updateStateFrame(double simulationFrameTime);

    void onReturnClick(MyGUI::Widget* sender);

private:
    std::shared_ptr<GuiButton> mReturnButton;
};

#endif
