#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "functions.h"
#include <QDir>
#include <QFileDialog>
#include <windows.h>
#include <QTextCodec>
#include <QRegularExpression>
#include <QProcess>
QString path, broil;
QString ckie, format, mp4d[30][6], webmd[30][6], T, lage;
std::string logs;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint);

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_download_clicked()
{
    QString part="";
    if ((ui->LINK->text().toStdString().find("https://www.youtube.com/")!=0
        && ui->LINK->text().toStdString().find("https://youtube.com/")!=0
        && ui->LINK->text().toStdString().find("youtube.com/")!=0
        && ui->LINK->text().toStdString().find("youtu.be/")!=0
        && ui->LINK->text().toStdString().find("https://youtu.be/")!=0
        && ui->LINK->text().toStdString().find("https://www.youtu.be/")!=0
        && ui->LINK->text().toStdString().find("www.youtu.be/")!=0
        && ui->LINK->text().toStdString().find("www.youtube.com/")!=0)
        || ui->LINK->text().contains("&list")){
        if(ui->LINK->text().contains("&list")){
            ui->LINK->setPlaceholderText("Ссылка(не плейлист)");}
        else{ui->LINK->setPlaceholderText("Введите ссылку на видео!");}
        ui->LINK->clear();
    }

    else{
    ui->LINK->setPlaceholderText("https://youtu.be/");
    readwithlines(settings, &broil, 1);
    readwithlines(settings, &path, 2);
    readwithlines(settings, &ckie, 3);
    readwithlines(settings, &lage, 4);
    if(lage=="true") logs=" > log.txt"; else logs.clear();
    if(ckie=="true") part=" --cookies-from-browser "+broil;
    std::string stdpath = "\""+QTextCodec::codecForName("Windows-1251")->fromUnicode(path).toStdString()+"\"";
    switch(ui->Format->currentIndex()){
    case 0:
        format = " -S ext:mp4:m4a ";
        break;
    case 1:
        format = " -x --audio-format mp3 ";
        break;
    case 2:
        format = " ";
        break;}
    QString naming=" -o \"%(title)s";
    if (int(ui->Format->currentIndex()==0 && !ui->mp4list->itemText(ui->mp4list->currentIndex()).isEmpty())){
        format=" -f "+mp4d[ui->mp4list->currentIndex()][5]+"+140 ";
        naming+= " ["+QRegularExpression("\\b\\d+\\.\\w+iB\\b").match(ui->mp4list->itemText(ui->mp4list->currentIndex())).captured(0)+"]";;
    }
    if (int(ui->Format->currentIndex()==2 && !ui->webmlist->itemText(ui->webmlist->currentIndex()).isEmpty())){
        format=" -f "+webmd[ui->webmlist->currentIndex()][5]+"+140 ";
        naming+=" ["+QRegularExpression("\\b\\d+\\.\\w+iB\\b").match(ui->webmlist->itemText(ui->webmlist->currentIndex())).captured(0)+"]";;
    }
    naming+="\"";
    QString vizov="yt-dlp"+naming+part+" -P ";
    std::string based = vizov.toStdString()+stdpath+format.toStdString()+ui->LINK->text().toStdString()+logs;
    //qDebug() << format;
    //qDebug() << based;
    system(based.c_str());
    }

}


void MainWindow::on_datacall_clicked()
{
    readwithlines(settings, &ckie, 3);
    readwithlines(settings, &broil, 1);
    if ((ui->LINK->text().toStdString().find("https://www.youtube.com/")!=0
         && ui->LINK->text().toStdString().find("https://youtube.com/")!=0
         && ui->LINK->text().toStdString().find("youtube.com/")!=0
         && ui->LINK->text().toStdString().find("youtu.be/")!=0
         && ui->LINK->text().toStdString().find("https://youtu.be/")!=0
         && ui->LINK->text().toStdString().find("https://www.youtu.be/")!=0
         && ui->LINK->text().toStdString().find("www.youtu.be/")!=0
         && ui->LINK->text().toStdString().find("www.youtube.com/")!=0)
        || ui->LINK->text().contains("&list")){}
    else{
        QProcess output;
        QStringList args={"-F"};
        if(ckie=="true")
            args<<"--cookies-from-browser"<<broil;
        args<<ui->LINK->text();
        output.setStandardOutputFile("data.txt");
        output.start("yt-dlp", args);
        output.waitForFinished();
        //qDebug() << args;
        QFile data("data.txt");
        int i=0, a=0;
        data.open(QIODevice::ReadOnly | QIODevice::Text);
        while(data.readLine().toStdString().find("---"));
        while(!data.atEnd()){
            T=data.readLine();
            if(T.contains("mp4") && !T.contains("audio")){
                mp4d[i][0]=T.split(' ').at(0);
                mp4d[i][1]=QRegularExpression("\\b\\d+x\\d+\\b").match(T).captured(0);
                if(T.contains("vp09")) {mp4d[i][2]="vp09";}
                if(T.contains("avc1")) {mp4d[i][2]="h264";}
                if(T.contains("av01")) {mp4d[i][2]="av01";}
                mp4d[i][3]=QRegularExpression("\\b\\w+k\\b").match(T).captured(0);
                mp4d[i][4]=" (≈"+QRegularExpression("\\b\\d+\\.\\w+iB\\b").match(T).captured(0)+")";
               // qDebug() << mp4d[i][0] << mp4d[i][1] << mp4d[i][2] << mp4d[i][3] << mp4d[i][4];
                i++;
            }
            if(T.contains("webm") && !T.contains("audio")){
                webmd[a][0]=T.split(' ').at(0);
                webmd[a][1]=QRegularExpression("\\b\\d+x\\d+\\b").match(T).captured(0);
                if(T.contains("vp9")) {webmd[a][2]="vp09";}
                if(T.contains("avc1")) {webmd[a][2]="h264";}
                if(T.contains("av01")) {webmd[a][2]="av01";}
                webmd[a][3]=QRegularExpression("\\b\\w+k\\b").match(T).captured(0);
                webmd[a][4]=" (≈"+QRegularExpression("\\b\\d+\\.\\w+iB\\b").match(T).captured(0)+")";
                a++;
            }
        }
        ui->mp4list->clear();
        ui->webmlist->clear();
        int m=0;
        for(int j=i-1; j>0; j--){
            QString tttemp;
            tttemp=mp4d[j][1]+" "+mp4d[j][3]+" "+mp4d[j][2]+mp4d[j][4];
            mp4d[m][5]=mp4d[j][0];
            ui->mp4list->addItem(tttemp);
            m++;
        }
        int w=0;
        for(int j=a-1; j>0; j--){
            QString tttemp;
            tttemp=webmd[j][1]+" "+webmd[j][3]+" "+webmd[j][2]+webmd[j][4];
            webmd[w][5]=webmd[j][0];
            ui->webmlist->addItem(tttemp);
            w++;
        }
        data.close();
    }

}




void MainWindow::on_LINK_textChanged()
{
    ui->mp4list->clear();
    ui->webmlist->clear();
}


void MainWindow::on_settings_clicked()
{
    int posx;
    if(this->pos().x()<320){
        posx=this->pos().x()+475;
    }
    else {posx=this->pos().x()-275;}
    options.move(posx, this->pos().y());
    options.show();
}


void MainWindow::on_pushButton_clicked()
{
    ui->LINK->clear();
    ui->LINK->setPlaceholderText("https://youtu.be/");
}




