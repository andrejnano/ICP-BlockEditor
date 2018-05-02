#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>

#include <QFileDialog>
#include <QTextStream>

#include <scheme.h>
#include "mainwindow.h"
#include "visualblock.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*****************************************************************************/
// BLOCK EDITOR | loads the scheme and works with it
/*****************************************************************************/

void MainWindow::editor(Scheme *scheme)
{
    // change the page
    QWidget *editor_page = ui->editor_page;
    ui->stackedWidget->setCurrentWidget(editor_page);

    QGraphicsScene * scene = new QGraphicsScene();

    // create an item to put into the scene
    VisualBlock * rect = new VisualBlock();
    rect->setRect(10,10,50,100);

    scene->addItem(rect);

    // make block focusable
    //->setFlag(Q)

    QGraphicsTextItem * text = new QGraphicsTextItem();
    QString temp = QString::fromStdString(scheme->getName());
    text->setPlainText(temp);

    scene->addItem(text);

    // add a view
    QGraphicsView * view = ui->graphicsView;
    view->setScene(scene);
    view->show();
}


/*****************************************************************************/
// BUTTONS / NAVIGATION / LINKS
/*****************************************************************************/

// start the editor with new scheme
void MainWindow::on_new_scheme_btn_clicked()
{
    // create new scheme
    Scheme *actual_scheme = new Scheme("New Scheme");
    editor(actual_scheme);
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
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("Open Scheme"), "~/", tr("Block Scheme Files (*.scheme *.xml)"));

     ui->lineEdit->setText( fileName );

     QFile file( fileName );
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return;
}


// load the scheme
void MainWindow::on_open_file_btn_clicked()
{
    QString fileName = ui->lineEdit->text();

    QFile file (fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;


    // temp scheme solution..

    // loader should be implemented here and then, schema passed to the editor
    Scheme * loaded_schema = new Scheme("Loaded Schema");
    // start the editor with loded file
    editor(loaded_schema);
}


// go back to main menu
void MainWindow::on_main_menu_btn_clicked()
{
    // main menu page
     QWidget *main_menu_page = ui->main_menu_page;
     ui->stackedWidget->setCurrentWidget(main_menu_page);
}
