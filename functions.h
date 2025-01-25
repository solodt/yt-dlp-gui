#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QFile>
#include <mainwindow.h>

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




#endif // FUNCTIONS_H
