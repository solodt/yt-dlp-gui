#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>

namespace Ui {
class Browser;
}

class Browser : public QWidget
{
    Q_OBJECT

public:
    explicit Browser(QWidget *parent = nullptr);
    ~Browser();

private slots:
    void on_Firefox_pressed();

    void on_Opera_pressed();

    void on_Chrome_pressed();

    void on_Edge_pressed();

    void on_Safari_pressed();

    void on_Chromium_pressed();

    void on_Whale_pressed();

    void on_Vivaldi_pressed();

    void on_Brave_pressed();

    void on_pathbutton_clicked();

    void on_checkBox_checkStateChanged(const Qt::CheckState &arg1);

    void on_checkBox_2_stateChanged(int arg1);

private:
    Ui::Browser *ui;
};

#endif // OPTIONS_H
