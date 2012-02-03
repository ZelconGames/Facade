#include "SceneLoaderTest.h"

#include "SceneLoader.h"

#include <Core/ResourceManager.hpp>

void Main::OnInitialize() {
    dt::ResourceManager::Get()->AddDataPath(QDir("D:\\"));
    dt::ResourceManager::Get()->AddResourceLocation("","FileSystem");
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    dt::Scene* scene = nullptr;
    scene = SceneLoader::LoadScene("D:\\test.scene");
    if(scene)
        AddScene(scene);
}

void Main::UpdateStateFrame(double simulation_frame_time) {
}