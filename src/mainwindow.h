#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// #include <QMainWindow>
#include <QFile>
#include <QMainWindow>

//cmd forward declaration
class CommandHandler;

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    // button actions
    void on_new_scheme_btn_clicked();
    void on_load_scheme_btn_clicked();
    void on_load_file_btn_clicked();
    void on_open_file_btn_clicked();
    void on_main_menu_btn_clicked();

    // the visual representation of the scheme
    void editor();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<CommandHandler> cmd;
};

#endif // MAINWINDOW_H
