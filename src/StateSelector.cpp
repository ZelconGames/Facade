#include "StateSelector.h"
#include "MainMenuState.h"
#include "OptionState.h"
#include "SelectLevelState.h"

#include <Scene/State.hpp>
#include <Scene/StateManager.hpp>

std::shared_ptr<StateSelector> StateSelector::mInstance = std::shared_ptr<StateSelector>(nullptr);

StateSelector::StateSelector()
{
}

StateSelector::~StateSelector()
{
}

void StateSelector::Initialize()
{
    if(mInstance.get() == nullptr)
    {
        mInstance = std::shared_ptr<StateSelector>(new StateSelector());
    }
}

std::shared_ptr<StateSelector> StateSelector::GetInstance()
{
    return mInstance;
}

bool StateSelector::Select(const StateCode& state_code)
{
    auto stateMgr = dt::StateManager::Get();
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

    if(stateMgr->GetCurrentState())
    {
        stateMgr->Pop();
    }
    stateMgr->SetNewState(state);

    return true;
}