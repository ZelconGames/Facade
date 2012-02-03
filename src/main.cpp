#include "SceneLoaderTest.h"

#include <Scene/Game.hpp>

int main(int argc, char** argv) {
    dt::Game game;
    game.Run(new Main(), argc, argv);

    return 0;
}