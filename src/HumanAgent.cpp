#include "HumanAgent.h"
#include "ConfigurationManager.h"

#include <Utils/Logger.hpp>

HumanAgent::HumanAgent() : mMove(0, 0, 0), mMouseYInversed(false), mMouseSensitivity(1.0) {}

HumanAgent::~HumanAgent() {}

bool HumanAgent::OnInitialize()
{
    bool result = true;

    if(!QObject::connect(InputManager::get(), SIGNAL(sPressed(dt::InputManager::InputCode, const OIS::EventArg&)), 
        this, SLOT(_HandleButtonDown(dt::InputManager::InputCode, const OIS::EventArg&))))
    {
            Logger::get().error("Failed to connect signal sKeyPressed.");
            result = false;
    }
    if(!QObject::connect(InputManager::get(), SIGNAL(sReleased(dt::InputManager::InputCode, const OIS::EventArg&)), 
        this, SLOT(_HandleButtonUp(dt::InputManager::InputCode, const OIS::EventArg&))))
    {
            Logger::get().error("Failed to connect signal sKeyReleased.");
            result = false;
    }
    if(!QObject::connect(InputManager::get(), SIGNAL(sMouseMoved(const OIS::MouseEvent&)), 
        this, SLOT(_HandleMouseMove(const OIS::MouseEvent&))))
    {
            Logger::get().error("Failed to connect signal sMouseMoved.");
            result = false;
    }

    return result;
}

bool HumanAgent::OnDeinitialize()
{
    bool result = true;

    if(!QObject::disconnect(this, SLOT(_HandleButtonDown(dt::InputManager::InputCode, const OIS::EventArg&))))
    {
        Logger::get().error("Failed to disconnect signal sKeyPressed.");
        result = false;
    }
    if(!QObject::disconnect(this, SLOT(_HandleButtonUp(dt::InputManager::InputCode, const OIS::EventArg&))))
    {
        Logger::get().error("Failed to disconnect signal sKeyReleased.");
        result = false;
    }
    if(!QObject::disconnect(this, SLOT(_HandleMouseMove(const OIS::MouseEvent&))))
    {
        Logger::get().error("Failed to disconnect signal sMouseMoved.");
        result = false;
    }

    return result;
}

void HumanAgent::OnUpdate(double time_diff) {}

void HumanAgent::_HandleButtonDown(dt::InputManager::InputCode input_code, const OIS::EventArg& event)
{
    KeySettings key_settings = ConfigurationManager::getInstance()->getKeySettings();

    if(input_code == key_settings.getKey(KeySettings::FORWARD))
    {
        mMove.z -= 1.0;
        mMove.normalise();

        emit sMove(mMove);
    }
    else if(input_code == key_settings.getKey(KeySettings::BACKWARD))
    {
        mMove.z += 1.0;
        mMove.normalise();

        emit sMove(mMove);
    }
    else if(input_code == key_settings.getKey(KeySettings::LEFTWARD))
    {
        mMove.x -= 1.0;
        mMove.normalise();

        emit sMove(mMove);
    }
    else if(input_code == key_settings.getKey(KeySettings::RIGHTWARD))
    {
        mMove.x += 1.0;
        mMove.normalise();

        emit sMove(mMove);
    }
    else if(input_code == key_settings.getKey(KeySettings::DUCK))
    {
        emit sDuck(true);
    }
    else if(input_code == key_settings.getKey(KeySettings::JUMP))
    {
        emit sJump(true);
    }
    else if(input_code == key_settings.getKey(KeySettings::ACTIVATE))
    {
        emit sActivate(true);
    }
    else if(input_code == key_settings.getKey(KeySettings::RECALL_NANO))
    {
        emit sRecallNano(true);
    }
    else if(input_code == key_settings.getKey(KeySettings::RELEASE_NANO))
    {
        emit sReleaseNano(true);
    }
    else if(input_code == key_settings.getKey(KeySettings::ZOOM))
    {
        emit sZoom(true);
    }
}

void HumanAgent::_HandleButtonUp(dt::InputManager::InputCode input_code, const OIS::EventArg& event)
{
    KeySettings key_settings = ConfigurationManager::getInstance()->getKeySettings();

    if(input_code == key_settings.getKey(KeySettings::FORWARD))
    {
        mMove.z += 1.0;
        mMove.normalise();

        emit sMove(mMove);
    }
    else if(input_code == key_settings.getKey(KeySettings::BACKWARD))
    {
        mMove.z -= 1.0;
        mMove.normalise();

        emit sMove(mMove);
    }
    else if(input_code == key_settings.getKey(KeySettings::LEFTWARD))
    {
        mMove.x += 1.0;
        mMove.normalise();

        emit sMove(mMove);
    }
    else if(input_code == key_settings.getKey(KeySettings::RIGHTWARD))
    {
        mMove.x -= 1.0;
        mMove.normalise();

        emit sMove(mMove);
    }
    else if(input_code == key_settings.getKey(KeySettings::DUCK))
    {
        emit sDuck(false);
    }
    else if(input_code == key_settings.getKey(KeySettings::JUMP))
    {
        emit sJump(false);
    }
    else if(input_code == key_settings.getKey(KeySettings::ACTIVATE))
    {
        emit sActivate(false);
    }
    else if(input_code == key_settings.getKey(KeySettings::RECALL_NANO))
    {
        emit sRecallNano(false);
    }
    else if(input_code == key_settings.getKey(KeySettings::RELEASE_NANO))
    {
        emit sReleaseNano(false);
    }
    else if(input_code == key_settings.getKey(KeySettings::ZOOM))
    {
        emit sZoom(false);
    }

    if(mMove.isZeroLength())
    {
        emit sStop();
    }
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