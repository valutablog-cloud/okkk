/********************************************************************************
** Form generated from reading UI file 'tooltipIPSHARKK.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLTIPIPSHARKK_H
#define UI_TOOLTIPIPSHARKK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_ToolTip
{
public:
    QLabel *text;
    QLabel *icon;
    QLabel *title;

    void setupUi(QDialog *ToolTip)
    {
        if (ToolTip->objectName().isEmpty())
            ToolTip->setObjectName(QStringLiteral("ToolTip"));
        ToolTip->resize(345, 92);
        ToolTip->setMinimumSize(QSize(345, 92));
        text = new QLabel(ToolTip);
        text->setObjectName(QStringLiteral("text"));
        text->setGeometry(QRect(70, 30, 160, 41));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(text->sizePolicy().hasHeightForWidth());
        text->setSizePolicy(sizePolicy);
        text->setMinimumSize(QSize(160, 40));
        text->setMaximumSize(QSize(16777215, 16777215));
        icon = new QLabel(ToolTip);
        icon->setObjectName(QStringLiteral("icon"));
        icon->setGeometry(QRect(10, 25, 32, 32));
        title = new QLabel(ToolTip);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(70, 10, 261, 16));
        sizePolicy.setHeightForWidth(title->sizePolicy().hasHeightForWidth());
        title->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        title->setFont(font);

        retranslateUi(ToolTip);

        QMetaObject::connectSlotsByName(ToolTip);
    } // setupUi

    void retranslateUi(QDialog *ToolTip)
    {
        ToolTip->setWindowTitle(QApplication::translate("ToolTip", "Dialog", 0));
        text->setText(QString());
        icon->setText(QString());
        title->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ToolTip: public Ui_ToolTip {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLTIPIPSHARKK_H
