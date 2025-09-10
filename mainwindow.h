#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebFrame>
#include <QWebView>
#include <QDirIterator>
#include <QBitmap>
#include <QImage>
#include <QTimer>
#include <QMenuBar>
#include <QPixmap>
#include <QMutex>
#include <QSysInfo>
#include <qabstractbutton.h>
#include <QMutexLocker>
#include <QPainter>
#include <QTcpServer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QRegion>
#include <QLabel>
#include <QScrollBar>
#include <QTableWidgetItem>
#include <QSet>
#include <QSettings>
#include <QNetworkProxy>
#include <QNetworkProxyQuery>
#include <QDialog>
#include <QMessageBox>
#if QT_VERSION > QT_VERSION_CHECK(5, 0, 0)
#include <QJsonArray>
#endif
#include <QSet>
#if QT_VERSION > QT_VERSION_CHECK(5, 0, 0)
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QJsonValueRef>
#endif
#include <QListWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QSystemTrayIcon>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QApplication>
#include <QProxyStyle>
#include <QDesktopServices>
#include <QVariant>
#include <QDebug>
#include <QStyleOption>
#include <QStyleOptionHeader>
#include <QMenu>
#include <QThread>
#include <QProcess>

#include "jsbridge.h"
#include "tooltip.h"
#include "translator.h"
#include "sha1.h"
#ifndef IPSHARKK
#include "ui_mainwindow.h"
#else
#include "ui_mainwindowIPSHARKK.h"
#endif
//#include "browserapplication.h"
#include "tooltip.h"
#include "functions.h"
#include "proxysettings.h"
#include "settings.h"
#include "instancecommunication.h"
#include "messageqeue.h"
#include "iplist.h"
#include "parsemessage.h"
#include "settings.h"
#include "systemproxy.h"

#include <list>
#include <iostream>

#ifdef Q_OS_WIN32
#include <windows.h>
#include <wininet.h>
#endif

#ifdef Q_OS_WIN32
#ifndef NO_WINSPARKLE
#include "winsparkle/include/winsparkle.h"
#endif
#endif

#ifndef DWORD
#define DWORD unsigned long
#endif

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

class TuxlerApp;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    static TuxlerApp * __instance;
    QPoint oldPos;
    bool restoreOnShow;
    bool ignoreShow;

    explicit MainWindow();
    ~MainWindow();

    /**
     *@brief restore window
    */
    void Restore();   
    void closeEvent(QCloseEvent* event);

protected:
    Ui::MainWindow *ui;
    QSize SizeBeforeMax, animateto;
    QCursor myCursor;
    QImage toolbar, buttons, buttonsb, buttonshover, bar, resizeimg, closeIMG, closec, closeh, buttonmenu, buttonmenuhover, buttonmenutext,
    maximize, maximizeh, maximizec, minimize, minimizec, minimizeh, bck, lefttool, righttool, middletool;
    QList<QLabel*> __buttons;
    QList<int> __regionsx;
    QPoint __lastPos, __lastPosMove, __lastPosMoveMouse;
    QPixmap *m_pPixmap;
    QPalette * m_pPalette;
    QPixmap bg2, bg2p;
    bool onleft;
    int margin, spacing, marginright;
    bool __isHover;
    bool __isResize;
    bool __isMove;
    bool __maximized;

    /**
     *@brief save wind size and position
    */
    void saveWindowSizePos();

    /**
     *@brief event - main window resizes
    */
    void resizeEvent(QResizeEvent* event);


    void UpdateButtons();
    void UpdateNavBox();


    /**
     *@brief animate window resize to new size
    */
    void AnimateTo(QSize&size);
    bool event(QEvent *event);
    bool eventFilter(QObject *object, QEvent *event);
    void showEvent(QShowEvent * event);

private slots:
    void ResetButtonHover(QAction *action);

    /**
     *@brief disable WebView text selection
    */
    void selectionChanged();
};

#endif // MAINWINDOW_H
