#include "Agent.h"

#include <Input/InputManager.hpp>

Agent::Agent() : mIsEnabled(true) {}

bool Agent::IsEnabled() const
{
    return mIsEnabled;
}

void Agent::SetEnabled(bool is_enabled)
{
    if(mIsEnabled != is_enabled)
        mIsEnabled = is_enabled;
}