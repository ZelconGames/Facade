#ifndef FACADE_CONTROLLER_COMPONENT_H
#define FACADE_CONTROLLER_COMPONENT_H

#include "Agent.h"

#include <Scene/Component.hpp>

#include <BulletCollision/CollisionShapes/btConvexHullShape.h>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>

#include <QString>

#include <memory>

using namespace dt;
using namespace std;

class FacadeControllerComponent : public Component
{
    Q_OBJECT
public:
    /**
      * Note: 1 node can only have 1 controller.
      */
    FacadeControllerComponent(Agent* agent);

    void OnInitialize();
    void OnEnable();
    void OnDisable();
    void OnDeinitialize();
    void OnUpdate(double time_diff);

    /**
      * Sets the speed the player moves at.
      * @param move_speed The maximum speed, in units per second.
      */
    void setMoveSpeed(float move_speed);

    /**
      * Gets the speed the player moves at.
      * @returns The player speed, in units per second.
      */

    float getMoveSpeed() const;
    /**
      * Sets whether the character can jump or not.
      * @param jump_enabled Whether the character can jump or not.
      */

    void setJumpEnabled(bool jump_enabled);

    /**
      * Gets whether the character can jump or not.
      * @returns Whether the character can jump or not.
      */
    bool getJumpEnabled() const;

    Agent* getAgent() const;

    void setAgent(Agent* agent);

private:
    void _OnMoveChange(Ogre::Vector3 direction);

    void _OnJump();

    void _OnLook(const Ogre::Radian& pitch, const Ogre::Radian& yaw, const Ogre::Radian& roll);

    shared_ptr<Agent> mAgent;                                     //!< The command interpreter.
    shared_ptr<btKinematicCharacterController> mBtController;     //!< The bullet's built-in character controller.
    shared_ptr<btPairCachingGhostObject> mBtGhostObject;          //!< The bullet's ghost object.;
    btVector3 mMove;                                              //!< Used to keep track of the movement direction.
    float mMoveSpeed;                                             //!< The speed to move at. Default: 5.0. In units per second.
    bool mJumpEnabled;                                            //!< Whether the character can jump or not.
};

#endif
