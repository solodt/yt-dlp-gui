#include "mainwindow.h"

#include <QApplication>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QMessageBox>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMessageBox error;
    error.setIcon(QMessageBox::Critical);
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
        error.setText("Приложение уже запущено.");
        error.exec();
        return 1;
    }
    else if(!QFile::exists("yt-dlp.exe") || (!QFile::exists("ffmpeg.exe") || (!QFile::exists("ffprobe.exe")))){
        QString text="Отсутствуют:";
        int i=1;
        if(!QFile::exists("yt-dlp.exe")){
            text+="\n"+QString::number(i)+". yt-dlp.exe   ";
            i++;
        }
        if(!QFile::exists("ffmpeg.exe")){
            text+="\n"+QString::number(i)+". ffmpeg.exe   ";
            i++;
        }
        if(!QFile::exists("ffprobe.exe")){
            text+="\n"+QString::number(i)+". ffprobe.exe   ";
            i++;
        }
        error.setText(text);
        error.exec();
        return 1;
}
    MainWindow w;
    w.show();
    return a.exec();
}
