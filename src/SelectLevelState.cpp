#include "SelectLevelState.h"
#include "StateSelector.h"

#include <Graphics/CameraComponent.hpp>
#include <Graphics/TextComponent.hpp>
#include <Gui/GuiManager.hpp>

#include <OgreFontManager.h>

void SelectLevelState::OnInitialize()
{
    Scene* scene = AddScene(new Scene("SelectLevel"));

    Node* camnode = scene->AddChildNode(new dt::Node("camnode"));
    camnode->SetPosition(Ogre::Vector3(0, 0, 10));
    camnode->AddComponent(new dt::CameraComponent("cam"))->LookAt(Ogre::Vector3(0, 0, 0));
    
    //************************************************************
    //The following lines are for test purpose only.
    //Todo: Replace them with the actual content.
    Ogre::FontManager::getSingleton().load("DejaVuSans", "General");

    Node* node1 = scene->AddChildNode(new dt::Node("node1"));
    dt::TextComponent* text1 = node1->AddComponent(new dt::TextComponent("Select Level", "text1"));
    text1->SetBackgroundMaterial("TextOverlayBackground");
    text1->SetColor(Ogre::ColourValue::White);
    text1->SetFont("DejaVuSans");
    text1->SetFontSize(72);
    text1->SetPadding(Ogre::Vector2(20, 20));

    GuiRootWindow& rootWindow = GuiManager::Get()->GetRootWindow();
    mReturnButton = rootWindow.AddChildWidget<GuiButton>(new GuiButton("return"));

    mReturnButton->SetPosition(100, 100);
    mReturnButton->SetSize(250, 100);
    mReturnButton->SetCaption("Return");
    dynamic_cast<MyGUI::Button*>(mReturnButton->GetMyGUIWidget())->eventMouseButtonClick
        += MyGUI::newDelegate(this, &SelectLevelState::OnReturnClick);
    //************************************************************
}

void SelectLevelState::OnReturnClick(MyGUI::Widget* sender)
{
    StateSelector::GetInstance()->Select(StateSelector::MAIN_MENU);
}

void SelectLevelState::UpdateStateFrame(double simulationFrameTime)
{
}