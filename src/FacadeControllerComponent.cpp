#include "FacadeControllerComponent.h"

#include <Scene/Node.hpp>
#include <Scene/Scene.hpp>
#include <Physics/PhysicsWorld.hpp>

#include <BtOgreGP.h>
#include <BtOgrePG.h>

FacadeControllerComponent::FacadeControllerComponent(Agent* agent)
    : Component("controller"),
      mAgent(agent),
      mBtController(nullptr),
      mBtGhostObject(nullptr),
      mMove(0, 0, 0),
      mMoveSpeed(0.0f),
      mJumpEnabled(true) {}

void FacadeControllerComponent::OnInitialize()
{
    btTransform  start_trans;
    start_trans.setIdentity();
    start_trans.setOrigin(BtOgre::Convert::toBullet(getNode()->getPosition(Node::SCENE)));
    start_trans.setRotation(BtOgre::Convert::toBullet(getNode()->getRotation(Node::SCENE)));

    btScalar character_height = 1.75;
    btScalar character_width = 0.44;
    btConvexShape* capsule = new btCapsuleShape(character_width, character_height);

    mBtGhostObject = std::shared_ptr<btPairCachingGhostObject>(new btPairCachingGhostObject());
    mBtGhostObject->setWorldTransform(start_trans);
    mBtGhostObject->setCollisionShape(capsule);
    mBtGhostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
    mBtGhostObject->setUserPointer(nullptr);
    mBtController = std::shared_ptr<btKinematicCharacterController>
        (new btKinematicCharacterController(mBtGhostObject.get(), capsule, 1));

    getNode()->getScene()->getPhysicsWorld()->getBulletWorld()->addCollisionObject(mBtGhostObject.get());
    getNode()->getScene()->getPhysicsWorld()->getBulletWorld()->addAction(mBtController.get());

    Agent* agent = mAgent.get();
    bool result = true;

    if(agent != nullptr)
    {
        if(agent->OnInitialize())
        {
            if(!QObject::connect(agent, SIGNAL(sMove(Ogre::Vector3)), this, SLOT(_OnMoveChange(Ogre::Vector3))))
            {
                Logger::get().error("Failed to connect signal sMove.");
                result = false;
            }
            if(!QObject::connect(agent, SIGNAL(sLook(const Ogre::Radian&, const Ogre::Radian&, const Ogre::Radian&)), 
                                  this, SLOT(_OnLook(const Ogre::Radian&, const Ogre::Radian&, const Ogre::Radian&))))
            {
                Logger::get().error("Failed to connect signal sLook.");
                result = false;
            }
            if(!QObject::connect(agent, SIGNAL(sJump(bool)), this, SLOT(_OnJump())))
            {
                Logger::get().error("Failed to connect signal sJump.");
                result = false;
            }
        }
        else
        {
            result = false;
        }
    }

    if(!result)
    {
        Logger::get().error(QString("Failed to connect one or more signals for ") + this->getNode()->getName() + ".");
    }
}

void FacadeControllerComponent::OnEnable()
{
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(BtOgre::Convert::toBullet(getNode()->getPosition(Node::SCENE)));
    transform.setRotation(BtOgre::Convert::toBullet(getNode()->getRotation(Node::SCENE)));

    mBtGhostObject->setWorldTransform(transform);
    getNode()->getScene()->getPhysicsWorld()->getBulletWorld()->addCollisionObject(mBtGhostObject.get());
}

void FacadeControllerComponent::OnDisable()
{
    getNode()->getScene()->getPhysicsWorld()->getBulletWorld()->removeCollisionObject(mBtGhostObject.get());
}

void FacadeControllerComponent::OnUpdate(double time_diff)
{
    static Ogre::Vector3 move;
    static Ogre::Quaternion quaternion;
    static btTransform trans;

    quaternion = Ogre::Quaternion(getNode()->getRotation().getYaw(), Ogre::Vector3(0.0, 1.0, 0.0));
    move = quaternion * BtOgre::Convert::toOgre(mMove) * mMoveSpeed;
    mBtController->setVelocityForTimeInterval(BtOgre::Convert::toBullet(move), 0.5);

    trans = mBtGhostObject->getWorldTransform();

    getNode()->setPosition(BtOgre::Convert::toOgre(trans.getOrigin()), Node::SCENE);

    mAgent->OnUpdate(time_diff);
}

void FacadeControllerComponent::OnDeinitialize()
{
    mAgent->OnDeinitialize();
}

void FacadeControllerComponent::setMoveSpeed(float move_speed)
{
    mMoveSpeed = move_speed;
}

float FacadeControllerComponent::getMoveSpeed() const
{
    return mMoveSpeed;
}

void FacadeControllerComponent::setJumpEnabled(bool jump_enabled)
{
    mJumpEnabled = jump_enabled;
}

bool FacadeControllerComponent::getJumpEnabled() const
{
    return mJumpEnabled;
}

Agent* FacadeControllerComponent::getAgent() const
{
    return mAgent.get();
}

void FacadeControllerComponent::setAgent(Agent* agent)
{
    mAgent.reset(agent);
}

void FacadeControllerComponent::_OnMoveChange(Ogre::Vector3 direction)
{
    mMove = BtOgre::Convert::toBullet(direction);
}

void FacadeControllerComponent::_OnJump()
{
    if(mJumpEnabled && mBtController->onGround())
    {
        mBtController->jump();
    }
}

void FacadeControllerComponent::_OnLook(const Ogre::Radian& pitch, const Ogre::Radian& yaw, const Ogre::Radian& roll)
{
    Ogre::Matrix3 orientMatrix;
    getNode()->getRotation().ToRotationMatrix(orientMatrix);

    Ogre::Radian old_yaw, old_pitch, old_roll;
    orientMatrix.ToEulerAnglesYXZ(old_yaw, old_pitch, old_roll);

    old_pitch += pitch;
    old_yaw += yaw;
    old_roll += roll;

    // do not let it look completely vertical, or the yaw will break
    if(old_pitch > Ogre::Degree(89.9))
        old_pitch = Ogre::Degree(89.9);

    if(old_pitch < Ogre::Degree(-89.9))
        old_pitch = Ogre::Degree(-89.9);

    orientMatrix.FromEulerAnglesYXZ(old_yaw, old_pitch, old_roll);

    Ogre::Quaternion rot;
    rot.FromRotationMatrix(orientMatrix);
    getNode()->setRotation(rot);
}
