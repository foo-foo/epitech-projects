/********************************************************************************
** Form generated from reading UI file 'mapeditor.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPEDITOR_H
#define UI_MAPEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapEditor
{
public:
    QPushButton *backButton;
    QTextEdit *txtMapEdit;
    QGroupBox *gbLegends;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QTextEdit *txtFileName;
    QPushButton *btnSave;
    QPushButton *btnLoad;

    void setupUi(QWidget *MapEditor)
    {
        if (MapEditor->objectName().isEmpty())
            MapEditor->setObjectName(QString::fromUtf8("MapEditor"));
        MapEditor->resize(1018, 676);
        backButton = new QPushButton(MapEditor);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(10, 640, 75, 23));
        txtMapEdit = new QTextEdit(MapEditor);
        txtMapEdit->setObjectName(QString::fromUtf8("txtMapEdit"));
        txtMapEdit->setGeometry(QRect(20, 30, 481, 561));
        QFont font;
        font.setFamily(QString::fromUtf8("Monospace"));
        txtMapEdit->setFont(font);
        gbLegends = new QGroupBox(MapEditor);
        gbLegends->setObjectName(QString::fromUtf8("gbLegends"));
        gbLegends->setGeometry(QRect(530, 30, 451, 351));
        gbLegends->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 100);\n"
""));
        label = new QLabel(gbLegends);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(210, 90, 121, 17));
        label_2 = new QLabel(gbLegends);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(210, 160, 121, 17));
        label_3 = new QLabel(gbLegends);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(210, 230, 121, 17));
        label_4 = new QLabel(gbLegends);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(110, 70, 67, 51));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/textures/ressources/grass.png")));
        label_5 = new QLabel(gbLegends);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(110, 140, 67, 51));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/textures/ressources/mur.png")));
        label_6 = new QLabel(gbLegends);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(110, 210, 67, 51));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/textures/ressources/bonus.png")));
        txtFileName = new QTextEdit(MapEditor);
        txtFileName->setObjectName(QString::fromUtf8("txtFileName"));
        txtFileName->setGeometry(QRect(530, 530, 461, 61));
        QFont font1;
        font1.setPointSize(26);
        font1.setBold(true);
        font1.setWeight(75);
        txtFileName->setFont(font1);
        btnSave = new QPushButton(MapEditor);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setGeometry(QRect(530, 600, 221, 61));
        btnLoad = new QPushButton(MapEditor);
        btnLoad->setObjectName(QString::fromUtf8("btnLoad"));
        btnLoad->setGeometry(QRect(770, 600, 221, 61));

        retranslateUi(MapEditor);

        QMetaObject::connectSlotsByName(MapEditor);
    } // setupUi

    void retranslateUi(QWidget *MapEditor)
    {
        MapEditor->setWindowTitle(QApplication::translate("MapEditor", "Form", 0, QApplication::UnicodeUTF8));
        backButton->setText(QApplication::translate("MapEditor", "Retour", 0, QApplication::UnicodeUTF8));
        gbLegends->setTitle(QApplication::translate("MapEditor", "L\303\251gendes", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MapEditor", "- :     passage", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MapEditor", "W :     mur", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MapEditor", "B :     bonus", 0, QApplication::UnicodeUTF8));
        label_4->setText(QString());
        label_5->setText(QString());
        label_6->setText(QString());
        btnSave->setText(QApplication::translate("MapEditor", "Enregistrer", 0, QApplication::UnicodeUTF8));
        btnLoad->setText(QApplication::translate("MapEditor", "Charger...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MapEditor: public Ui_MapEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEDITOR_H
