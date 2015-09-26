#include <QFontDatabase>
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include "options.hpp"
#include "ui_options.h"

#include "home.hpp"

Options::Options(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Options)
{
    m_parent = parent;
    ui->setupUi(this);

    // Fontes
    QFont silk = loadFont(40);
    ui->titleLabel->setFont(silk);
    silk = loadFont(16);
    ui->lblt1->setFont(silk);
    ui->lblt2->setFont(silk);
    ui->lblt3->setFont(silk);

    // signaux
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(returnHome()));
    connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(saveChanges()));
    connect(ui->slid_Bonus, SIGNAL(valueChanged(int)), this, SLOT(changeLabelValue(int)));
}

Options::~Options()
{
    delete ui;
}

QFont Options::loadFont(int size)
{
    int id = QFontDatabase::addApplicationFont(":/fonts/ressources/slkscr.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont silkscreenNormal(family);
    silkscreenNormal.setWeight(80);
    silkscreenNormal.setPixelSize(size);
    return (silkscreenNormal);
}

void Options::returnHome()
{
    this->close();

    Home *home = new Home(m_parent);
    home->show();
}

void Options::saveChanges()
{
    // On récupère les infos
    m_keysP1.push_back(ui->txt_avancer1->toPlainText().toStdString());
    m_keysP1.push_back(ui->txt_reculer1->toPlainText().toStdString());
    m_keysP1.push_back(ui->txt_gauche1->toPlainText().toStdString());
    m_keysP1.push_back(ui->txt_droite1->toPlainText().toStdString());
    m_keysP1.push_back(ui->txt_poserBombe1->toPlainText().toStdString());

    m_keysP2.push_back(ui->txt_avancer2->toPlainText().toStdString());
    m_keysP2.push_back(ui->txt_reculer2->toPlainText().toStdString());
    m_keysP2.push_back(ui->txt_gauche2->toPlainText().toStdString());
    m_keysP2.push_back(ui->txt_droite2->toPlainText().toStdString());
    m_keysP2.push_back(ui->txt_poserBombe2->toPlainText().toStdString());

    m_sound = ui->cbMusique->isChecked();
    m_nbIa = ui->cbNPlayer->currentText().toStdString();
    m_levelIa = ui->cbLevelIa->currentText().toStdString();
    m_bonusValue = ui->slid_Bonus->value();
    // On écrit dans le fichier
    std::ofstream file("config/options.txt", std::ios::out | std::ios::trunc);
    if (file)
    {
        file << "p1:" << listKeys(m_keysP1) << std::endl << "p2:" << listKeys(m_keysP2) << std::endl
             << "sound:" << (m_sound == true ? "y" : "n") << std::endl
             << "nb_ia:" << m_nbIa << std::endl
             << "level_ia:" << m_levelIa << std::endl << "level_bonus:" << m_bonusValue << std::endl;
        file.close();
        // On affiche le message de confirmation
        QMessageBox saveInfo(QMessageBox::Information, "Options", "Les options ont été sauvegardées");
        saveInfo.exec();
    }
}

// Créer une chaine de caractères formattée
std::string Options::listKeys(std::vector<std::string> keys)
{
    std::ostringstream oss;
    oss << keys[0] << "|" << keys[1] << "|" << keys[2] << "|" << keys[3] << "|"
                   << keys[4];
    return (oss.str());
}

void Options::changeLabelValue(int value)
{
    ui->lbl_Bonus->setText(QString::number(value) + " %");
}
