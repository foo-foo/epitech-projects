/********************************************************************************
** Form generated from reading UI file 'options.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONS_H
#define UI_OPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSlider>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Options
{
public:
    QLabel *titleLabel;
    QPushButton *backButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *lblt1;
    QGroupBox *gbPLayer1;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QTextEdit *txt_avancer1;
    QTextEdit *txt_reculer1;
    QTextEdit *txt_gauche1;
    QTextEdit *txt_droite1;
    QTextEdit *txt_poserBombe1;
    QGroupBox *gbPlayer2;
    QTextEdit *txt_gauche2;
    QLabel *label_8;
    QLabel *label_9;
    QTextEdit *txt_reculer2;
    QLabel *label_10;
    QTextEdit *txt_avancer2;
    QLabel *label_11;
    QLabel *label_12;
    QTextEdit *txt_droite2;
    QTextEdit *txt_poserBombe2;
    QLabel *lblt2;
    QLabel *lblt3;
    QLabel *label;
    QComboBox *comboBox;
    QComboBox *cbNPlayer;
    QCheckBox *cbMusique;
    QPushButton *btnSave;
    QLabel *label_2;
    QComboBox *cbLevelIa;
    QLabel *lblt2_2;
    QSlider *slid_Bonus;
    QLabel *lbl_Bonus;

    void setupUi(QWidget *Options)
    {
        if (Options->objectName().isEmpty())
            Options->setObjectName(QString::fromUtf8("Options"));
        Options->resize(1018, 676);
        titleLabel = new QLabel(Options);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(20, 20, 481, 71));
        backButton = new QPushButton(Options);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(10, 640, 75, 23));
        scrollArea = new QScrollArea(Options);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(20, 90, 951, 531));
        scrollArea->setMinimumSize(QSize(0, 531));
        scrollArea->setMaximumSize(QSize(16777215, 16777215));
        scrollArea->setBaseSize(QSize(0, 531));
        scrollArea->setAcceptDrops(false);
        scrollArea->setLayoutDirection(Qt::LeftToRight);
        scrollArea->setStyleSheet(QString::fromUtf8(""));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 949, 529));
        lblt1 = new QLabel(scrollAreaWidgetContents);
        lblt1->setObjectName(QString::fromUtf8("lblt1"));
        lblt1->setGeometry(QRect(10, 10, 101, 21));
        gbPLayer1 = new QGroupBox(scrollAreaWidgetContents);
        gbPLayer1->setObjectName(QString::fromUtf8("gbPLayer1"));
        gbPLayer1->setGeometry(QRect(70, 40, 301, 291));
        label_3 = new QLabel(gbPLayer1);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 50, 47, 13));
        label_4 = new QLabel(gbPLayer1);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 100, 47, 13));
        label_5 = new QLabel(gbPLayer1);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 150, 47, 13));
        label_6 = new QLabel(gbPLayer1);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 200, 47, 13));
        label_7 = new QLabel(gbPLayer1);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 240, 111, 16));
        txt_avancer1 = new QTextEdit(gbPLayer1);
        txt_avancer1->setObjectName(QString::fromUtf8("txt_avancer1"));
        txt_avancer1->setGeometry(QRect(110, 40, 181, 31));
        txt_reculer1 = new QTextEdit(gbPLayer1);
        txt_reculer1->setObjectName(QString::fromUtf8("txt_reculer1"));
        txt_reculer1->setGeometry(QRect(110, 90, 181, 31));
        txt_gauche1 = new QTextEdit(gbPLayer1);
        txt_gauche1->setObjectName(QString::fromUtf8("txt_gauche1"));
        txt_gauche1->setGeometry(QRect(110, 140, 181, 31));
        txt_droite1 = new QTextEdit(gbPLayer1);
        txt_droite1->setObjectName(QString::fromUtf8("txt_droite1"));
        txt_droite1->setGeometry(QRect(110, 190, 181, 31));
        txt_poserBombe1 = new QTextEdit(gbPLayer1);
        txt_poserBombe1->setObjectName(QString::fromUtf8("txt_poserBombe1"));
        txt_poserBombe1->setGeometry(QRect(110, 240, 181, 31));
        gbPlayer2 = new QGroupBox(scrollAreaWidgetContents);
        gbPlayer2->setObjectName(QString::fromUtf8("gbPlayer2"));
        gbPlayer2->setGeometry(QRect(530, 40, 301, 291));
        txt_gauche2 = new QTextEdit(gbPlayer2);
        txt_gauche2->setObjectName(QString::fromUtf8("txt_gauche2"));
        txt_gauche2->setGeometry(QRect(110, 140, 181, 31));
        label_8 = new QLabel(gbPlayer2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 200, 47, 13));
        label_9 = new QLabel(gbPlayer2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 100, 47, 13));
        txt_reculer2 = new QTextEdit(gbPlayer2);
        txt_reculer2->setObjectName(QString::fromUtf8("txt_reculer2"));
        txt_reculer2->setGeometry(QRect(110, 90, 181, 31));
        label_10 = new QLabel(gbPlayer2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 150, 47, 13));
        txt_avancer2 = new QTextEdit(gbPlayer2);
        txt_avancer2->setObjectName(QString::fromUtf8("txt_avancer2"));
        txt_avancer2->setGeometry(QRect(110, 40, 181, 31));
        label_11 = new QLabel(gbPlayer2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 240, 111, 16));
        label_12 = new QLabel(gbPlayer2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 50, 47, 13));
        txt_droite2 = new QTextEdit(gbPlayer2);
        txt_droite2->setObjectName(QString::fromUtf8("txt_droite2"));
        txt_droite2->setGeometry(QRect(110, 190, 181, 31));
        txt_poserBombe2 = new QTextEdit(gbPlayer2);
        txt_poserBombe2->setObjectName(QString::fromUtf8("txt_poserBombe2"));
        txt_poserBombe2->setGeometry(QRect(110, 240, 181, 31));
        lblt2 = new QLabel(scrollAreaWidgetContents);
        lblt2->setObjectName(QString::fromUtf8("lblt2"));
        lblt2->setGeometry(QRect(10, 350, 101, 21));
        lblt3 = new QLabel(scrollAreaWidgetContents);
        lblt3->setObjectName(QString::fromUtf8("lblt3"));
        lblt3->setGeometry(QRect(10, 450, 81, 16));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 480, 121, 16));
        comboBox = new QComboBox(scrollAreaWidgetContents);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(160, 610, 69, 22));
        cbNPlayer = new QComboBox(scrollAreaWidgetContents);
        cbNPlayer->setObjectName(QString::fromUtf8("cbNPlayer"));
        cbNPlayer->setGeometry(QRect(200, 470, 141, 31));
        cbMusique = new QCheckBox(scrollAreaWidgetContents);
        cbMusique->setObjectName(QString::fromUtf8("cbMusique"));
        cbMusique->setGeometry(QRect(80, 380, 181, 21));
        cbMusique->setChecked(true);
        btnSave = new QPushButton(scrollAreaWidgetContents);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setGeometry(QRect(780, 470, 161, 51));
        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(400, 480, 101, 16));
        cbLevelIa = new QComboBox(scrollAreaWidgetContents);
        cbLevelIa->setObjectName(QString::fromUtf8("cbLevelIa"));
        cbLevelIa->setGeometry(QRect(510, 470, 131, 31));
        lblt2_2 = new QLabel(scrollAreaWidgetContents);
        lblt2_2->setObjectName(QString::fromUtf8("lblt2_2"));
        lblt2_2->setGeometry(QRect(530, 350, 141, 21));
        slid_Bonus = new QSlider(scrollAreaWidgetContents);
        slid_Bonus->setObjectName(QString::fromUtf8("slid_Bonus"));
        slid_Bonus->setGeometry(QRect(530, 380, 301, 19));
        slid_Bonus->setMinimum(1);
        slid_Bonus->setMaximum(100);
        slid_Bonus->setOrientation(Qt::Horizontal);
        lbl_Bonus = new QLabel(scrollAreaWidgetContents);
        lbl_Bonus->setObjectName(QString::fromUtf8("lbl_Bonus"));
        lbl_Bonus->setGeometry(QRect(840, 380, 47, 13));
        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(Options);

        QMetaObject::connectSlotsByName(Options);
    } // setupUi

    void retranslateUi(QWidget *Options)
    {
        Options->setWindowTitle(QApplication::translate("Options", "Form", 0, QApplication::UnicodeUTF8));
        titleLabel->setText(QApplication::translate("Options", "Options", 0, QApplication::UnicodeUTF8));
        backButton->setText(QApplication::translate("Options", "Retour", 0, QApplication::UnicodeUTF8));
        lblt1->setText(QApplication::translate("Options", "Touches", 0, QApplication::UnicodeUTF8));
        gbPLayer1->setTitle(QApplication::translate("Options", "Joueur 1", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Options", "Avancer", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Options", "Reculer", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Options", "Gauche", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Options", "Droite", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Options", "Poser une bombe", 0, QApplication::UnicodeUTF8));
        gbPlayer2->setTitle(QApplication::translate("Options", "Joueur 2", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Options", "Droite", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Options", "Reculer", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Options", "Gauche", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("Options", "Poser une bombe", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("Options", "Avancer", 0, QApplication::UnicodeUTF8));
        lblt2->setText(QApplication::translate("Options", "Son", 0, QApplication::UnicodeUTF8));
        lblt3->setText(QApplication::translate("Options", "IA", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Options", "Nombre d'ordinateur:", 0, QApplication::UnicodeUTF8));
        cbNPlayer->clear();
        cbNPlayer->insertItems(0, QStringList()
         << QApplication::translate("Options", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Options", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Options", "3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Options", "4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Options", "5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Options", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Options", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Options", "8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Options", "9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Options", "10", 0, QApplication::UnicodeUTF8)
        );
        cbMusique->setText(QApplication::translate("Options", "Activer la musique", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("Options", "Sauvegarder", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Options", "Niveau ordinateur:", 0, QApplication::UnicodeUTF8));
        cbLevelIa->clear();
        cbLevelIa->insertItems(0, QStringList()
         << QApplication::translate("Options", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Options", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Options", "3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Options", "4", 0, QApplication::UnicodeUTF8)
        );
        lblt2_2->setText(QApplication::translate("Options", "Niveau de bonus", 0, QApplication::UnicodeUTF8));
        lbl_Bonus->setText(QApplication::translate("Options", "1 %", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Options: public Ui_Options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONS_H
