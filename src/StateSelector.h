#ifndef STATE_SELECTOR_H
#define STATE_SELECTOR_H
#pragma once

#include <memory>

class StateSelector
{
public:
    enum StateCode
    {
        MAIN_MENU,
        OPTION,
        SELECT_LEVEL
    };

    ~StateSelector();

    static StateSelector* getInstance();

    bool Select(const StateCode& state_code);

private:
    StateSelector();

    static std::shared_ptr<StateSelector> mInstance;
};

#endif
