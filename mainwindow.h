#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "options.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_download_clicked();

    void on_datacall_clicked();

    void on_LINK_textChanged();

    void on_settings_clicked();

    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;
    Browser options;
};

#endif // MAINWINDOW_H
