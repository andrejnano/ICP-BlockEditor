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


class GridLockScene : public QGraphicsScene
{
 private:
    const QSize cellSize;
    QGraphicsItem* DraggedItem;
    QPointF DragOffset;

 public:
    GridLockScene() : cellSize(100,100) {}

 protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
};


void GridLockScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    qreal left = int(rect.left()) - (int(rect.left()) % cellSize.width());
    qreal top = int(rect.top()) - (int(rect.top()) % cellSize.height());

    QVarLengthArray<QLineF, 100> lines;

    for (qreal x = left; x < rect.right(); x += cellSize.width())
    {
        lines.append(QLineF(x, rect.top(), x, rect.bottom()));
    }

    for (qreal y = top; y < rect.bottom(); y += cellSize.height())
    {
        lines.append(QLineF(rect.left(), y, rect.right(), y));
    }

    painter->setPen(Qt::lightGray);
    painter->drawLines(lines.data(), lines.size());
}


void GridLockScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    // try to get item where the mouse clicks
    DraggedItem = qgraphicsitem_cast<QGraphicsItem*>(itemAt(mouseEvent->scenePos(), QTransform()));

    // if there was an item,
    if (DraggedItem)
    {
        DragOffset = mouseEvent->scenePos() - DraggedItem->pos();
    }
    else
    {
        QGraphicsScene::mousePressEvent(mouseEvent);
    }
}

void GridLockScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (DraggedItem)
    {
        // Ensure that the item's offset from the mouse cursor stays the same.
        DraggedItem->setPos(mouseEvent->scenePos() - DragOffset);
    }
    else
    {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void GridLockScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (DraggedItem) {
        int x = floor(mouseEvent->scenePos().x() / cellSize.width()) * cellSize.width();
        int y = floor(mouseEvent->scenePos().y() / cellSize.height()) * cellSize.height();
        DraggedItem->setPos(x, y);
        DraggedItem = 0;
    } else
        QGraphicsScene::mouseReleaseEvent(mouseEvent);
}




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
    for (auto block_ptr : currentScheme->getBlockPointers())
    {
        BlockView* blockview = new BlockView(block_ptr); // dealloc?
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

    // in case there is nothing to show
    if (currentScheme->getWires().empty())
    {
        view->show();
        return;
    }

    WireView* wireview {nullptr};
    for (auto wire: currentScheme->getWires())
    {
        for (auto blockview_first : blockviewlist) // every block SOURCE/TARGET
            for (auto blockview_second : blockviewlist) // every other block TARGET/SOURCE
            {
                // the first is source
                if ( blockview_first->getDataBlock()->getBlockID() == wire.id_out && blockview_second->getDataBlock()->getBlockID() == wire.id_in)
                {
                    for(auto portview_first : portviewlist)
                        for(auto portview_second : portviewlist)
                        {
                            if (portview_first->getParentBlock() == blockview_first && portview_first->getId() == wire.index_out)
                                if (portview_second->getParentBlock() == blockview_second && portview_second->getId() == wire.index_in)
                                {
                                    wireview = new WireView(0);
                                    wireview->setSourcePort(portview_first);
                                    wireview->setDestPort(portview_second);

                                    portview_first->setCurrentWire(wireview);
                                    portview_second->setCurrentWire(wireview);

                                    view->scene()->addItem(wireview);
                                }
                        }
                }
                else if ( blockview_first->getDataBlock()->getBlockID() == wire.id_in && blockview_second->getDataBlock()->getBlockID() == wire.id_out)
                {
                    for(auto portview_first : portviewlist)
                        for(auto portview_second : portviewlist)
                        {
                            if (portview_first->getParentBlock() == blockview_first && portview_first->getId() == wire.index_in)
                                if (portview_second->getParentBlock() == blockview_second && portview_second->getId() == wire.index_out)
                                {
                                    wireview = new WireView(0);
                                    wireview->setSourcePort(portview_first);
                                    wireview->setDestPort(portview_second);

                                    portview_first->setCurrentWire(wireview);
                                    portview_second->setCurrentWire(wireview);

                                    view->scene()->addItem(wireview);
                                }
                        }
                }
            }
    }


    // VERY CHAOTIC SOLUTION ...



//    WireView* wireview {nullptr};
//    for (auto wire: currentScheme->getWires())
//    {
//        unsigned SourceBlockID = wire->id_out;
//        unsigned TargetBlockID = wire->id_in;
//        unsigned SourcePortIDX = wire->index_out;
//        unsigned TargetPortIDX = wire->index_in;


//        // check every block in the scene for ID
//        foreach(QGraphicsItem *item, view->scene()->items())
//        {
//            BlockView* blockview = qgraphicsitem_cast<BlockView *>(item);
//            if (!blockview) continue;

//            // get ptr to the data model
//            auto direct_block_ptr = blockview->getDataBlock();

//            if ( direct_block_ptr->getBlockID() == SourceBlockID || direct_block_ptr->getBlockID() == TargetBlockID)
//            {
//                bool isSource = direct_block_ptr->getBlockID() == SourceBlockID ? true : false;

//                foreach(QGraphicsItem *item2, view->scene()->items())
//                {
//                    BlockView* blockview2 = qgraphicsitem_cast<BlockView *>(item2);
//                    if (!blockview2) continue;

//                    // get ptr to the data model
//                    auto direct_block_ptr2 = blockview2->getDataBlock();

//                    if (isSource && direct_block_ptr2->getBlockID() == TargetBlockID)
//                    {
//                        for ()
//                            blockview1
//                        WireView *wireview = new WireView();
//                        wireview->
//                    }
//                    else
//                    if (direct_block_ptr2->getBlockID() == SourceBlockID)
//                    {

//                    }

//        }


//        WireView* wireview = new WireView(this); // dealloc?
//        wireview->
//        view->scene()->addItem(wireview);
//    }

    view->show();
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
    QString fileName = QFileDialog::getOpenFileName(this, "Open Scheme",  QString(), "Block Scheme Files (*.scheme *.sch)");

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
