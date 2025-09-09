/** @file */

/** @addtogroup Preprocessor_defs */
/*@{*/
#ifndef CONFIG_H
#define CONFIG_H

#ifdef Q_OS_UNIX
#ifndef Q_OS_MAC
/**
 *@brief disable auto start with Linux
 */
#define DISABLE_AUTOSTART_LINUX
#endif
#endif

/**
 *@brief local port used to communicate between instances - used to limit instances to just one
 */
#define PORT_INSTANCE_COMMUNICATION 54319

#define WS_PSTART 1700
#define WS_PJUMP 7070
#define WS_END 65000

#define STARSMINTOGOTOSTORE 5
#define SHOWAFTERRUNNUMBER 4
#define DISPLAYNOTOFTENTHANDAYS 30
#define SHOWAFTERLOCATIONCHANGENUMBER 10
#define SHOWEVERYDAYIFDIDNTFILLFEEDBACK 3
#define RESETALLAFTERDAYS 50

/**
 *@brief used for shared memory - limit number of instances
 */
#define UNIQUEID_SINGLE_APP "4635634636dfhdhdfhyyhdhdhhdhIDTULER"
#ifndef IPSHARKK
#define ABOUT_WINDOW_TITLE "About Tuxler"
#define ABOUT_WINDOW_TEXT "About Tuxler"
#define ABOUT_DESCRIPTION "Copyright 2008-2021 &copy;  Tuxler Privacy Technologies, Inc. All Rights Reserved. <br>build 1.0"
#define URL_PREMIUM ("http://tuxler.com/extension_event.php?id=upgrade_to_premium&source=winapp")
#define URL_FREE_PREMIUM ("http://tuxler.com/extension_event.php?id=referral_program&source=winapp")
#define URL_SUPPORT ("http://tuxler.com/extension_event.php?id=support&source=winapp")
#define URL_GUIDE ("http://tuxler.com/extension_event.php?id=help&source=winapp")
#define URL_RATING ("http://tuxler.com/extension_event.php?id=winapp_rating&source=winapp")
#define INFO_TEXT "Tuxler notification !"
#define SETTINGS_NAME "Tuxlerapp"
#else
#define ABOUT_WINDOW_TITLE "About IPSharkk"
#define ABOUT_WINDOW_TEXT "About IPSharkk"
#define ABOUT_DESCRIPTION "Copyright 2008-2013 &copy;  ipsharkk.com. All Rights Reserved. <br>build 1.0"
#define URL_PREMIUM "https://www.ipsharkk.com/#prices"
#define INFO_TEXT "IPSharkk notification !"
#define SETTINGS_NAME "IPSharkkapp"
#endif

#define AUTO_START_ARG "--auto-start"

/**
 *@brief used for winsparkle (windows only)
 */
#define IDB_CHECK_FOR_UPDATES_ID 3241

#endif // CONFIG_H
/*@}*/
