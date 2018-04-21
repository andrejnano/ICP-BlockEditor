/**
 *  @file       main.cc
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
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
#include "scheme.h"

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

  // testing code

  /*Port myPort(1,t_simple);
  myPort.print();
  myPort.setValue("val",1.25);
  myPort.print();*/

  /*Block soucet1(b_sum,1012,t_simple,t_simple);
  soucet1.print();
  soucet1.setPortValue(0,"val",2.26);
  soucet1.setPortValue(1,"val",1.15);
  soucet1.print();
  soucet1.compute();
  soucet1.print();*/

  Scheme a("Schema A");
  a.print();
  a.addBlock(b_sum, t_simple, t_simple);
  a.setBlockPortValue(1001, 0, "val", 1.25);
  a.setBlockPortValue(1001, 1, "val", 1.75);
  a.computeBlock(1001);
  a.addBlock(b_sum, t_simple, t_simple);
  a.setBlockPortValue(1002, 0, "val", 2.05);
  a.setBlockPortValue(1002, 0, "val", 2.91);
  a.connect(23, 0, 68, 2);
  a.connect(1234, 1, 4321, 1);
  a.connect(1, 0, 333, 3);
  a.print();

  // end of testing code


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



