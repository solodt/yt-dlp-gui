#include "mainwindow.h"

#include <QApplication>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSystemSemaphore semaphore("<sdtgui>", 1);
    semaphore.acquire();
    QSharedMemory sharedMemory("<sdtgui2>");
    bool active;
    if (sharedMemory.attach()){
        active = true;
    }
    else
    {
        sharedMemory.create(1);
        active = false;
    }
    semaphore.release();
    if (active)
    {
        QMessageBox error;
        error.setIcon(QMessageBox::Critical);
        error.setText("Приложение уже запущено.");
        error.exec();
        return 1;
    }
    MainWindow w;
    w.show();
    return a.exec();
}
