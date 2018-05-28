/**
 *  @file       utilities.cc
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    1.0
 * 
 *  @brief ICP 2018, Project - Block Editor. Utilities.
 *  
 *  @section Description
 * 
 */

#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "utilities.h"


// commonly used std objects.. really no need to be careful about poluting namespace
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;


/**
 * @brief error output wrapper
 * @param error_code
 * @param error_msg
 * @param do_exit
 */
void error(Err_code_t error_code, string error_msg, bool do_exit)
{
  cout << " Error " << error_code << " >> " << error_msg << endl;
  do_exit ? exit(error_code) : void();
}

/**
 * @brief help output for cli
 */
void help()
{
  cout << "\n" << CL::BOLD << CL::UNDERLINE << "BlockEditor" << CL::ENDC << "\n\n"
    << "Description will go here\n\n" << "Commands: \n\n" << "- help\t Show help and usage info.\n\n"
    << "- save <schema_path>\t Save schema to the specified path.\n\n"
    << "- load <schema_path>\t Load schema at the specified path.\n\n"
    << "- print\t Print actual scheme.\n\n"
    << "- add <block_type>\t Add new block of specified type.\n\n"
    << "- rm <block_id>\t Removes block with given ID.\n\n"
    << "- add-in <block_id>\t Add new input port to specified block.\n\n"
    << "- add-out <block_id>\t Add new output port to specified block.\n\n"
    << "- rm-in <block_id> <port_index>\t Removes input port at specified index in block.\n\n"
    << "- rm-out <block_id> <port_index>\t Removes output port at specified index in block.\n\n"
    << "- connect <src_id> <src_index> <dst_id> <dst_index>\t Make connection between two specified ports.\n\n"
    << "- rm-wire <src_id> <src_index> <dst_id> <dst_index>\t Removes connection between two specified ports.\n\n"
    << "- set <block_id> <port_index> <value>\t Set value to specified input port.\n\n"
    << "- compute <block_id>\t Compute block operation and propagate result.\n\n"
    << "- sch-load\t Loads actual blocks to scheduler.\n\n"
    << "- sch-print\t Prints ID of blocks stored in scheduler.\n\n"
    << "- check\t Check if actual scheme contains any cycle.\n\n"
    << "- set-free\t Asks for values of free input ports.\n\n"
    << "- step\t Computes next prepared block.\n\n"
    << "- exit\t Exit the application.\n"
    << endl;
}

/**
 * @brief cli output separator
 * @param chosen_char character to use to separate
 */
