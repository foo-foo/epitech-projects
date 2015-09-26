#include <QFontDatabase>
#include <QSignalMapper>
#include "home.hpp"
#include "ui_home.h"

#include "launcher.hpp"
#include "options.hpp"
#include "mapeditor.hpp"
#include "scores.hpp"

Home::Home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);

    m_parent = parent;

    // Fontes
    QFont silk = loadFont(16);
    ui->bomberButton->setFont(silk);
    ui->editButton->setFont(silk);
    ui->multiButton->setFont(silk);
    ui->optionButton->setFont(silk);
    ui->buttonQuitter->setFont(silk);
    ui->boutonScores->setFont(silk);
    silk = loadFont(40);
    ui->titleLabel->setFont(silk);

    // signaux
    connect(ui->bomberButton, SIGNAL( clicked() ), this, SLOT(displayPlay1()));
    connect(ui->multiButton, SIGNAL( clicked() ), this, SLOT(displayPlay2()));
    connect(ui->editButton, SIGNAL(clicked()), this, SLOT(displayMapEditor()));
    connect(ui->optionButton, SIGNAL(clicked()), this, SLOT(displayOptions()));
    connect(ui->editButton, SIGNAL(clicked()), this, SLOT(displayMapEditor()));
    connect(ui->boutonScores, SIGNAL(clicked()), this, SLOT(displayScores()));
    connect(ui->buttonQuitter, SIGNAL(clicked()), this, SLOT(exitGame()));

}

Home::~Home()
{
    delete ui;
}

QFont Home::loadFont(int size)
{
    int id = QFontDatabase::addApplicationFont(":/fonts/ressources/slkscr.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont silkscreenNormal(family);
    silkscreenNormal.setWeight(80);
    silkscreenNormal.setPixelSize(size);
    return (silkscreenNormal);
}

void Home::displayPlay2()
{
    this->close();
    Launcher *launcher = new Launcher(true, m_parent);
    launcher->show();
}

void Home::displayPlay1()
{
    this->close();
    Launcher *launcher = new Launcher(false, m_parent);
    launcher->show();
}
void Home::displayMapEditor()
{
    this->close();
    MapEditor *map = new MapEditor(m_parent);
    map->show();
}

void Home::displayOptions()
{
    this->close();
    Options *options = new Options(m_parent);
    options->show();
}

void Home::displayScores()
{
    this->close();
    Scores *scores = new Scores(m_parent);
    scores->show();
}

void Home::exitGame()
{
    m_parent->close();
}
