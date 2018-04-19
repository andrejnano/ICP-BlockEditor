/**
 *  @file       main.cc
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl
 *  @date       2018-05-05
 *  @version    0.1
 * 
 *  @brief ICP 2018, Project - Block Editor. Main source file.
 *  
 *  @section Description
 * 
 *  @section Usage
 *  
 */

// std libraries
#include <iostream>
#include <vector>
#include <map>

// project headers
#include "utilities.h"
#include "types.h"
#include "port.h"
#include "blocks.h"

// commonly used std objects.. really no need to be careful about poluting namespace
using std::cout;
using std::cerr;
using std::endl;
using std::string;


/**
 * @brief Main entry point
 * @param argc arg count
 * @param argv pointer to array of args
 * @return success/error code
 */
int main(int argc, char **argv)
{
  // simple drat;
  // drat.print();
  // drat.setValue(1.25);
  // drat.print();

  cout << CL::OKGREEN << "some text : " << CL::ENDC << CL::BOLD << "Hello" << CL::ENDC << endl;
}



