#include "OptionState.h"
#include "StateSelector.h"

#include <Graphics/CameraComponent.hpp>
#include <Graphics/TextComponent.hpp>
#include <Gui/GuiManager.hpp>
#include <Core/ResourceManager.hpp>

#include <OgreFontManager.h>

void OptionState::onInitialize()
{
    ResourceManager::get()->addResourceLocation("gui","FileSystem", true);
    ResourceManager::get()->addResourceLocation("", "FileSystem", true);

    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    auto scene = addScene(new Scene("Option"));

    auto camnode = scene->addChildNode(new dt::Node("camnode"));
    camnode->setPosition(Ogre::Vector3(0, 0, 10));
    camnode->addComponent(new dt::CameraComponent("cam"))->lookAt(Ogre::Vector3(0, 0, 0));
    
    //************************************************************
    //The following lines are for test purpose only.
    //Todo: Replace them with the actual content.
    Ogre::FontManager::getSingleton().load("DejaVuSans", "General");

    auto node1 = scene->addChildNode(new dt::Node("node1"));
    auto text1 = node1->addComponent(new dt::TextComponent("Option", "text1"));
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
    mReturnButton->setVisible(true);
    dynamic_cast<MyGUI::Button*>(mReturnButton->getMyGUIWidget())->eventMouseButtonClick
        += MyGUI::newDelegate(this, &OptionState::onReturnClick);
    //************************************************************
}

void OptionState::onReturnClick(MyGUI::Widget* sender)
{
    StateSelector::getInstance()->Select(StateSelector::MAIN_MENU);
}

void OptionState::updateStateFrame(double simulationFrameTime)
{
}
