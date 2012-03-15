#include "KeySettings.h"

KeySettings::KeySettings()
{
    mKeyMap[FORWARD] = pair<QString, InputManager::InputCode>("Forward", InputManager::KC_W);
    mKeyMap[BACKWARD] = pair<QString, InputManager::InputCode>("Backward", InputManager::KC_S);
    mKeyMap[LEFTWARD] = pair<QString, InputManager::InputCode>("Leftward", InputManager::KC_A);
    mKeyMap[RIGHTWARD] = pair<QString, InputManager::InputCode>("Rightward", InputManager::KC_D);
    mKeyMap[JUMP] = pair<QString, InputManager::InputCode>("Jump", InputManager::KC_SPACE);
    mKeyMap[DUCK] = pair<QString, InputManager::InputCode>("Duck", InputManager::KC_LCONTROL);
    mKeyMap[RELEASE_NANO] = pair<QString, InputManager::InputCode>("Release_Nano", InputManager::MC_RIGHT);
    mKeyMap[RECALL_NANO] = pair<QString, InputManager::InputCode>("Recall_Nano", InputManager::MC_LEFT);
    mKeyMap[ZOOM] = pair<QString, InputManager::InputCode>("Zoom", InputManager::MC_MIDDLE);
    mKeyMap[ACTIVATE] = pair<QString, InputManager::InputCode>("Activate", InputManager::KC_E);
}

void KeySettings::SetKey(Function function, InputManager::InputCode key)
{
    mKeyMap[function].second = key;
}

InputManager::InputCode KeySettings::GetKey(Function function) const
{
    return mKeyMap.at(function).second;
}

QString KeySettings::GetName(Function function) const
{
    return mKeyMap.at(function).first;
}

KeySettings::Function KeySettings::Begin() const
{
    return FORWARD;
}

KeySettings::Function KeySettings::End() const
{
    return ACTIVATE;
}