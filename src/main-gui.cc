/**
 *  @file       main-gui.cc
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    1.0
 * 
 *  @brief ICP 2018, Project - Block Editor. GUI main source file.
 *  
 *  @section Description
 * 
 *  @section Usage
 *  
 */

// std libraries
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>

// Qt Libraries
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

// project headers
#include "utilities.h"
#include "port.h"
#include "blocks.h"
#include "scheme.h"
#include "scheduler.h"
#include "loader.h"

// Project GUI header
#include "mainwindow.h"

// GUI/CLI different handling switch
const Mode_t RUN_MODE {GUI_MODE};


/**
 * @brief GUI Main entry point
 * @param argc arg count
 * @param argv pointer to array of args
 * @return success/error code
 */
int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    // main app window
    MainWindow w;
    w.show();

    return a.exec();
}
