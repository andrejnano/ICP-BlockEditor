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
#include <iomanip>
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
#include "loader.h"

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
  headline(1, "BlockEditor 1.0");
  headline(0, "Commands: ");
  paragraph("Help  Show help and usage info.\nPrint  Print actual scheme.\nLoad <scheme>  Load the scheme.\nExit  Leave the program.\n");
  command_menu();

  return SUCCESS;
}

/* COMMAND HANDLER */
/* handle input, decide what to do */
void command_menu()
{
  Scheme* active_scheme = new Scheme("My Scheme");
  Loader* loader = new Loader();

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
      loader->saveScheme(schema_path, active_scheme);
    }
    else if (user_input == "load")
    {
      string schema_path;
      cin >> schema_path;
      
      cout << "Going to load scheme from '" << CL::BOLD << schema_path << CL::ENDC << "'." << endl;

      if(active_scheme = loader->loadScheme(schema_path))
      {
        cout << CL::OKGREEN << "Scheme was successfully loaded" << CL::ENDC << endl;
      }
      else
      {
        cout << CL::FAIL << "Error - scheme was not load!" << CL::ENDC << endl;
      }
    }
    else if (user_input == "inc-id")
    {
      active_scheme->incrementID();
    }
    else if (user_input == "print")
    {
      active_scheme->print();
    }
    else if (user_input == "add")
    {
      string type_of_block;
      cin >> type_of_block;

      if(type_of_block == "sum")
      {
        active_scheme->addBlock(SUM, t_simple, t_simple);
      }
      else if(type_of_block == "avg")
      {
        active_scheme->addBlock(AVG, t_simple, t_simple);
      }
      else if(type_of_block == "min")
      {
        active_scheme->addBlock(MIN, t_simple, t_simple);
      }
      else if(type_of_block == "max")
      {
        active_scheme->addBlock(MAX, t_simple, t_simple);
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

      active_scheme->removeBlock(stoul(a));
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

      active_scheme->connect(stoul(a), stoul(b), stoul(c), stoul(d));
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

      active_scheme->removeConnection(stoul(a), stoul(b), stoul(c), stoul(d));
    }
    else if (user_input == "set")
    {
      string id;
      cin >> id;
      string index;
      cin >> index;
      string value;
      cin >> value;

      active_scheme->setBlockPortValue(stoul(id), stoul(index), "val", stod(value));
    }
    else if (user_input == "compute")
    {
      string id;
      cin >> id;

      active_scheme->computeBlock(stoul(id));
    }
    else if (user_input == "add-in")
    {
      string id;
      cin >> id;

      active_scheme->addBlockInPort(stoul(id));
    }
    else if (user_input == "add-out")
    {
      string id;
      cin >> id;

      active_scheme->addBlockOutPort(stoul(id));
    }
    else if (user_input == "rm-in")
    {
      string id;
      cin >> id;
      string index;
      cin >> index;

      active_scheme->removeBlockInPort(stoul(id), stoul(index));
    }
    else if (user_input == "rm-out")
    {
      string id;
      cin >> id;
      string index;
      cin >> index;

      active_scheme->removeBlockOutPort(stoul(id), stoul(index));
    }
    else if (user_input == "sch-load")
    {
      active_scheme->loadIntoScheduler();
    }
    else if (user_input == "sch-print")
    {
      active_scheme->printScheduler();
    }
    else if (user_input == "check")
    {
      if(active_scheme->checkCycles())
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
      active_scheme->setFreeInputs();
    }
    else if (user_input == "step")
    {
      active_scheme->step();
    }
    else
    {
      cout << "Uknown command: " << CL::BOLD << user_input << CL::ENDC << endl;
      cout << "If you need help, enter \"help\"." << endl;
    }
  }
}



