
/**
 *  @file       main-cli.cc
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    0.1
 * 
 *  @brief ICP 2018, Project - Block Editor. CLI main source file.
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

// project headers
#include "utilities.h"
#include "port.h"
#include "blocks.h"
#include "scheme.h"
#include "scheduler.h"
#include "loader.h"

// commonly used std objects.. really no need to be careful about poluting the namespace
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::stoul;
using std::stod;


// GUI/CLI different handling switch
const Mode_t RUN_MODE {CLI_MODE};


/**
 * @brief CLI Main entry point
 * @param argc arg count
 * @param argv pointer to array of args
 * @return success/error code
 */
int main(int argc, char **argv)
{
    // // // // // // // // // // // // // // // // // // // // // // // // // // 
    headline(1, "BlockEditor 1.0");
    headline(0, "Commands: ");
    paragraph("Help  Show help and usage info.\nPrint  Print actual scheme.\nLoad <scheme>  Load the scheme.\nExit  Leave the program.\n");
    // // // // // // // // // // // // // // // // // // // // // // // // // // 

    // SPAWN THE ESSENTIAL BLOCK EDITOR OBJECTS: Loader, Scheduler & Command Handler
    std::shared_ptr<Loader>             loader;
    std::shared_ptr<Scheduler>          scheduler;
    std::unique_ptr<CommandHandler>     cmd;

    loader      = std::make_shared<Loader>();
    scheduler   = std::make_shared<Scheduler>();
    cmd         = std::make_unique<CommandHandler>(nullptr, loader, scheduler);

    // buffer for the input from user in the terminal
    string user_input;
    
    for(;;)
    {
        cout << "~> "; cin >> user_input;
        cmd->exec(user_input);
    }

    return SUCCESS;
}
