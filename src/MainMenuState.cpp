#include "MainMenuState.h"

#include "StateSelector.h"

#include <Core/ResourceManager.hpp>
#include <Scene/StateManager.hpp>
#include <Gui/GuiManager.hpp>
#include <Gui/GuiRootWindow.hpp>
#include <Graphics/CameraComponent.hpp>

#include <QCoreApplication>

void MainMenuState::onInitialize()
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
    ResourceManager::get()->addResourceLocation("data/gui","FileSystem", true);
    ResourceManager::get()->addResourceLocation("data", "FileSystem", true);

    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    auto scene = addScene(new Scene("MainMenu"));

    GuiManager::get()->setSceneManager(scene->getSceneManager());

    auto camnode = scene->addChildNode(new Node("camnode"));
    camnode->setPosition(Ogre::Vector3(0, 5, 10));
    camnode->addComponent(new CameraComponent("cam"))->lookAt(Ogre::Vector3(0, 0, 0));;

    GuiRootWindow& rootWindow = GuiManager::get()->getRootWindow();

    //********************************************************************************
    //The following lines are for test purpose only.
    //Todo: Refine them for actual use.
    mOptionButton = rootWindow.addChildWidget<GuiButton>(new GuiButton("option"));
    mOptionButton->setCaption("Option");
    mOptionButton->setSize(250, 100);
    mOptionButton->setPosition(100, 100);
    dynamic_cast<MyGUI::Button*>(mOptionButton->getMyGUIWidget())->eventMouseButtonClick
        += MyGUI::newDelegate(this, &MainMenuState::onOptionClick);
    
    mSelectLevelButton = rootWindow.addChildWidget<GuiButton>(new GuiButton("select_level"));
    mSelectLevelButton->setCaption("Select Level");
    mSelectLevelButton->setSize(250, 100);
    mSelectLevelButton->setPosition(100, 220);
    dynamic_cast<MyGUI::Button*>(mSelectLevelButton->getMyGUIWidget())->eventMouseButtonClick
        += MyGUI::newDelegate(this, &MainMenuState::onSelectLevelClick);
    //**********************************************************************************
}

void MainMenuState::onSelectLevelClick(MyGUI::Widget* sender)
{
    StateSelector::getInstance()->Select(StateSelector::SELECT_LEVEL);
}

void MainMenuState::onOptionClick(MyGUI::Widget* sender)
{
    StateSelector::getInstance()->Select(StateSelector::OPTION);
}

void MainMenuState::updateStateFrame(double simulationFrameTime)
{
}
