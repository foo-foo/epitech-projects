#include "launcher.hpp"
#include "ui_launcher.h"

#include "home.hpp"

#include "BombEngine.hpp"
#include "GameEngine.hpp"
#include "Field.hpp"
#include "Opt.hpp"

Launcher::Launcher(bool multi, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Launcher)
{
    m_parent = parent;
    ui->setupUi(this);
    m_maps = readDirectory("./Maps/");
    // On écrit les maps dans la listView
    for (QStringList::iterator it = m_maps.begin(); it != m_maps.end(); ++it)
    {
        ui->listMaps->addItem(*it);
    }
    // signaux
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(returnHome()));
    connect(ui->listMaps, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(enableButtonPlay()));
    if (multi)
      connect(ui->btnPlay, SIGNAL(clicked()), this, SLOT(launchGame2()));
    else
      connect(ui->btnPlay,SIGNAL(clicked()), this, SLOT(launchGame1()));
}

Launcher::~Launcher()
{
    delete ui;
}

void Launcher::returnHome()
{
    this->close();

    Home *home = new Home(m_parent);
    home->show();
}

//
// Cherche les maps disponible dans le répertoire
QStringList Launcher::readDirectory(QString dir)
{
    QDir recoredDir(dir);
    QStringList allMaps = recoredDir.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    return (allMaps);
}

//
// active le bouton "Jouer"
void Launcher::enableButtonPlay()
{
    ui->btnPlay->setEnabled(true);
}

int  Launcher::newRound(std::vector<int> &scores, const int nbIa, const int lvl, const int nbPlayer) const
{
  int		gameStatus;
  Field		field("./Maps/"  + ui->listMaps->currentItem()->text().toStdString());
  GameEngine	engine(field, nbPlayer, nbIa, lvl);

  if (!engine.initialize())
    {
      std::cout << "Error : can\'t initialize game engine." << std::endl;
      return (-1);
    }
  BombEngine    bomb_engine(field);
  while (engine.update())
    engine.draw();
  bomb_engine.exitThread();
  gameStatus = engine.getGameStatus();
  if (gameStatus > 0)
    {
      std::cout << "Player " << gameStatus << " won this round." << std::endl;
      scores[gameStatus - 1] += 1;
      if (scores[gameStatus - 1] == 3)
        gameStatus = -1;
    }
  engine.getContext().stop();
  return (gameStatus);
}

void Launcher::launchGame2()
{
    m_parent->hide();
    Opts o("./config/options.txt");
    int nbIa = o.getNbIa();
    int lvl = o.getLevelIa();
    const int nbPlayer = 2;

    int                   gameStatus = 0;
    std::vector<int>      scores(nbIa + nbPlayer, 0);
    size_t                i = 0;

    //_initLaunchGame();
    while ((gameStatus = newRound(scores, nbIa, lvl, nbPlayer)) >= 0);
    while (i < scores.size() && scores[i] != SCORE_TO_WIN)
      i += 1;
    if (i < scores.size())
      std::cout << "Winner is player " << i + 1 << std::endl;

    m_parent->show();
}

void Launcher::launchGame1()
{
    m_parent->hide();
    Opts o("./config/options.txt");
    int nbIa = o.getNbIa();
    int lvl = o.getLevelIa();
    const int nbPlayer = 1;
    int                   gameStatus = 0;
    std::vector<int>      scores(nbIa + nbPlayer, 0);
    size_t                i = 0;

    //_initLaunchGame();
    while ((gameStatus = newRound(scores, nbIa, lvl, nbPlayer)) >= 0);
    while (i < scores.size() && scores[i] != SCORE_TO_WIN)
      i += 1;
    if (i < scores.size())
      std::cout << "Winner is player " << i + 1 << std::endl;

    m_parent->show();
}
