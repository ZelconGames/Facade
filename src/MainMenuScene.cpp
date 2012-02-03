#include "SceneLoaderTest.h"

#include "SceneLoader.h"

#include <Core/ResourceManager.hpp>

void Main::OnInitialize() {
    dt::ResourceManager::Get()->AddDataPath(QDir("F:\\"));
    dt::ResourceManager::Get()->AddResourceLocation("","FileSystem");
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    dt::Scene* mainmenuscene = AddScene(new dt::Scene("MainMenuScene"));
}

void Main::UpdateStateFrame(double simulation_frame_time) {
}