void separator(int chosen_char)
{
  char separators[]
  {
    '~',
    '-',
    '_',
    '#',
    '@'
  };

  if (chosen_char < 0 || chosen_char >= static_cast<int>(strlen(separators)))
  {
    std::cerr << "Index is out of the range of array of chars." << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << std::setfill (separators[chosen_char]) << std::setw(80);
  std::cout << " " << std::endl;
  std::cout << std::setfill (' ') << std::setw(80);
  std::cout << " " << std::endl;
  std::cout << std::setfill (separators[chosen_char]) << std::setw(80);
  std::cout << " " << std::endl;
}

/**
 * @brief cli headline output
 * @param chosen_char
 * @param headline_text
 */
void headline(int chosen_char, std::string headline_text)
{
  char separators[]
  {
    ' ',
    '~',
    '-',
    '#',
    '@'
  };

  if (chosen_char < 0 || chosen_char >= static_cast<int>(strlen(separators)))
  {
    std::cerr << "Index is out of the range of array of chars." << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << std::setfill (separators[chosen_char]) << std::setw(80);
  std::cout << " " << std::endl;
  std::cout << std::setfill (' ') << std::setw(10);
  std::cout << CL::BOLD << headline_text << CL::ENDC;
  std::cout << " " << std::endl;
  std::cout << std::setfill (separators[chosen_char]) << std::setw(80);
  std::cout << " " << std::endl;
}

/**
 * @brief cli paragraph output
 * @param text
 */
void paragraph(std::string text)
{
    std::istringstream f(text);
    std::string line;

    while (std::getline(f, line))
        std::cout << "\t" << line << std::endl;

    std::cout << std::endl;
}


/***********************************************************************/
// COMMAND HANDLING
/***********************************************************************/

/**
 * @brief Command handler interface for executing command both for GUI & CLI
 * @param command command to be executed
 */
bool CommandHandler::exec(string command)
{
    // lowercase it
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);

    // evaluate it
    Command_t cmd = eval(command);

    // get current scheme access ptr
    std::shared_ptr<Scheme> active_scheme = scheduler->currentScheme();


    // Most of the commands require a scheme to be active
    // In case it is not active, it would be unnecessary to go through
    // the whole switch case.
    switch (cmd)
    {
        // (Only INVALID, HELP, LOAD, NEW and EXIT do not require an active scheme)
        case INVALID:
        case HELP:
        case LOAD:
        case NEW:
        case EXIT:
            break;
        default:
        {
            if (!active_scheme)
            {
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                error(E_SCHEMA_OTHER, "No scheme active!");
                return false;
            }
            break;
        }
    }

    // GUI SPECIFIC COMMAND EXECUTION
    if (RUN_MODE == GUI_MODE)
    {
        switch (cmd)
        {
            case INVALID:
            {
                QMessageBox messageBox;
                messageBox.critical(0,"Error","Unknown command received by the Command Handler!");
                messageBox.setFixedSize(500,200);
                return true;
            }

            case HELP:
            {
                // change the page
                QWidget *help_page = ui->help_page;
                ui->stackedWidget->setCurrentWidget(help_page);
                break;
            }

            case SAVE:
            {

                QString fileName = QFileDialog::getSaveFileName(ui->editor_page, "Save Scheme",  QDir::currentPath(), "Block Scheme Files (*.scheme *.sch)");
                loader->saveScheme(fileName.toStdString(), active_scheme);
                break;
            }

            case LOAD:
            {
                std::string scheme_file_path = ui->lineEdit->text().toStdString();
                
                active_scheme = loader->loadScheme(scheme_file_path);

                if (active_scheme)
                {
                    scheduler->bindScheme(active_scheme, ui->editor_page);
                }
                else
                {
                    QMessageBox messageBox;
                    messageBox.critical(0,"Error","Scheme could not be loaded.");
                    messageBox.setFixedSize(500,200);
                    return false;
                }
                break;
            }

            case NEW:
            {
                active_scheme = loader->createScheme("new_scheme"); 
                scheduler->bindScheme(active_scheme);
                break;
            }

            case ADD:
            {
                bool status;

                QString operation_input = QInputDialog::getText(ui->editor_page, "BlockEditor prompt", "Choose the operation: 'SUM', 'AVG', 'MIN', 'MAX', 'COUNT':", QLineEdit::Normal, "", &status);

                std::string operation = operation_input.toStdString();
                // lowercase it
                std::transform(operation.begin(), operation.end(), operation.begin(), ::tolower);

                if ( operation == "sum") active_scheme->addBlock(SUM, t_simple, t_simple);
                else
                if ( operation == "avg") active_scheme->addBlock(AVG, t_simple, t_simple);
                else
                if ( operation == "min") active_scheme->addBlock(MIN, t_simple, t_simple);
                else
                if ( operation == "max") active_scheme->addBlock(MAX, t_simple, t_simple);
                else
                if ( operation == "count") active_scheme->addBlock(COUNT, t_simple, t_simple);
                else
                {
                    QMessageBox messageBox;
                    messageBox.critical(0,"Error","No such operation.");
                    messageBox.setFixedSize(500,200);
                    return false;
                }
                break;
            }

            case STEP:      scheduler->step(); break;
            case UNDO:      scheduler->undo(); break;
            case RUN:       scheduler->run(); break;

            default: 
            {
                QMessageBox messageBox;
                messageBox.critical(0,"Error","No such command. Not even 'INVALID'!");
                messageBox.setFixedSize(500,200);
                error(E_UNDEF, "No such command. Not even 'INVALID'!", true);
            }

        }
    }
    else
    // CLI SPECIFIC COMMAND EXECUTION
    if (RUN_MODE == CLI_MODE)
    {
        switch (cmd)
        {
            case INVALID:
            {
                error(E_INTERNAL, "Invalid command. Enter 'help' to display possible commands.");
                return false;
            }

            case HELP:
            {
                help();
                break;
            }
            
            // // // // // // // // // // //
            //   COMMANDS WITH ARGUMENTS  //
            // // // // // // // // // // //
    
            case SAVE:
            {
                string scheme_file_path;
                cin >> scheme_file_path;
        
                cout << "Saving the current scheme to '" << CL::BOLD << scheme_file_path << CL::ENDC << "'..." << endl;
                loader->saveScheme(scheme_file_path, active_scheme);
                break;
            }

            case LOAD:
            {
                string scheme_file_path;
                cin >> scheme_file_path;
                cout << "Going to load scheme from '" << CL::BOLD << scheme_file_path << CL::ENDC << "'." << endl;

                active_scheme = loader->loadScheme(scheme_file_path);

                if(active_scheme)
                {
                    scheduler->bindScheme(active_scheme);
                    cout << CL::OKGREEN << "Scheme was successfully loaded" << CL::ENDC << endl;
                }
                else
                    cout << CL::FAIL << "Error - scheme was not loaded!" << CL::ENDC << endl;
                break;
            }

            case RESET:
            {
                scheduler->resetQueue();
                cout << CL::OKGREEN << "Scheduler was reset." << CL::ENDC << endl;
                break;
            }

            case NEW:
            {
                string new_scheme_name;
                cin >> new_scheme_name;

                active_scheme = loader->createScheme(new_scheme_name);
                scheduler->bindScheme(active_scheme);
                break;
            }

            case ADD:
            {
                string operation;
                cin >> operation;

                // lowercase it
                std::transform(operation.begin(), operation.end(), operation.begin(), ::tolower);

                if ( operation == "sum") active_scheme->addBlock(SUM, t_simple, t_simple);
                else
                if ( operation == "avg") active_scheme->addBlock(AVG, t_simple, t_simple);
                else
                if ( operation == "min") active_scheme->addBlock(MIN, t_simple, t_simple);
                else
                if ( operation == "max") active_scheme->addBlock(MAX, t_simple, t_simple);
                else
                if ( operation == "count") active_scheme->addBlock(COUNT, t_simple, t_simple);
                else
                {
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    error(E_SCHEMA_OTHER, "Unrecognized operation type! Must be 'sum', 'avg', min', 'max' or 'count'");
                }
                break;
            }

            case RM:
            {
                string block_id;
                cin >> block_id;

                active_scheme->removeBlock(stoul(block_id));
                break;
            }

            case ADD_IN:
            {
                string block_id;
                cin >> block_id;

                active_scheme->addBlockInPort(stoul(block_id));
                break;
            }

            case ADD_OUT:
            {
                string block_id;
                cin >> block_id;

                active_scheme->addBlockOutPort(stoul(block_id));
                break;
            }

            case RM_IN:
            {
                string block_id;
                cin >> block_id;
                string port_idx;
                cin >> port_idx;

                active_scheme->removeBlockInPort(stoul(block_id), stoul(port_idx));
                break;
            }

            case RM_OUT:
            {
                string block_id;
                cin >> block_id;
                string port_idx;
                cin >> port_idx;

                active_scheme->removeBlockOutPort(stoul(block_id), stoul(port_idx));
                break;
            }

            case CONNECT:
            {                
                string out_block_id;
                cin >> out_block_id;
                string out_port_idx;
                cin >> out_port_idx;
                
                string in_block_id;
                cin >> in_block_id;
                string in_port_idx;
                cin >> in_port_idx;

                active_scheme->connect(stoul(out_block_id), stoul(out_port_idx), stoul(in_block_id), stoul(in_port_idx));
                break;
            }

            case DISCONNECT:
            {
                string out_block_id;
                cin >> out_block_id;
                string out_port_idx;
                cin >> out_port_idx;
                
                string in_block_id;
                cin >> in_block_id;
                string in_port_idx;
                cin >> in_port_idx;

                active_scheme->removeConnection(stoul(out_block_id), stoul(out_port_idx), stoul(in_block_id), stoul(in_port_idx));
                break;
            }

            case SET:
            {
                string block_id;
                cin >> block_id;
                string port_idx;
                cin >> port_idx;
                string port_val;
                cin >> port_val;

                active_scheme->setBlockPortValue(stoul(block_id), stoul(port_idx), "val", stod(port_val));
                break;
            }

            case COMPUTE:
            {
                string block_id;
                cin >> block_id;

                active_scheme->computeBlock(stoul(block_id));
                break;
            }


            // // // // // // // // // // //
            //  COMMANDS W/ NO ARGUMENTS  //
            // // // // // // // // // // //
            
            case PRINT:     active_scheme->print(); break;

            case BIND:      scheduler->bindScheme(active_scheme); break;
            case SCHEDULE:  scheduler->print(); break;
            case CHECK:     scheduler->checkCycles(); break;
            case SET_FREE:  scheduler->setFreeInputs(); break;
            case STEP:      scheduler->step(); break;
            case UNDO:      scheduler->undo(); break;
            case RUN:       scheduler->run(); break;
            
            case EXIT:
            {
                cout << "Going to exit ..." << endl;
                exit(SUCCESS);
                break;
            }
            
            default: error(E_UNDEF, "No such command. Not even 'INVALID'!", true); break;
        }
    }
    return true;
}

/**
 * @brief Evaluation part of the command execution
 */
Command_t CommandHandler::eval(std::string command)
{
    if( command ==  "help")         return HELP;
    if( command ==  "save")         return SAVE;
    if( command ==  "load")         return LOAD;
    if( command ==  "new")          return NEW;
    if( command ==  "print")        return PRINT;
    if( command ==  "add")          return ADD;
    if( command ==  "rm")           return RM;
    if( command ==  "add-in")       return ADD_IN;
    if( command ==  "add-out")      return ADD_OUT;
    if( command ==  "rm-in")        return RM_IN;
    if( command ==  "rm-out")       return RM_OUT;
    if( command ==  "connect")      return CONNECT;
    if( command ==  "disconnect")   return DISCONNECT;
    if( command ==  "set")          return SET;
    if( command ==  "compute")      return COMPUTE;
    if( command ==  "bind")         return BIND;
    if( command ==  "schedule")     return SCHEDULE;
    if( command ==  "check")        return CHECK;
    if( command ==  "set-free")     return SET_FREE;
    if( command ==  "step")         return STEP;
    if( command ==  "undo")         return UNDO;
    if( command ==  "run")          return RUN;
    if( command ==  "exit")         return EXIT;
    if( command ==  "reset")        return RESET;

    return INVALID;
}
