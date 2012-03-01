#include "HumanAgent.h"

#include <Utils/Logger.hpp>

HumanAgent::HumanAgent() {}

HumanAgent::~HumanAgent() {}

bool HumanAgent::OnInitialize()
{
    bool result = true;

    if(!QObject::connect(InputManager::Get(), SIGNAL(sPressed(dt::InputManager::InputCode, const OIS::EventArg&)), 
        this, SLOT(_HandleButtonDown(dt::InputManager::InputCode, const OIS::EventArg&))))
    {
            Logger::Get().Error("Failed to connect signal sKeyPressed.");
            result = false;
    }
    if(!QObject::connect(InputManager::Get(), SIGNAL(sReleased(dt::InputManager::InputCode, const OIS::EventArg&)), 
        this, SLOT(_HandleButtonUp(dt::InputManager::InputCode, const OIS::EventArg&))))
    {
            Logger::Get().Error("Failed to connect signal sKeyReleased.");
            result = false;
    }
    if(!QObject::connect(InputManager::Get(), SIGNAL(sMouseMoved(const OIS::MouseEvent&)), 
        this, SLOT(_HandleMouseMove(const OIS::MouseEvent&))))
    {
            Logger::Get().Error("Failed to connect signal sMouseMoved.");
            result = false;
    }

    return result;
}

bool HumanAgent::OnDeinitialize()
{
    bool result = true;

    if(!QObject::disconnect(this, SLOT(_HandleButtonDown(dt::InputManager::InputCode, const OIS::EventArg&))))
    {
        Logger::Get().Error("Failed to disconnect signal sKeyPressed.");
        result = false;
    }
    if(!QObject::disconnect(this, SLOT(_HandleButtonUp(dt::InputManager::InputCode, const OIS::EventArg&))))
    {
        Logger::Get().Error("Failed to disconnect signal sKeyReleased.");
        result = false;
    }
    if(!QObject::disconnect(this, SLOT(_HandleMouseMove(const OIS::MouseEvent&))))
    {
        Logger::Get().Error("Failed to disconnect signal sMouseMoved.");
        result = false;
    }

    return result;
}

void HumanAgent::OnUpdate(double time_diff) {}

void HumanAgent::_HandleButtonDown(dt::InputManager::InputCode input_code, const OIS::EventArg& event)
{

}

void HumanAgent::_HandleButtonUp(dt::InputManager::InputCode input_code, const OIS::EventArg& event)
{
}

void HumanAgent::_HandleMouseMove(const OIS::MouseEvent& event)
{
    float factor = mMouseSensitivity * -0.01;

    float dx = event.state.X.rel * factor;
    float dy = event.state.Y.rel * factor * (mMouseYInversed ? -1 : 1);

    if(dx != 0 || dy != 0)
    {
        emit sLook(Ogre::Radian(dy), Ogre::Radian(dx), Ogre::Radian(0.0f));
    }
}