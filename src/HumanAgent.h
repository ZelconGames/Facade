#ifndef HUMAN_AGENT_H
#define HUMAN_AGENT_H

#include "Agent.h"

#include <Input/InputManager.hpp>

using namespace dt;

class HumanAgent : public Agent
{
    Q_OBJECT
public:
    HumanAgent();

    bool OnInitialize();

    bool OnDeinitialize();

    void OnUpdate(double time_diff);

    ~HumanAgent();

private slots:
    void _HandleButtonDown(dt::InputManager::InputCode input_code, const OIS::EventArg& event);

    void _HandleButtonUp(dt::InputManager::InputCode input_code, const OIS::EventArg& event);

    void _HandleMouseMove(const OIS::MouseEvent& event);

private:
    bool mMouseYInversed;
    float mMouseSensitivity;
};

#endif