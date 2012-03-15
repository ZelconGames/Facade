#include "KeySettings.h"

KeySettings::KeySettings()
{
    mKeyMap[FORWARD] = InputManager::KC_W;
    mKeyMap[BACKWARD] = InputManager::KC_S;
    mKeyMap[LEFTWARD] = InputManager::KC_A;
    mKeyMap[RIGHTWARD] = InputManager::KC_D;
    mKeyMap[JUMP] = InputManager::KC_SPACE;
    mKeyMap[DUCK] = InputManager::KC_LCONTROL;
    mKeyMap[RELEASE_NANO] = InputManager::MC_RIGHT;
    mKeyMap[RECALL_NANO] = InputManager::MC_LEFT;
    mKeyMap[ZOOM] = InputManager::MC_MIDDLE;
    mKeyMap[ACTIVATE] = InputManager::KC_E;
}

void KeySettings::SetKey(Function function, InputManager::InputCode key)
{
    mKeyMap[function] = key;
}

InputManager::InputCode KeySettings::GetKey(Function function) const
{
    return mKeyMap.at(function);
}