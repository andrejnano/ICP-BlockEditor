#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <scheme.h>

#include <QMainWindow>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_new_scheme_btn_clicked();
    void on_load_scheme_btn_clicked();
    void on_load_file_btn_clicked();
    void on_open_file_btn_clicked();
    void on_main_menu_btn_clicked();

    void editor(Scheme* scheme);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
