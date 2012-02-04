#include "MainMenuState.h"

#include "StateSelector.h"

#include <Core/ResourceManager.hpp>
#include <Scene/StateManager.hpp>
#include <Gui/GuiManager.hpp>
#include <Graphics/CameraComponent.hpp>

#include <QCoreApplication>

void MainMenuState::OnInitialize()
{
    {
        QDir dir(QCoreApplication::applicationDirPath());
        while(!dir.isRoot()) {
            QDir data(dir.absolutePath() + "/externals/ducttape-engine/data");
            if(data.exists()) {
                ResourceManager::Get()->AddDataPath(data);
                break;
            }
            dir.cdUp();
        }
    }
    ResourceManager::Get()->AddResourceLocation("gui","FileSystem", true);
    ResourceManager::Get()->AddResourceLocation("", "FileSystem", true);

    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    Scene* scene = AddScene(new Scene("MainMenu"));

    Node* camnode = scene->AddChildNode(new Node("camnode"));
    camnode->SetPosition(Ogre::Vector3(0, 5, 10));
    camnode->AddComponent(new CameraComponent("cam"))->LookAt(Ogre::Vector3(0, 0, 0));;

    GuiRootWindow& rootWindow = GuiManager::Get()->GetRootWindow();

    //********************************************************************************
    //The following lines are for test purpose only.
    //Todo: Refine them for actual use.
    mOptionButton = shared_ptr<GuiButton>(rootWindow.CreateChild<GuiButton>("option"));
    mOptionButton->SetCaption("Option");
    mOptionButton->SetSize(250, 100);
    mOptionButton->SetPosition(100, 100);
    dynamic_cast<MyGUI::Button*>(mOptionButton->GetMyGUIWidget())->eventMouseButtonClick
        += MyGUI::newDelegate(this, &MainMenuState::OnOptionClick);

    mSelectLevelButton = shared_ptr<GuiButton>(rootWindow.CreateChild<GuiButton>("select_level"));
    mSelectLevelButton->SetCaption("Select Level");
    mSelectLevelButton->SetSize(250, 100);
    mSelectLevelButton->SetPosition(100, 220);
    dynamic_cast<MyGUI::Button*>(mSelectLevelButton->GetMyGUIWidget())->eventMouseButtonClick
        += MyGUI::newDelegate(this, &MainMenuState::OnSelectLevelClick);
    //**********************************************************************************
}

void MainMenuState::OnSelectLevelClick(MyGUI::Widget* sender)
{
    StateSelector::GetInstance()->Select(StateSelector::SELECT_LEVEL);
}

void MainMenuState::OnOptionClick(MyGUI::Widget* sender)
{
    StateSelector::GetInstance()->Select(StateSelector::OPTION);
}

void MainMenuState::UpdateStateFrame(double simulationFrameTime)
{
}
