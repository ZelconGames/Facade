#ifndef AGENT_H
#define AGENT_H

#include <Input/InputManager.hpp>

#include <OGRE/OgreVector3.h>
#include <OGRE/OgreMath.h>
#include <OGRE/OgreQuaternion.h>

#include <QObject>

/**
  * A base class for hunman player and AI player.
  */
class Agent : public QObject
{
    Q_OBJECT
public:
    Agent();

    void SetEnabled(bool is_enabled);

    virtual bool OnInitialize() = 0;

    virtual bool OnDeinitialize() = 0;

    virtual void OnUpdate(double time_diff) = 0;

    bool IsEnabled() const;

signals:
    void sMove(Ogre::Vector3 direction);

    void sStop();

    void sLook(const Ogre::Radian& pitch, const Ogre::Radian& yaw, const Ogre::Radian& roll);

    void sJump(bool is_key_down);

    void sDuck(bool is_key_down);

    void sActivate(bool is_key_down);

    void sRecallNano(bool is_key_down);

    void sReleaseNano(bool is_key_down);

    void sZoom(bool is_key_down);  //Placeholder.

protected:
    bool mIsEnabled;
};

#endif