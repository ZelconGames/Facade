#ifndef CONFIGURATION_MANAGER_H
#define CONFIGURATION_MANAGER_H

#include "KeySettings.h"
#include "Definitions.h"

#include <boost/noncopyable.hpp>

#include <QtXml/QtXml>

#include <memory>
#include <map>

class ConfigurationManager : boost::noncopyable
{
public:
    static ConfigurationManager* GetInstance();

    bool LoadConfig();

    bool SaveConfig() const;

    KeySettings GetKeySettings() const;

    void SetKeySettings(KeySettings key_settings);

private:
    void _LoadKeySettings(const QDomElement& element);

    QDomElement _SaveKeySettings(QDomDocument& doc) const;

    ConfigurationManager();

    static std::shared_ptr<ConfigurationManager> mInstance;
    KeySettings mKeySettings;
};

#endif