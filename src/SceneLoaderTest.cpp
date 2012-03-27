#include "SceneLoaderTest.h"

#include "SceneLoader.h"

#include <Core/ResourceManager.hpp>

void Main::onInitialize()
{
    {
        QDir dir(QCoreApplication::applicationDirPath());
        while(!dir.isRoot()) {
            QDir data(dir.absolutePath() + "/externals/ducttape-engine");
            if(data.exists()) {
                ResourceManager::get()->addDataPath(data);

                break;
            }
            dir.cdUp();
        }
    }
    dt::ResourceManager::get()->addResourceLocation("","FileSystem");
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    dt::Scene* scene = nullptr;
    scene = SceneLoader::LoadScene(Utils::toString(scenefile));
    if(scene)
        addScene(scene);
}

void Main::updateStateFrame(double simulation_frame_time)
{
}

void Main::setFile(std::string file) {
    scenefile = file;
    Logger::get().debug("Setting scene file: " + Utils::toString(scenefile));
}
