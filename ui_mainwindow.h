/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *labelbuttons;
    QLabel *resize;
    QLabel *close;
    QLabel *maximize;
    QLabel *minimize;
    QWebView *webView;
    QLabel *lefttool;
    QLabel *menubutton;
    QLabel *menutext;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(450, 690);
        MainWindow->setMinimumSize(QSize(450, 690));
        MainWindow->setMaximumSize(QSize(450, 690));
        MainWindow->setWindowTitle(QStringLiteral("Tuxler"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        centralWidget->setAutoFillBackground(false);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 460, 21));
        labelbuttons = new QLabel(centralWidget);
        labelbuttons->setObjectName(QStringLiteral("labelbuttons"));
        labelbuttons->setGeometry(QRect(0, 0, 40, 21));
        resize = new QLabel(centralWidget);
        resize->setObjectName(QStringLiteral("resize"));
        resize->setGeometry(QRect(431, 750, 31, 21));
        close = new QLabel(centralWidget);
        close->setObjectName(QStringLiteral("close"));
        close->setGeometry(QRect(40, 90, 62, 16));
        maximize = new QLabel(centralWidget);
        maximize->setObjectName(QStringLiteral("maximize"));
        maximize->setGeometry(QRect(160, 120, 62, 16));
        minimize = new QLabel(centralWidget);
        minimize->setObjectName(QStringLiteral("minimize"));
        minimize->setGeometry(QRect(250, 100, 62, 16));
        webView = new QWebView(centralWidget);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setGeometry(QRect(0, 21, 412, 689));
        webView->setUrl(QUrl(QStringLiteral("about:blank")));
        lefttool = new QLabel(centralWidget);
        lefttool->setObjectName(QStringLiteral("lefttool"));
        lefttool->setGeometry(QRect(0, 0, 412, 21));
        menubutton = new QLabel(centralWidget);
        menubutton->setObjectName(QStringLiteral("menubutton"));
        menubutton->setGeometry(QRect(0, 0, 412, 21));
        menutext = new QLabel(centralWidget);
        menutext->setObjectName(QStringLiteral("menutext"));
        menutext->setGeometry(QRect(0, 0, 412, 21));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        label->setText(QString());
        labelbuttons->setText(QString());
        resize->setText(QString());
        close->setText(QString());
        maximize->setText(QString());
        minimize->setText(QString());
        lefttool->setText(QString());
        menubutton->setText(QString());
        menutext->setText(QString());
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
