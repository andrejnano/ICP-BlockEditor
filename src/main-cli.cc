
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
    cmd = std::make_unique<CommandHandler>(nullptr, loader, scheduler);

    // buffer for the input from user in the terminal
    string user_input;
    
    // Interpreting user commands from the terminal. Runs until the 'EXIT' command is called or error occurs.
    for(;;)
    {
        cout << "~> "; cin >> user_input;
        cmd->exec(user_input);
    }

    return SUCCESS;
}
