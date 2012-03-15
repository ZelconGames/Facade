#include "ConfigurationManager.h"

#include <Utils/Logger.hpp>
#include <Utils/Utils.hpp>

std::shared_ptr<ConfigurationManager> ConfigurationManager::mInstance = 
    std::shared_ptr<ConfigurationManager>(new ConfigurationManager());

ConfigurationManager::ConfigurationManager()
{
}

ConfigurationManager* ConfigurationManager::GetInstance()
{
    return mInstance.get();
}

bool ConfigurationManager::LoadConfig()
{
    QFile config_file(CONFIG_FILE);
    QDomDocument doc;

    // If the file doesn't exist...
    if(!config_file.open(QIODevice::ReadOnly))
    {
        Logger::Get().Info("The configuration file doesn't exist. Trying to create a new one.");
        
        if(!SaveConfig())
        {
            Logger::Get().Error("Failed to open the configuration file.");

            return false;
        }
        else
        {
            Logger::Get().Info("Created a new configuration file.");

            return true;
        }
    }

    // Else...
    if(doc.setContent(&config_file))
    {
        QDomElement root = doc.documentElement();

        // Only loads the key settings for now.
        // TODO: Add other loading stuff here.
        for(QDomElement config_node = root.firstChildElement() ; !config_node.isNull() ; config_node = config_node.nextSiblingElement())
        {
            QString tag_name = config_node.tagName();

            if(tag_name == KEY_SETTINGS)
            {
                _LoadKeySettings(config_node);
            }
        }
    }
    else
    {
        Logger::Get().Error("Failed to read from the configuration file.");

        return false;
    }

    return true;
}

KeySettings ConfigurationManager::GetKeySettings() const
{
    return mKeySettings;
}

void ConfigurationManager::SetKeySettings(KeySettings key_settings)
{
    mKeySettings = key_settings;
}

bool ConfigurationManager::SaveConfig() const
{
    QFile config_file(CONFIG_FILE);
    QDomDocument doc;

    if(!config_file.open(QIODevice::WriteOnly))
    {
        Logger::Get().Error("Cannot create the configuration file.");
        
        return false;
    }

    // The root.
    auto root = doc.createElement(CONFIG_ROOT);
    doc.appendChild(root);

    // Only saves the key settings for now.
    // TODO: Add other saving stuff here.
    root.appendChild(_SaveKeySettings(doc));

    // Save it to the file.
    QTextStream out(&config_file);
    out << doc.toString();

    // Close the file.
    config_file.close();

    return true;
}

void ConfigurationManager::_LoadKeySettings(const QDomElement& element)
{
    for(auto key_node = element.firstChildElement() ; !key_node.isNull() ; key_node = key_node.nextSiblingElement())
    {
        KeySettings::Function function_code = (KeySettings::Function)key_node.attribute(KEY_FUNCTION).toUInt();
        InputManager::InputCode input_code = (InputManager::InputCode)key_node.nodeValue().toUInt();

        mKeySettings.SetKey(function_code, input_code);
    }
}

QDomElement ConfigurationManager::_SaveKeySettings(QDomDocument& doc) const
{
    auto key_settings = doc.createElement(KEY_SETTINGS);
    auto forward = doc.createElement(KEY_FORWARD);
    auto backward = doc.createElement(KEY_BACKWARD);
    auto leftward = doc.createElement(KEY_LEFTWARD);
    auto rightward = doc.createElement(KEY_RIGHTWARD);
    auto jump = doc.createElement(KEY_JUMP);
    auto duck = doc.createElement(KEY_DUCK);
    auto activate = doc.createElement(KEY_ACTIVATE);
    auto recall_nano = doc.createElement(KEY_RECALL_NANO);
    auto release_nano = doc.createElement(KEY_RELEASE_NANO);
    auto zoom = doc.createElement(KEY_ZOOM);
    
    forward.setAttribute(KEY_FUNCTION, (unsigned)KeySettings::FORWARD);
    forward.setAttribute(KEY_CODE, (unsigned)mKeySettings.GetKey(KeySettings::FORWARD));
    key_settings.appendChild(forward);

    backward.setAttribute(KEY_FUNCTION, (unsigned)KeySettings::BACKWARD);
    backward.setAttribute(KEY_CODE, (unsigned)mKeySettings.GetKey(KeySettings::BACKWARD));
    key_settings.appendChild(backward);

    leftward.setAttribute(KEY_FUNCTION, (unsigned)KeySettings::LEFTWARD);
    leftward.setAttribute(KEY_CODE, (unsigned)mKeySettings.GetKey(KeySettings::LEFTWARD));
    key_settings.appendChild(leftward);

    rightward.setAttribute(KEY_FUNCTION, (unsigned)KeySettings::RIGHTWARD);
    rightward.setAttribute(KEY_CODE, (unsigned)mKeySettings.GetKey(KeySettings::RIGHTWARD));
    key_settings.appendChild(rightward);

    jump.setAttribute(KEY_FUNCTION, (unsigned)KeySettings::JUMP);
    jump.setAttribute(KEY_CODE, (unsigned)mKeySettings.GetKey(KeySettings::JUMP));
    key_settings.appendChild(jump);

    duck.setAttribute(KEY_FUNCTION, (unsigned)KeySettings::DUCK);
    duck.setAttribute(KEY_CODE, (unsigned)mKeySettings.GetKey(KeySettings::DUCK));
    key_settings.appendChild(duck);

    activate.setAttribute(KEY_FUNCTION, (unsigned)KeySettings::ACTIVATE);
    activate.setAttribute(KEY_CODE, (unsigned)mKeySettings.GetKey(KeySettings::ACTIVATE));
    key_settings.appendChild(activate);

    recall_nano.setAttribute(KEY_FUNCTION, (unsigned)KeySettings::RECALL_NANO);
    recall_nano.setAttribute(KEY_CODE, (unsigned)mKeySettings.GetKey(KeySettings::RECALL_NANO));
    key_settings.appendChild(recall_nano);

    release_nano.setAttribute(KEY_FUNCTION, (unsigned)KeySettings::RELEASE_NANO);
    release_nano.setAttribute(KEY_CODE, (unsigned)mKeySettings.GetKey(KeySettings::RELEASE_NANO));
    key_settings.appendChild(release_nano);

    zoom.setAttribute(KEY_FUNCTION, (unsigned)KeySettings::ZOOM);
    zoom.setAttribute(KEY_CODE, (unsigned)mKeySettings.GetKey(KeySettings::ZOOM));
    key_settings.appendChild(zoom);

    return key_settings;
}