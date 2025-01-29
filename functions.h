#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QFile>
#include <mainwindow.h>
#include <QComboBox>

QFile settings("config.ini");


void readwithlines(QFile &dab, QString *text, int lines){
    dab.open(QIODevice::ReadOnly | QIODevice::Text);
    QString temp; int i=1;
    do{
        temp=dab.readLine();
        i++;
    }while(lines>=i);
    dab.close();
    *text=temp;
    if(lines>0 && lines<=3) text->resize(text->size()-1);
}

void boxclear(QComboBox *first, QComboBox *second, QComboBox *third){
    first->clear();
    second->clear();
    third->clear();
}

void putformat(QString formatd[][6], int &counter, QString T){
    formatd[counter][0]=T.split(' ').at(0);
    formatd[counter][1]=QRegularExpression("\\b\\d+x\\d+\\b").match(T).captured(0);
    if(T.contains("vp09") || T.contains("vp9")) {formatd[counter][2]="vp09";}
    else if(T.contains("avc1")) {formatd[counter][2]="h264";}
    else if(T.contains("av01")) {formatd[counter][2]="av01";}
    formatd[counter][3]=QRegularExpression("\\b\\w+k\\b").match(T).captured(0);
    formatd[counter][4]=" (≈"+QRegularExpression("\\b\\d+\\.\\w+iB\\b").match(T).captured(0)+")";
    counter++;
}

void putaudio(QString formatd[][6], int &counter, QString T){
    formatd[counter][0]=T.split(' ').at(0);
    //qDebug() << lang;
    formatd[counter][1]=QRegularExpression("\\[([^\\]]+)\\]\\s+([^,]+)").match(T).captured(0);
    counter++;
}

void additems(QString formatd[][6], int counter, QComboBox *list){
    int item=0;
    for(int j=counter-1; j>=0; j--){
        QString tttemp;
        tttemp=formatd[j][1]+" "+formatd[j][3]+" "+formatd[j][2]+formatd[j][4];
        formatd[item][5]=formatd[j][0];
        list->addItem(tttemp);
        item++;
    }
}



#endif // FUNCTIONS_H
