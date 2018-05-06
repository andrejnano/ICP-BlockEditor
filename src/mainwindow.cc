/**
 *  @file       mainwindow.cc
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    1.0
 * 
 *  @brief ICP 2018, Project - Block Editor. Mainwindow class.
 *  
 *  @section Description
 * 
 *  @section Usage
 *  
 */

#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

#include <math.h>

#include "blocks.h"
#include "scheme.h"
#include "loader.h"
#include "scheduler.h"
#include "utilities.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "blockview.h"
#include "wireview.h"
#include "portview.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // // // // // // // // // // // // // // // // // // // // // // // // // //

    // SPAWN THE ESSENTIAL BLOCK EDITOR OBJECTS: Loader, Scheduler & Command Handler
    // Command Handler pointer is a private member of the MainWindow during GUI Mode

    // Loader is an object handling file->schema or schema->file conversions [LOAD/SAVE].
    // It is also able to create blank new scheme.
    loader = std::make_shared<Loader>();

    // Scheduler is an object managing the order of computation in the scheme.
    // It is able to run, step and undo the commands, it also checks for cycles in the scheme.
    scheduler = std::make_shared<Scheduler>();

    // Command Handler is an interface to the application logic.
    // It can be used both by GUI and CLI, using the same commands.
    // Depending on the run mode, the commands are interpreted in a different way.
    // Additionally, it's job is to connect the Loader with the Scheduler.
    cmd = std::make_unique<CommandHandler>(ui, loader, scheduler);

    // // // // // // // // // // // // // // // // // // // // // // // // // //

    // open the main menu
    QWidget *main_menu_page = ui->main_menu_page;
    ui->stackedWidget->setCurrentWidget(main_menu_page);
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

    QGraphicsView* view = ui->view;
    view->setRenderHint(QPainter::Antialiasing);
    view->setScene(new QGraphicsScene());

    QBrush bgcolor(QColor(9, 12, 29));
    view->setBackgroundBrush(bgcolor);

    view->setSceneRect(0,0,view->size().width(), view->size().height());

    // get the current scheme ptr
    std::shared_ptr<Scheme> currentScheme = scheduler->currentScheme();


    // Create visual representation of the blocks, ports and wires in the scheme.
    if (currentScheme->getBlockPointers().empty())
    {
        view->show();
        return;
    }

    // store all the blocks and ports for easy access
    std::vector<BlockView*> blockviewlist;
    std::vector<PortView*> portviewlist;

    BlockView* blockview {nullptr};
    int offset_x = 10;
    int offset_y = 10;

    for (auto block_ptr : currentScheme->getBlockPointers())
    {
        BlockView* blockview = new BlockView(block_ptr); // dealloc?
        blockview->setPos(QPoint(offset_x, offset_y));
        offset_x += 110;
        view->scene()->addItem(blockview);
        blockviewlist.push_back(blockview);

        // in port draw
        for (auto port_ptr : block_ptr->getInPorts())
        {
            // add portview to the blockview and save the pointer to the list
            portviewlist.push_back(blockview->addPort(port_ptr, false));
        }

        // out port draw
        for (auto port_ptr : block_ptr->getOutPorts())
        {
            // add portview to the blockview and save the pointer to the list
            portviewlist.push_back(blockview->addPort(port_ptr, true));
        }
    }

//    // in case there is nothing to show
//    if (currentScheme->getWires().empty())
//    {
//        view->show();
//        return;
//    }

    view->show();
}

/*****************************************************************************/
// Editor Commands
/*****************************************************************************/
void MainWindow::on_step_btn_clicked()
{
    cmd->exec("step");
    update();
}

void MainWindow::on_undo_btn_clicked()
{
    cmd->exec("undo");
    update();
}

void MainWindow::on_add_block_btn_clicked()
{
    cmd->exec("add");
    editor();
}

void MainWindow::on_save_scheme_btn_clicked()
{
    cmd->exec("save");
    update();
}


/*****************************************************************************/
// BUTTONS / NAVIGATION / LINKS
/*****************************************************************************/

// show help page
void MainWindow::on_help_menu_btn_clicked()
{
    //QWidget *help_page = ui->help_page;
    //ui->stackedWidget->setCurrentWidget(help_page);
    QMessageBox::about(this, tr("BlockEditor"),
                       tr("Hello <b> This is a test </b>. "
                          "....."));
}

void MainWindow::on_editor_menu_btn_clicked()
{
    editor();
}




// start the editor with new scheme
void MainWindow::on_new_scheme_btn_clicked()
{
    cmd->exec("new");
    editor();
}


// change page to the load page
void MainWindow::on_load_scheme_btn_clicked()
{
    QWidget *load_scheme_page = ui->load_scheme_page;
    ui->stackedWidget->setCurrentWidget(load_scheme_page);
}


// just load the filename into the textbox
void MainWindow::on_load_file_btn_clicked()
{
    // open a file dialog
    QString fileName = QFileDialog::getOpenFileName(this, "Open Scheme",  QDir::currentPath(), "Block Scheme Files (*.scheme *.sch)");

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

    // the scheme was loadeed and then bound to the scheduler
    // it may be now used by executing the scheduler commands
    editor();
}


// go back to main menu
void MainWindow::on_main_menu_btn_clicked()
{
    // main menu page
     QWidget *main_menu_page = ui->main_menu_page;
     ui->stackedWidget->setCurrentWidget(main_menu_page);
}
