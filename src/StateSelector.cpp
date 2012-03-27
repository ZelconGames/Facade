#include "StateSelector.h"
#include "MainMenuState.h"
#include "OptionState.h"
#include "SelectLevelState.h"

#include <Scene/State.hpp>
#include <Scene/StateManager.hpp>

std::shared_ptr<StateSelector> StateSelector::mInstance = std::shared_ptr<StateSelector>(new StateSelector());

StateSelector::StateSelector()
{
}

StateSelector::~StateSelector()
{
}

StateSelector* StateSelector::getInstance()
{
    return mInstance.get();
}

bool StateSelector::Select(const StateCode& state_code)
{
    auto stateMgr = dt::StateManager::get();
    dt::State* state = nullptr;

    switch(state_code)
    {
    case MAIN_MENU:
        state = new MainMenuState();
        break;
    case OPTION:
        state = new OptionState();
        break;
    case SELECT_LEVEL:
        state = new SelectLevelState();
        break;
    default:
        return false;
    }

    if(stateMgr->getCurrentState())
    {
        stateMgr->pop();
    }
    stateMgr->setNewState(state);

    return true;
}
