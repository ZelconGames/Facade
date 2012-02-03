#include "MainMenuState.h"
#include "StateSelector.h"

#include <Scene/Game.hpp>
#include <Core/ResourceManager.hpp>

using namespace dt;

int main(int argc, char** argv) {
    Game game;
    StateSelector::Initialize();
    
    game.Run(new MainMenuState(), argc, argv);

    return 0;
}