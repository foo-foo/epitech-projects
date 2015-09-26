#include <fstream>
#include <QMessageBox>
#include <QFileDialog>
#include "mapeditor.hpp"
#include "ui_mapeditor.h"

#include "home.hpp"

MapEditor::MapEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapEditor)
{
    m_parent = parent;
    ui->setupUi(this);

    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(returnHome()));
    connect(ui->btnLoad, SIGNAL(clicked()), this, SLOT(loadButton()));
    connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(saveButton()));
}

MapEditor::~MapEditor()
{
    delete ui;
}

void MapEditor::returnHome()
{
    this->close();

    Home *home = new Home(m_parent);
    home->show();
}

void MapEditor::saveButton()
{
    m_content = ui->txtMapEdit->toPlainText().toStdString();
    std::string filename = "./Maps/" + ui->txtFileName->toPlainText().trimmed().toStdString();

    if (!fileExists(filename))
    {
        std::ofstream fileMap(filename.c_str(), std::ios::out | std::ios::trunc);

        if (fileMap)
        {
            fileMap << m_content;
            fileMap.close();
            QMessageBox saveInfo(QMessageBox::Information, "Map", "La map a bien été crée");
            saveInfo.exec();
        }
    }
    else
    {
        QMessageBox saveInfo(QMessageBox::Warning, "Map", "Tentative d'écrire sur une map existante.");
        saveInfo.exec();
    }
}

void MapEditor::loadButton()
{
     QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir une map"), "./Maps/", tr("Fichier map (*.bmap)"));
     std::ifstream fileMap(fileName.toStdString().c_str(), std::ios::in);

     if (fileMap)
     {
         std::string ligne;
         while(std::getline(fileMap, ligne))
         {
             ui->txtMapEdit->append(QString::fromStdString(ligne));
         }
         fileMap.close();
     }
}

bool MapEditor::fileExists(std::string fileName)
{
    std::ifstream infile(fileName.c_str());
    return infile.good();
}
