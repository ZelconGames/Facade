#ifndef SELECT_LEVEL_STATE_H
#define SELECT_LEVEL_STATE_H
#pragma once

#include <Gui/GuiButton.hpp>
#include <Scene/State.hpp>

#include <memory>

using namespace dt;
using namespace std;

class SelectLevelState : public State
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
