#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "functions.h"
#include <QDir>
#include <QFileDialog>
#include <windows.h>
#include <QTextCodec>
#include <QRegularExpression>
#include <QProcess>
#include <QtConcurrent>
QString path, broil,
    ckie, format,
    formatd[3][30][6],
    T, lage;
std::string logs;

const int mp4=0, webm=1, audio=2;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setTabEnabled(2, false);
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void dload(std::string beb){
    system(beb.c_str());
}

void fchange(QComboBox *list, QString &naming, QComboBox *first, QComboBox *second, QComboBox *third){
    if(int(list->currentIndex())==0 && !first->itemText(first->currentIndex()).isEmpty()){
        format=" -f "+formatd[mp4][first->currentIndex()][5];
        naming+= " ["+QRegularExpression("\\b\\d+\\.\\w+iB\\b").match(first->itemText(first->currentIndex())).captured(0)+"]";
        if(!third->itemText(third->currentIndex()).isEmpty()){
            format+="+"+formatd[audio][third->currentIndex()][5]+" ";
            naming+=" "+third->itemText(third->currentIndex()).trimmed();
        } else format+="+140 ";
    }

    if(int(list->currentIndex())==1 && !third->itemText(third->currentIndex()).isEmpty()){
        format=" -f "+formatd[audio][third->currentIndex()][5]+" ";
        naming+=" "+third->itemText(third->currentIndex()).trimmed()+".mp3";
    }


    if(int(list->currentIndex())==2 && !second->itemText(second->currentIndex()).isEmpty()){
        format=" -f "+formatd[webm][second->currentIndex()][5];
        naming+= " ["+QRegularExpression("\\b\\d+\\.\\w+iB\\b").match(second->itemText(second->currentIndex())).captured(0)+"]";
        if(!third->itemText(third->currentIndex()).isEmpty()){
            format+="+"+formatd[audio][third->currentIndex()][5]+" ";
            naming+=" "+third->itemText(third->currentIndex()).trimmed();
        } else format+="+140 ";

}
}


void MainWindow::on_download_clicked(){
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
    QString naming=" -o \"%(title)s";
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
        fchange(ui->Format, naming, ui->mp4list, ui->webmlist, ui->audiolist);
        naming+="\"";
        std::string call="yt-dlp"+naming.toStdString();
        if(ckie=="true") call+=" --cookies-from-browser "+broil.toStdString();
        call+=" -P "+stdpath+format.toStdString()+ui->LINK->text().toStdString();
        if(lage=="true") call+=" > log.txt";
        //qDebug() << call;
        Q_UNUSED(QtConcurrent::run(dload, call));
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
        int cmp4=0, cwebm=0, cdub=0;
        data.open(QIODevice::ReadOnly | QIODevice::Text);
        while(data.readLine().toStdString().find("-----"));

        while(!data.atEnd()){
            T=data.readLine();
            if(T.contains("mp4") && !T.contains("audio") && T.contains("video only")){
                putformat(formatd[mp4], cmp4, T);}
            else if(T.contains("webm") && !T.contains("audio")){
                putformat(formatd[webm], cwebm, T);}
            else if(T.contains(QRegularExpression("140-\\d"))){
                ui->tabWidget->setTabEnabled(2, true);
                putaudio(formatd[audio], cdub, T);}
        }
        boxclear(ui->mp4list, ui->webmlist, ui->audiolist);
        additems(formatd[mp4], cmp4, ui->mp4list);
        additems(formatd[webm], cwebm, ui->webmlist);
        additems(formatd[audio], cdub, ui->audiolist);
        data.close();
    }

}





void MainWindow::on_LINK_textChanged()
{
    if(ui->tabWidget->currentIndex()==2) ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabEnabled(2, false);

    boxclear(ui->mp4list, ui->webmlist, ui->audiolist);
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

