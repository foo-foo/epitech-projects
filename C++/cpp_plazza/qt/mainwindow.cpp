#include <unistd.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "./includes/Reception.hpp"
#include "./includes/Kitchen.hpp"

QStandardItemModel *_model;
extern Reception *reception;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _model = new QStandardItemModel(0, 10, this);
    _model->setHorizontalHeaderItem(0, new QStandardItem(QString("Cooks working")));
    _model->setHorizontalHeaderItem(1, new QStandardItem(QString("Doe")));
    _model->setHorizontalHeaderItem(2, new QStandardItem(QString("Tomato")));
    _model->setHorizontalHeaderItem(3, new QStandardItem(QString("Gruyere")));
    _model->setHorizontalHeaderItem(4, new QStandardItem(QString("Ham")));
    _model->setHorizontalHeaderItem(5, new QStandardItem(QString("Mushrooms")));
    _model->setHorizontalHeaderItem(6, new QStandardItem(QString("Steak")));
    _model->setHorizontalHeaderItem(7, new QStandardItem(QString("Eggplant")));
    _model->setHorizontalHeaderItem(8, new QStandardItem(QString("Chieflove")));
    _model->setHorizontalHeaderItem(9, new QStandardItem(QString("Goatcheese")));
   ui->tableView->setModel(_model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void*    MainWindow::uiUpdate(void* args)
{
    std::list<Kitchen*>*            list;
    std::list<Kitchen*>::iterator   it;
    t_resource                     resources;
    QList<QStandardItem*>           data_list;
    QList<QStandardItem*>::iterator itl;

    list = reception->getKitchensList();
    while (42)
    {
        for (it = list->begin(); it != list->end(); it++)
        {
          while (!data_list.empty())
            data_list.pop_front();
          resources = (*it)->getResources().getResources();
          data_list.push_back(new QStandardItem(QString::number(42))); // cooks occupés
          data_list.push_back(new QStandardItem(QString::number(resources.doe)));
          data_list.push_back(new QStandardItem(QString::number(resources.tomato)));
          data_list.push_back(new QStandardItem(QString::number(resources.gruyere)));
          data_list.push_back(new QStandardItem(QString::number(resources.ham)));
          data_list.push_back(new QStandardItem(QString::number(resources.mushrooms)));
          data_list.push_back(new QStandardItem(QString::number(resources.steak)));
          data_list.push_back(new QStandardItem(QString::number(resources.eggplant)));
          data_list.push_back(new QStandardItem(QString::number(resources.chieflove)));
          data_list.push_back(new QStandardItem(QString::number(resources.goatcheese)));
          _model->appendRow(data_list);
        }
     //   printf("Size : %d\n", list->size());
        sleep(1);

        _model->removeRows(0, _model->rowCount());
    }
  return (NULL);
}

/* *********** */
/* Public Slot */
/* *********** */

void    MainWindow::askReginaS() const
{
    write(0, "regina S x1\n", 13);
}

void    MainWindow::askReginaM() const
{
    write(1, "regina M x1\n", 12);
}

void    MainWindow::askReginaL() const
{
    write(1, "regina L x1\n", 12);
}

void    MainWindow::askReginaXL() const
{
    write(1, "regina XL x1\n", 13);
}

void    MainWindow::askReginaXXL() const
{
    write(1, "regina XXL x1\n", 14);
}

/* *********************** */

void    MainWindow::askMargaritaS() const
{
    write(1, "margarita S x1\n", 15);
}

void    MainWindow::askMargaritaM() const
{
    write(1, "margarita M x1\n", 15);
}

void    MainWindow::askMargaritaL() const
{
    write(1, "margarita L x1\n", 15);
}

void    MainWindow::askMargaritaXL() const
{
    write(1, "margarita XL x1\n", 16);
}

void    MainWindow::askMargaritaXXL() const
{
    write(1, "margarita XXL x1\n", 17);
}

/* *********************** */

void    MainWindow::askAmericaineS() const
{
    write(1, "americaine S x1\n", 16);
}

void    MainWindow::askAmericaineM() const
{
    write(1, "americaine M x1\n", 16);
}

void    MainWindow::askAmericaineL() const
{
    write(1, "americaine L x1\n", 16);
}

void    MainWindow::askAmericaineXL() const
{
    write(1, "americaine XL x1\n", 17);
}

void    MainWindow::askAmericaineXXL() const
{
    write(1, "americaine XXL x1\n", 18);
}

/* *********************** */

void    MainWindow::askFantasiaS() const
{
    write(1, "fantasia S x1\n", 14);
}

void    MainWindow::askFantasiaM() const
{
    write(1, "fantasia M x1\n", 14);
}

void    MainWindow::askFantasiaL() const
{
    write(1, "fantasia L x1\n", 14);
}

void    MainWindow::askFantasiaXL() const
{
    write(1, "fantasia XL x1\n", 15);
}

void    MainWindow::askFantasiaXXL() const
{
    write(1, "fantasia XXL x1\n", 16);
}
