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
    << "Description will go here\n\n" << "Commands: \n\n" << "- help\t Shows help and usage info.\n\n"
    << "- load <schema_path>\t Will load schema at the specified path.\n\n" << "- exit\t will exit the application.\n"
    << endl;
}