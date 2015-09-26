#include <QApplication>
#include "mainwindow.h"
#include "./includes/Reception.hpp"
#include <stdlib.h>

Reception *reception;

void* main_ui(void *args)
{
    QApplication a(0, {});
    MainWindow w;
    w.show();

    reception = reinterpret_cast<Reception*>(args);
    pthread_t update_thread;
    pthread_create(&update_thread, NULL, w.uiUpdate, NULL);

    int ret = a.exec();
    exit(0);
    return &ret;
}
