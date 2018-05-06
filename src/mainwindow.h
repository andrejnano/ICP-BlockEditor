/**
 *  @file       mainwindow.h
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    1.0
 * 
 *  @brief ICP 2018, Project - Block Editor. Mainwindow class header.
 *  
 *  @section Description
 * 
 *  @section Usage
 *  
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

// #include <QMainWindow>
#include <QFile>
#include <QMainWindow>

//cmd forward declaration
class CommandHandler;
class Loader;
class Scheduler;

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
    void on_help_menu_btn_clicked();
    void on_editor_menu_btn_clicked();
    // editor menu actions
    void on_step_btn_clicked();
    void on_undo_btn_clicked();
    void on_add_block_btn_clicked();
    void on_save_scheme_btn_clicked();

    // the visual representation of the scheme
    void editor();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<CommandHandler> cmd;
    std::shared_ptr<Loader>             loader;
    std::shared_ptr<Scheduler>          scheduler;
};

#endif // MAINWINDOW_H
