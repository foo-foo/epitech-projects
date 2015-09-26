/********************************************************************************
** Form generated from reading UI file 'launcher.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAUNCHER_H
#define UI_LAUNCHER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Launcher
{
public:
    QListWidget *listMaps;
    QPushButton *btnPlay;
    QPushButton *backButton;

    void setupUi(QWidget *Launcher)
    {
        if (Launcher->objectName().isEmpty())
            Launcher->setObjectName(QString::fromUtf8("Launcher"));
        Launcher->resize(1018, 676);
        listMaps = new QListWidget(Launcher);
        listMaps->setObjectName(QString::fromUtf8("listMaps"));
        listMaps->setEnabled(true);
        listMaps->setGeometry(QRect(190, 100, 671, 481));
        listMaps->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 100);"));
        btnPlay = new QPushButton(Launcher);
        btnPlay->setObjectName(QString::fromUtf8("btnPlay"));
        btnPlay->setEnabled(false);
        btnPlay->setGeometry(QRect(440, 10, 201, 81));
        btnPlay->setStyleSheet(QString::fromUtf8(""));
        backButton = new QPushButton(Launcher);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(10, 640, 75, 23));

        retranslateUi(Launcher);

        QMetaObject::connectSlotsByName(Launcher);
    } // setupUi

    void retranslateUi(QWidget *Launcher)
    {
        Launcher->setWindowTitle(QApplication::translate("Launcher", "Form", 0, QApplication::UnicodeUTF8));
        btnPlay->setText(QApplication::translate("Launcher", "Jouer", 0, QApplication::UnicodeUTF8));
        backButton->setText(QApplication::translate("Launcher", "Retour", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Launcher: public Ui_Launcher {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAUNCHER_H
