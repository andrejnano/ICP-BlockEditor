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
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

// project headers
#include "utilities.h"
#include "port.h"
#include "blocks.h"
#include "scheme.h"
#include "scheduler.h"

// commonly used std objects.. really no need to be careful about poluting the namespace
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::stoul;
using std::stod;

void command_menu();

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
  a.addBlock(MAX, t_simple, t_simple);
  a.setBlockPortValue(1001, 0, "val", 1.25);
  a.setBlockPortValue(1001, 1, "val", 1.75);
  a.computeBlock(1001);

  a.addBlock(COUNT, t_simple, t_simple);
  a.setBlockPortValue(1002, 0, "val", 9);

  a.connect(1001, 0, 1002, 1);
  a.propagate(1001);

  a.computeBlock(1002);
  
  a.print();
  a.propagate(1002);*/
  
  // end of testing code

  //Scheme actual_scheme("My Scheme");
  //Scheduler computation_scheduler();
  cout << CL::BOLD << "BlockEditor started" << CL::ENDC << endl;

  command_menu();

  return SUCCESS;
}

/* COMMAND HANDLER */
/* handle input, decide what to do */
void command_menu()
{
  Scheme actual_scheme("My Scheme");
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
    else if (user_input == "save")
    {
      string schema_path;
      cin >> schema_path;

    cout << "Going to save scheme into '" << CL::BOLD << schema_path << CL::ENDC << "'." << endl;
      actual_scheme.saveScheme(schema_path);
    }
    else if (user_input == "load")
    {
      string schema_path;
      cin >> schema_path;
      
      cout << "Going to load scheme from '" << CL::BOLD << schema_path << CL::ENDC << "'." << endl;

      if(actual_scheme.loadScheme(schema_path) == true)
      {
        cout << CL::OKGREEN << "Scheme was successfully loaded" << CL::ENDC << endl;
      }
      else
      {
        cout << CL::FAIL << "Error - scheme was not load!" << CL::ENDC << endl;
      }

      // Loader();
      // schema loaded
      // -> execute
    }
    else if (user_input == "inc-id")
    {
      actual_scheme.incrementID();
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
        cout << "Unrecognized block type! Must be 'sum', 'avg', min' or 'max'" << endl;
      }
    }
    else if (user_input == "rm")
    {
      string a;
      cin >> a;

      actual_scheme.removeBlock(stoul(a));
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
    else if (user_input == "rm-wire")
    {
      string a;
      cin >> a;
      string b;
      cin >> b;
      string c;
      cin >> c;
      string d;
      cin >> d;

      actual_scheme.removeConnection(stoul(a), stoul(b), stoul(c), stoul(d));
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
    else if (user_input == "add-in")
    {
      string id;
      cin >> id;

      actual_scheme.addBlockInPort(stoul(id));
    }
    else if (user_input == "add-out")
    {
      string id;
      cin >> id;

      actual_scheme.addBlockOutPort(stoul(id));
    }
    else if (user_input == "rm-in")
    {
      string id;
      cin >> id;
      string index;
      cin >> index;

      actual_scheme.removeBlockInPort(stoul(id), stoul(index));
    }
    else if (user_input == "rm-out")
    {
      string id;
      cin >> id;
      string index;
      cin >> index;

      actual_scheme.removeBlockOutPort(stoul(id), stoul(index));
    }
    else if (user_input == "sch-load")
    {
      actual_scheme.loadIntoScheduler();
    }
    else if (user_input == "sch-print")
    {
      actual_scheme.printScheduler();
    }
    else if (user_input == "check")
    {
      if(actual_scheme.checkCycles())
      {
        std::cout << CL::OKGREEN << CL::BOLD << "  NO CYCLES DETECTED!" << CL::ENDC << std::endl;
      }
      else
      {
        std::cout << CL::FAIL << CL::BOLD << "  CHECK FAILED!" << CL::ENDC << std::endl;
      }
    }
    else if (user_input == "set-free")
    {
      actual_scheme.setFreeInputs();
    }
    else if (user_input == "step")
    {
      actual_scheme.step();
    }
    else
    {
      cout << "Uknown command: " << CL::BOLD << user_input << CL::ENDC << endl;
      cout << "If you need help, enter \"help\"." << endl;
    }
  }
}



