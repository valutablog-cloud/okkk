#include "mainwindow.h"
#include "tuxlerapp.h"

bool SettingsManager::isDefault(QString s, bool reset){

    foreach(defaultSetting set, __defaultSettings){

        if(set.id == s && ((!MainWindow::__instance->__isPremium && set.forPremium))) {

            if(reset) emit MainWindow::__instance->SendNewGuiEvent(QString("<message>EVENTSETCONTROL</message><details>"+set.id+";"+set.value+"</details>"));

            return true;
        }
    }

    return false;
}

defaultSetting SettingsManager::GetSetting(QString id, bool &was){

    was = false;

    defaultSetting setret;

    foreach (defaultSetting set, __defaultSettings) 
	{
        if(set.id == id)
		{
            was = true;
            setret = set;
            break;
        }
    }

    defaultSetting set;


    QSettings settings(SETTINGS_NAME, SETTINGS_NAME);

    settings.beginGroup("gui");

    bool was2 = false;

    foreach (const QString &key, settings.childKeys()) 
	{
            if(key == id)
			{
                QString value = settings.value(key).toString();

                set.value = value;

                set.checked = value == "true" ? true : false;

				was2 = true;

                break;
            }
    }

    settings.endGroup();

    if(was2) 
		return set;

    return setret;
}

void SettingsManager::UpdateSettings(){

}

void SettingsManager::LoadSettings(){

    QList<defaultSetting> currentSettings;

    foreach(defaultSetting set, __defaultSettings){

        emit MainWindow::__instance->SendNewGuiEvent(QString("<message>EVENTSETCONTROL</message><details>"+set.id+";"+set.value+"</details>"));

        currentSettings.append(set);
    }

    QSettings settings(SETTINGS_NAME, SETTINGS_NAME);

    settings.beginGroup("gui");

    foreach (const QString &key, settings.childKeys()) {

        if(isDefault(key)) continue;

        for(QList<defaultSetting>::iterator it = currentSettings.begin(); it != currentSettings.end(); it++){

            if((*it).id == key){

                QString value = settings.value(key).toString();

                (*it).value = value;

                (*it).checked = value == "true" ? true : false;

            }
        }

        emit MainWindow::__instance->SendNewGuiEvent(QString("<message>EVENTSETCONTROL</message><details>"+key+";"+settings.value(key).toString()+"</details>"));
    }

    settings.endGroup();

    __currentSettings = currentSettings;

    UpdateSettings();
}
