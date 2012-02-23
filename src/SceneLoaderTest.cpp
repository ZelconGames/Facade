#include "SceneLoaderTest.h"

#include "SceneLoader.h"

#include <Core/ResourceManager.hpp>

void Main::OnInitialize() 
{
    {
        QDir dir(QCoreApplication::applicationDirPath());
        while(!dir.isRoot()) {
            QDir data(dir.absolutePath() + "/externals/ducttape-engine");
            if(data.exists()) {
                ResourceManager::Get()->AddDataPath(data);

                break;
            }
            dir.cdUp();
        }
    }
    dt::ResourceManager::Get()->AddResourceLocation("","FileSystem");
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    dt::Scene* scene = nullptr;
    scene = SceneLoader::LoadScene(Utils::ToString(scenefile));
    if(scene)
        AddScene(scene);
}

void Main::UpdateStateFrame(double simulation_frame_time) 
{
}

void Main::SetFile(std::string file) {
    scenefile = file;
    Logger::Get().Debug("Setting scene file: " + Utils::ToString(scenefile));
}
