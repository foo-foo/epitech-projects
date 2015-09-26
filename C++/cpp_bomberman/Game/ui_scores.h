/********************************************************************************
** Form generated from reading UI file 'scores.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCORES_H
#define UI_SCORES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Scores
{
public:
    QLabel *label;
    QPushButton *backButton;

    void setupUi(QWidget *Scores)
    {
        if (Scores->objectName().isEmpty())
            Scores->setObjectName(QString::fromUtf8("Scores"));
        Scores->resize(1018, 676);
        label = new QLabel(Scores);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(250, 20, 67, 17));
        backButton = new QPushButton(Scores);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(10, 640, 75, 23));

        retranslateUi(Scores);

        QMetaObject::connectSlotsByName(Scores);
    } // setupUi

    void retranslateUi(QWidget *Scores)
    {
        Scores->setWindowTitle(QApplication::translate("Scores", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Scores", "SCORES", 0, QApplication::UnicodeUTF8));
        backButton->setText(QApplication::translate("Scores", "Retour", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Scores: public Ui_Scores {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCORES_H
