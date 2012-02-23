#ifndef SCENE_LOADER_TEST_H
#define SCENE_LOADER_TEST_H
#pragma once

#include <Scene/State.hpp>

class Main : public dt::State {
    Q_OBJECT
public:
    void OnInitialize();
    void UpdateStateFrame(double simulation_frame_time);
    void SetFile(std::string file);

private:
    std::string scenefile;
};

#endif
