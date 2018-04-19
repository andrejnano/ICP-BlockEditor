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
#include <algorithm>

// project headers
#include "utilities.h"
#include "port.h"
#include "blocks.h"

// commonly used std objects.. really no need to be careful about poluting namespace
using std::cout;
using std::cin;
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

  cout << CL::BOLD << "BlockEditor started" << CL::ENDC << endl;

  // handle input, decide what to do
    // -> show help
    // -> load schema
    // -> .. create schema, edit schema,.. 

  /* COMMAND HANDLER */
  string user_input;

  while(true)
  {
    cout << "~> ";
    cin >> user_input;
    std::transform(user_input.begin(), user_input.end(), user_input.begin(), ::tolower);

    if (user_input == "help")
    {
      help();
    }
    else if (user_input == "exit")
    {
      cout << "Going to exit ..." << endl;
      exit(SUCCESS);
    }
    else if (user_input == "load")
    {
      string schema_path;
      cin >> schema_path;
      
      cout << "Going to load '" << CL::BOLD << schema_path << CL::ENDC << "'." << endl;
      // Loader();
      // schema loaded
      // -> execute
    }
    else
    {
      cout << "Uknown command: " << CL::BOLD << user_input << CL::ENDC << endl;
      cout << "If you need help, enter \"help\"." << endl;
    }
  }

  return SUCCESS;
}



