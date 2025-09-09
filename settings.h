#ifndef SettingsManager_H
#define SettingsManager_H

#include <QObject>

/** @addtogroup settings */
/*@{*/

struct defaultSetting{

    QString id;
    QString value;
    bool enabled;
    bool checked;
    bool checkedAvailable;
    bool forPremium;
};


class SettingsManager : QObject
{
    Q_OBJECT
public:
    QList<defaultSetting> __currentSettings;
    QList<defaultSetting> __defaultSettings;

    SettingsManager(){}

    bool isDefault(QString s, bool reset = false);
    defaultSetting GetSetting(QString id, bool &was);

    void LoadSettings();
    void UpdateSettings();
};
/*@}*/
#endif // SettingsManager_H
