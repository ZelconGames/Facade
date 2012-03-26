#include "ConfigurationManager.h"

#include <Utils/Logger.hpp>
#include <Utils/Utils.hpp>

std::shared_ptr<ConfigurationManager> ConfigurationManager::mInstance = 
    std::shared_ptr<ConfigurationManager>(new ConfigurationManager());

ConfigurationManager::ConfigurationManager()
{
}

ConfigurationManager* ConfigurationManager::getInstance()
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
        Logger::get().info("The configuration file doesn't exist. Trying to create a new one.");
        
        if(!SaveConfig())
        {
            Logger::get().error("Failed to open the configuration file.");

            return false;
        }
        else
        {
            Logger::get().info("Created a new configuration file.");

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
        Logger::get().error("Failed to read from the configuration file.");

        return false;
    }

    return true;
}

KeySettings ConfigurationManager::getKeySettings() const
{
    return mKeySettings;
}

void ConfigurationManager::setKeySettings(KeySettings key_settings)
{
    mKeySettings = key_settings;
}

bool ConfigurationManager::SaveConfig() const
{
    QFile config_file(CONFIG_FILE);
    QDomDocument doc;

    if(!config_file.open(QIODevice::WriteOnly))
    {
        Logger::get().error("Cannot create the configuration file.");
        
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
        InputManager::InputCode input_code = (InputManager::InputCode)key_node.attribute(KEY_CODE).toUInt();

        mKeySettings.setKey(function_code, input_code);
    }
}

QDomElement ConfigurationManager::_SaveKeySettings(QDomDocument& doc) const
{
    auto key_settings = doc.createElement(KEY_SETTINGS);

    for(unsigned function = (unsigned)mKeySettings.Begin() ; function <= (unsigned)mKeySettings.End() ; ++function)
    {
        auto element = doc.createElement(mKeySettings.getName((KeySettings::Function)function));
        
        element.setAttribute(KEY_FUNCTION, function);
        element.setAttribute(KEY_CODE, (unsigned)mKeySettings.getKey((KeySettings::Function)function));
        
        key_settings.appendChild(element);
    }

    return key_settings;
}