#include "SceneLoaderTest.h"
#include "StateSelector.h"

#include <Scene/Game.hpp>
#include <Core/ResourceManager.hpp>

using namespace dt;

int main(int argc, char** argv) 
{
    Game game;
    StateSelector::Initialize();
    
    game.Run(new Main(), argc, argv);

    return 0;
}