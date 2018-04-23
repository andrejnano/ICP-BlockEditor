/**
 *  @file       utilities.cc
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    0.1
 * 
 *  @brief ICP 2018, Project - Block Editor. Utilities.
 *  
 *  @section Description
 * 
 */

#include <iostream>
#include <string>
#include "utilities.h"

// commonly used std objects.. really no need to be careful about poluting namespace
using std::cout;
using std::cerr;
using std::endl;
using std::string;

void error(err_code_t error_code, string error_msg, bool do_exit)
{
  cout << " Error " << error_code << " >> " << error_msg << endl;
  do_exit ? exit(error_code) : void();
}

void help()
{
  cout << "\n" << CL::BOLD << CL::UNDERLINE << "BlockEditor" << CL::ENDC << "\n\n"
    << "Description will go here\n\n" << "Commands: \n\n" << "- help\t Show help and usage info.\n\n"
    << "- print\t Print actual scheme.\n\n"
    << "- add <block_type>\t Add new block of specified type.\n\n"
    << "- add-in <block_id>\t Add new input port to specified block.\n\n"
    << "- add-out <block_id>\t Add new output port to specified block.\n\n"
    << "- rm-in <block_id> <port_index>\t Removes input port at specified index in block.\n\n"
    << "- rm-out <block_id> <port_index>\t Removes output port at specified index in block.\n\n"
    << "- connect <src_id> <src_index> <dst_id> <dst_index>\t Make connection between two specified ports.\n\n"
    << "- set <block_id> <port_index> <value>\t Set value to specified input port.\n\n"
    << "- compute <block_id>\t Compute block operation and propagate result.\n\n"
    << "- sch-load\t Loads actual blocks to scheduler.\n\n"
    << "- sch-print\t Prints ID of blocks stored in scheduler.\n\n"
    << "- check\t Check if actual scheme contains any cycle.\n\n"
    << "- load <schema_path>\t Load schema at the specified path.\n\n" << "- exit\t Exit the application.\n"
    << endl;
}