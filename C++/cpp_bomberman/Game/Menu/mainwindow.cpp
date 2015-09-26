#include <QDebug>
#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "home.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // signaux / slots
    /*connect(ui->bomberButton, SIGNAL(clicked()), this, SLOT(displayPlay()));
    connect(ui->multiButton, SIGNAL(clicked()), this, SLOT(displayPlay()));
    connect(ui->editButton, SIGNAL(clicked()), this, SLOT(displayMapEditor()));
    connect(ui->optionButton, SIGNAL(clicked()), this, SLOT(displayOptions()));*/

    Home *home = new Home(this);
    home->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
