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
using std::stoul;
using std::stod;


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

  /*Scheme a("Schema A");
  a.print();
  a.addBlock(b_sum, t_simple, t_simple);
  a.setBlockPortValue(1001, 0, "val", 1.25);
  a.setBlockPortValue(1001, 1, "val", 1.75);
  a.computeBlock(1001);
  a.addBlock(b_sum, t_simple, t_simple);
  a.setBlockPortValue(1002, 0, "val", 2.05);
  a.connect(1001, 0, 1002, 1);
  a.propagate(1001);
  a.computeBlock(1002);
  a.print();
  a.propagate(1002);*/
  
  // end of testing code

  Scheme actual_scheme("My Scheme");

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
    else if (user_input == "print")
    {
      actual_scheme.print();
    }
    else if (user_input == "add")
    {
      string type_of_block;
      cin >> type_of_block;

      if(type_of_block == "sum")
      {
        actual_scheme.addBlock(SUM, t_simple, t_simple);
      }
      else if(type_of_block == "avg")
      {
        actual_scheme.addBlock(AVG, t_simple, t_simple);
      }
      else if(type_of_block == "min")
      {
        actual_scheme.addBlock(MIN, t_simple, t_simple);
      }
      else if(type_of_block == "max")
      {
        actual_scheme.addBlock(MAX, t_simple, t_simple);
      }
      else
      {
        cout << "Unrecognized block type! Try 'add sum'" << endl;
      }
    }
    else if (user_input == "connect")
    {
      string a;
      cin >> a;
      string b;
      cin >> b;
      string c;
      cin >> c;
      string d;
      cin >> d;

      actual_scheme.connect(stoul(a), stoul(b), stoul(c), stoul(d));
    }
    else if (user_input == "set")
    {
      string id;
      cin >> id;
      string index;
      cin >> index;
      string value;
      cin >> value;

      actual_scheme.setBlockPortValue(stoul(id), stoul(index), "val", stod(value));
    }
    else if (user_input == "compute")
    {
      string id;
      cin >> id;

      actual_scheme.computeBlock(stoul(id));
    }
    else
    {
      cout << "Uknown command: " << CL::BOLD << user_input << CL::ENDC << endl;
      cout << "If you need help, enter \"help\"." << endl;
    }
  }

  return SUCCESS;
}



