#include "SelectLevelState.h"
#include "StateSelector.h"

#include <Graphics/CameraComponent.hpp>
#include <Graphics/TextComponent.hpp>
#include <Gui/GuiManager.hpp>

#include <OgreFontManager.h>

void SelectLevelState::onInitialize()
{
    auto scene = addScene(new Scene("SelectLevel"));

    auto camnode = scene->addChildNode(new dt::Node("camnode"));
    camnode->setPosition(Ogre::Vector3(0, 0, 10));
    camnode->addComponent(new dt::CameraComponent("cam"))->lookAt(Ogre::Vector3(0, 0, 0));
    
    //************************************************************
    //The following lines are for test purpose only.
    //Todo: Replace them with the actual content.
    Ogre::FontManager::getSingleton().load("DejaVuSans", "General");

    auto node1 = scene->addChildNode(new dt::Node("node1"));
    auto text1 = node1->addComponent(new dt::TextComponent("Select Level", "text1"));
    text1->setBackgroundMaterial("TextOverlayBackground");
    text1->setColor(Ogre::ColourValue::White);
    text1->setFont("DejaVuSans");
    text1->setFontSize(72);
    text1->setPadding(Ogre::Vector2(20, 20));

    GuiRootWindow& rootWindow = GuiManager::get()->getRootWindow();
    mReturnButton = rootWindow.addChildWidget<GuiButton>(new GuiButton("return"));

    mReturnButton->setPosition(100, 100);
    mReturnButton->setSize(250, 100);
    mReturnButton->setCaption("Return");
    dynamic_cast<MyGUI::Button*>(mReturnButton->getMyGUIWidget())->eventMouseButtonClick
        += MyGUI::newDelegate(this, &SelectLevelState::onReturnClick);
    //************************************************************
}

void SelectLevelState::onReturnClick(MyGUI::Widget* sender)
{
    StateSelector::getInstance()->Select(StateSelector::MAIN_MENU);
}

void SelectLevelState::updateStateFrame(double simulationFrameTime)
{
}
