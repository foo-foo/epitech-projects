/********************************************************************************
** Form generated from reading UI file 'home.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_H
#define UI_HOME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Home
{
public:
    QPushButton *optionButton;
    QPushButton *bomberButton;
    QPushButton *editButton;
    QPushButton *multiButton;
    QLabel *titleLabel;
    QPushButton *buttonQuitter;
    QPushButton *boutonScores;

    void setupUi(QWidget *Home)
    {
        if (Home->objectName().isEmpty())
            Home->setObjectName(QString::fromUtf8("Home"));
        Home->resize(1018, 676);
        Home->setStyleSheet(QString::fromUtf8(""));
        optionButton = new QPushButton(Home);
        optionButton->setObjectName(QString::fromUtf8("optionButton"));
        optionButton->setGeometry(QRect(320, 380, 405, 45));
        optionButton->setCursor(QCursor(Qt::PointingHandCursor));
        optionButton->setFlat(false);
        bomberButton = new QPushButton(Home);
        bomberButton->setObjectName(QString::fromUtf8("bomberButton"));
        bomberButton->setGeometry(QRect(320, 200, 405, 45));
        QFont font;
        font.setPointSize(9);
        font.setBold(false);
        font.setWeight(50);
        bomberButton->setFont(font);
        bomberButton->setCursor(QCursor(Qt::PointingHandCursor));
        bomberButton->setStyleSheet(QString::fromUtf8(""));
        bomberButton->setFlat(false);
        editButton = new QPushButton(Home);
        editButton->setObjectName(QString::fromUtf8("editButton"));
        editButton->setGeometry(QRect(320, 320, 405, 45));
        editButton->setCursor(QCursor(Qt::PointingHandCursor));
        editButton->setFlat(false);
        multiButton = new QPushButton(Home);
        multiButton->setObjectName(QString::fromUtf8("multiButton"));
        multiButton->setGeometry(QRect(320, 260, 405, 45));
        multiButton->setCursor(QCursor(Qt::PointingHandCursor));
        multiButton->setFlat(false);
        titleLabel = new QLabel(Home);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(40, 10, 481, 71));
        buttonQuitter = new QPushButton(Home);
        buttonQuitter->setObjectName(QString::fromUtf8("buttonQuitter"));
        buttonQuitter->setGeometry(QRect(320, 500, 405, 45));
        buttonQuitter->setCursor(QCursor(Qt::PointingHandCursor));
        buttonQuitter->setFlat(false);
        boutonScores = new QPushButton(Home);
        boutonScores->setObjectName(QString::fromUtf8("boutonScores"));
        boutonScores->setGeometry(QRect(320, 440, 405, 45));
        boutonScores->setCursor(QCursor(Qt::PointingHandCursor));
        boutonScores->setFlat(false);

        retranslateUi(Home);

        QMetaObject::connectSlotsByName(Home);
    } // setupUi

    void retranslateUi(QWidget *Home)
    {
        Home->setWindowTitle(QApplication::translate("Home", "Form", 0, QApplication::UnicodeUTF8));
        optionButton->setText(QApplication::translate("Home", "Options...", 0, QApplication::UnicodeUTF8));
        bomberButton->setText(QApplication::translate("Home", "Jouer", 0, QApplication::UnicodeUTF8));
        editButton->setText(QApplication::translate("Home", "Editeur de map", 0, QApplication::UnicodeUTF8));
        multiButton->setText(QApplication::translate("Home", "Multijoueur", 0, QApplication::UnicodeUTF8));
        titleLabel->setText(QApplication::translate("Home", "Accueil", 0, QApplication::UnicodeUTF8));
        buttonQuitter->setText(QApplication::translate("Home", "Quitter le jeu", 0, QApplication::UnicodeUTF8));
        boutonScores->setText(QApplication::translate("Home", "Tableau des scores", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Home: public Ui_Home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_H
