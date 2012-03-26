#include "SceneLoaderTest.h"
#include "MainMenuState.h"
#include "StateSelector.h"

#include <Scene/Game.hpp>
#include <Core/ResourceManager.hpp>

using namespace dt;

int main(int argc, char** argv) 
{
    Game game;
    Main* main = new Main();
    if (argc > 1) {
        main->setFile(argv[1]);
    }

    game.run(main, argc, argv);

    return 0;
}
