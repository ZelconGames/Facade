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
    static ConfigurationManager* getInstance();

    bool LoadConfig();

    bool SaveConfig() const;

    KeySettings getKeySettings() const;

    void setKeySettings(KeySettings key_settings);

private:
    void _LoadKeySettings(const QDomElement& element);

    QDomElement _SaveKeySettings(QDomDocument& doc) const;

    ConfigurationManager();

    static std::shared_ptr<ConfigurationManager> mInstance;
    KeySettings mKeySettings;
};

#endif
