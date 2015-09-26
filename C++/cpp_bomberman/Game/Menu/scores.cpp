#include "scores.hpp"
#include "ui_scores.h"
#include "home.hpp"

Scores::Scores(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Scores)
{
    m_parent = parent;
    ui->setupUi(this);

    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(returnHome()));
}

Scores::~Scores()
{
    delete ui;
}

void Scores::returnHome()
{
    this->close();

    Home *home = new Home(m_parent);
    home->show();
}
