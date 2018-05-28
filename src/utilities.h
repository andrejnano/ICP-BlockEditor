/**
 *  @file       utilities.h
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    1.0
 * 
 *  @brief ICP 2018, Project - Block Editor. Utilities header.
 *  
 *  @section Description
 *  
 */

#ifndef BLOCKEDITOR_MISC_H_
#define BLOCKEDITOR_MISC_H_

#include <string>
#include <cstdio>  //required for printf
#include <memory>

// commonly used std objects..
using std::string;

#include "scheduler.h"
#include "loader.h"

// qt
#include "ui_mainwindow.h"

enum Err_code_t
{
  // default success exit
  SUCCESS         = 0,

  // internal application errors
  E_INTERNAL      = 11,
  E_FILE_IO       = 12,
  E_UNDEF         = 13,

  // block schema specific
  E_SCHEMA_LOAD   = 21,
  E_SCHEMA_SAVE   = 22,
  E_SCHEMA_OTHER  = 23,

  // block specific 
  E_BLOCK_CREATE  = 31,
  E_BLOCK_WORK    = 32,

  // scheduler specific
  E_SCHEDULER     = 40

};

// usage: cout << CL::OKGREEN << "some text" << CL::ENDC << ... 
namespace CL {
  auto const OKBLUE     = "\033[94m";
  auto const OKGREEN    = "\033[92m";
  auto const WARNING    = "\033[93m";
  auto const FAIL       = "\033[91m";
  auto const ENDC       = "\033[0m";
  auto const BOLD       = "\033[1m";
  auto const UNDERLINE  = "\033[4m";
}

// default is to exit, but can be turned of by passing false
void error(Err_code_t error_code, string error_msg, bool do_exit=false);

// show help and usage informations
void help();

// printout separator line
void separator(int chosen_char);

// printout headline
void headline(int chosen_char, string headline_text);

// printout paragraph offset text
void paragraph(string text);


// Application run modes
enum Mode_t 
{ 
    GUI_MODE = 0, 
    CLI_MODE = 1
};

// definition is inside the corresponding main [main-cli/main-gui]
extern const Mode_t RUN_MODE;

// All the possible commands, both for GUI && CLI
enum Command_t
{
    INVALID,
    HELP,
    SAVE,
    LOAD,
    NEW,
    PRINT,
    ADD,
    RM,
    ADD_IN,
    ADD_OUT,
    RM_IN,
    RM_OUT,
    CONNECT,
    DISCONNECT,
    SET,
    COMPUTE,
    BIND,
    SCHEDULE,
    CHECK,
    SET_FREE,
    STEP,
    RUN,
    UNDO,
    EXIT,
    RESET
};


class CommandHandler
{
private:
    Ui::MainWindow *ui; // if it's gui this points to the UI
    
    // loader & scheduler that has to be used by commands
    std::shared_ptr<Loader> loader;
    std::shared_ptr<Scheduler> scheduler;
    
    // evaluates the string and finds the corresponding Command
    Command_t eval(string command);

public:
    CommandHandler(
        Ui::MainWindow *ui_passed,
        std::shared_ptr<Loader> used_loader, 
        std::shared_ptr<Scheduler> used_scheduler
    ) :
        ui {ui_passed},
        loader {used_loader}, 
        scheduler {used_scheduler}
    {}

    // execute the supplied command
    bool exec(string command);

};



#endif // BLOCKEDITOR_MISC_H_
