#include "options.h"
#include "ui_options.h"
#include <QFile>
#include <QFileDialog>
#include <QDir>
QString broiler, Path, cook, loge;

QFile set("config.ini");

void readwithlines1(QFile &dab, QString *text, int lines){
    dab.open(QIODevice::ReadOnly | QIODevice::Text);
    QString temp; int i=1;
    do{
        temp=dab.readLine();
        i++;
    }while(lines>=i);
    dab.close();
    *text=temp;
    if(lines>=1 && lines<=3) text->resize(text->size()-1);
}

void writewithlines1(QFile &dab, QString text1, QString text2, QString text3, QString text4){
    dab.open(QIODevice::WriteOnly | QIODevice::Text);
    dab.write(text1.toUtf8()+"\n");
    dab.write(text2.toUtf8()+"\n");
    dab.write(text3.toUtf8()+"\n");
    dab.write(text4.toUtf8());
    dab.close();
}

Browser::Browser(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Browser)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    if(!set.exists()){
        set.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&set);
        out <<"firefox\n\nfalse\nfalse";
        set.close();
    }
    readwithlines1(set, &broiler, 1);
    readwithlines1(set, &Path, 2);
    readwithlines1(set, &cook, 3);
    readwithlines1(set, &loge, 4);
    if(loge=="true") ui->checkBox_2->setChecked(true);
    if(cook=="true") ui->checkBox->setChecked(true);
    else ui->checkBox->setChecked(false);
    ui->PathL->setMarkdown(Path);
    if(broiler=="firefox") ui->Firefox->setChecked(true);
    if(broiler=="opera") ui->Opera->setChecked(true);
    if(broiler=="chrome") ui->Chrome->setChecked(true);
    if(broiler=="chromium") ui->Chromium->setChecked(true);
    if(broiler=="edge") ui->Edge->setChecked(true);
    if(broiler=="safari") ui->Safari->setChecked(true);
    if(broiler=="whale") ui->Whale->setChecked(true);
    if(broiler=="vivaldi") ui->Vivaldi->setChecked(true);
    if(broiler=="brave") ui->Brave->setChecked(true);
}

void check(QString browser){
    broiler=browser;
    writewithlines1(set, broiler, Path, cook, loge);
}

Browser::~Browser()
{
    delete ui;
}

void Browser::on_Firefox_pressed()
{
    check("firefox");
}


void Browser::on_Opera_pressed()
{
    check("opera");
}


void Browser::on_Chrome_pressed()
{
     check("chrome");
}


void Browser::on_Edge_pressed()
{
     check("edge");
}


void Browser::on_Safari_pressed()
{
     check("safari");
}


void Browser::on_Chromium_pressed()
{
     check("chromium");
}


void Browser::on_Whale_pressed()
{
     check("whale");
}


void Browser::on_Vivaldi_pressed()
{
     check("vivaldi");
}


void Browser::on_Brave_pressed()
{
     check("brave");
}


void Browser::on_pathbutton_clicked()
{
    QString temp = QFileDialog::getExistingDirectory();
    if(temp.isEmpty()){}
        else{
    Path=temp;
       // qDebug() << broiler << Path << cook;
    writewithlines1(set, broiler, Path, cook, loge);
    ui->PathL->setMarkdown(Path);}
}


void Browser::on_checkBox_checkStateChanged(const Qt::CheckState &arg1)
{
    if(int(bool(arg1))==1) cook="true";
    if(int(bool(arg1))==0) cook="false";
    writewithlines1(set, broiler, Path, cook, loge);
    //qDebug() << cook;
}


void Browser::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1==2) loge="true";
    else loge="false";
    writewithlines1(set, broiler, Path, cook, loge);
    }

