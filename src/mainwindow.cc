#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>

#include <QFileDialog>
#include <QTextStream>

#include "scheme.h"
#include "loader.h"
#include "scheduler.h"
#include "utilities.h"

#include "mainwindow.h"
#include "visualblock.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // SPAWN THE ESSENTIAL BLOCK EDITOR OBJECTS: Loader, Scheduler & Command Handler
    std::shared_ptr<Loader>             loader;
    std::shared_ptr<Scheduler>          scheduler;

    loader      = std::make_shared<Loader>();
    scheduler   = std::make_shared<Scheduler>();
    cmd         = std::make_unique<CommandHandler>(ui, loader, scheduler);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*****************************************************************************/
// BLOCK EDITOR | loads the scheme and works with it
/*****************************************************************************/

void MainWindow::editor()
{
    // change the page
    QWidget *editor_page = ui->editor_page;
    ui->stackedWidget->setCurrentWidget(editor_page);

    // draw all the blocks corresponding to the scheme

}


/*****************************************************************************/
// BUTTONS / NAVIGATION / LINKS
/*****************************************************************************/

// start the editor with new scheme
void MainWindow::on_new_scheme_btn_clicked()
{
    // create new scheme
    cmd->exec("new");
    editor();
}


// change page to load page
void MainWindow::on_load_scheme_btn_clicked()
{
    // create new scheme
    QWidget *load_scheme_page = ui->load_scheme_page;

    ui->stackedWidget->setCurrentWidget(load_scheme_page);

}


// just load the filename into the textbox
void MainWindow::on_load_file_btn_clicked()
{
    // open a file dialog
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Scheme"), "~/", tr("Block Scheme Files (*.scheme *.sch)"));

    // store the text inside a text field
    // now it is editable manually or just can be opened by clicking
    // the button next to it
    ui->lineEdit->setText( fileName );
}


// load the scheme in to the loader and start the editor
// also bind the scheme
void MainWindow::on_open_file_btn_clicked()
{
    QString fileName = ui->lineEdit->text();

    QFile file (fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->lineEdit->setText("ERROR: Cannot open the file !");
        return;
    }

    // gui 'load' case, takes input from the input box
    cmd->exec("load");

    editor();
}


// go back to main menu
void MainWindow::on_main_menu_btn_clicked()
{
    // main menu page
     QWidget *main_menu_page = ui->main_menu_page;
     ui->stackedWidget->setCurrentWidget(main_menu_page);
}
