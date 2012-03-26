#ifndef SCENE_LOADER_TEST_H
#define SCENE_LOADER_TEST_H
#pragma once

#include <Scene/State.hpp>

class Main : public dt::State {
    Q_OBJECT
public:
    void onInitialize();
    void updateStateFrame(double simulation_frame_time);
    void setFile(std::string file);

private:
    std::string scenefile;
};

#endif
