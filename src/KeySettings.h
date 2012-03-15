#ifndef KEY_SETTINGS_H
#define KEY_SETTINGS_H

#include <Input/InputManager.hpp>

#include <map>

using namespace dt;
using namespace std;

class KeySettings
{
public:
    enum Function
    {
        FORWARD,
        BACKWARD,
        LEFTWARD,
        RIGHTWARD,
        JUMP,
        DUCK,
        RECALL_NANO,
        RELEASE_NANO,
        ZOOM,
        ACTIVATE
    };

    KeySettings();

    void SetKey(Function function, InputManager::InputCode key);

    InputManager::InputCode GetKey(Function function) const;

    QString GetName(Function function) const;

    Function Begin() const;

    Function End() const;

private:
    map<Function, pair<QString, InputManager::InputCode>> mKeyMap;
};

#endif