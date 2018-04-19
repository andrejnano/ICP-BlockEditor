/**
 *  @file       misc.cc
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl
 *  @date       2018-05-05
 *  @version    0.1
 * 
 *  @brief ICP 2018, Project - Block Editor. Misc
 *  
 *  @section Description
 * 
 *  @section Usage
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