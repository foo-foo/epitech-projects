#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStandardItemModel>
#include <QStandardItem>
#include <cstdio>
#include <unistd.h>
#include <QMainWindow>

#include <list>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static void    *uiUpdate(void *args);

public slots:
    void    askReginaS() const;
    void    askReginaM() const;
    void    askReginaL() const;
    void    askReginaXL() const;
    void    askReginaXXL() const;

    void    askMargaritaS() const;
    void    askMargaritaM() const;
    void    askMargaritaL() const;
    void    askMargaritaXL() const;
    void    askMargaritaXXL() const;

    void    askAmericaineS() const;
    void    askAmericaineM() const;
    void    askAmericaineL() const;
    void    askAmericaineXL() const;
    void    askAmericaineXXL() const;

    void    askFantasiaS() const;
    void    askFantasiaM() const;
    void    askFantasiaL() const;
    void    askFantasiaXL() const;
    void    askFantasiaXXL() const;



signals:
    void    askForRegina() const;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
