/**
 *  @file       port.cc
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    0.1
 * 
 *  @brief ICP 2018, Project - Block Editor. Port class.
 *  
 *  @section Description
 * 
 *  
 */

#include <vector>
#include <iostream>
#include <iomanip>
#include <map>
#include <list>

#include "port.h"
#include "utilities.h"


Port::Port(int new_id, data_type_t new_type)
{
    this->id = new_id;
    this->type = new_type;
    switch(new_type)
    {
        case t_simple:
            this->data.insert(std::pair <std::string, double> ("val", 0.0));
            std::cout << "[new port (simple)]" << std::endl;
            break;
        default:
            this->data.clear();
            std::cout << "[new unrecognized port]" << std::endl;
            break;
    }
}

void Port::print()
{
    std::cout << "|  ~ PORT [";

    switch(this->type)
    {
        case t_simple:
            std::cout << CL::BOLD << "SIMPLE" << CL::ENDC << "]: "
            << std::setw(11) << std::left << this->data["val"] << " |" <<  std::endl;
            break;
        default:
            std::cout << CL::FAIL << "UNKNOWN" << CL::ENDC << "] {}"
            << std::setw(10) << " |" << std::endl;
            break;
    }
}

void Port::setValue(std::string name, double value)
{
    this->data[name] = value;
}

double Port::getValue(std::string name)
{
    return this->data[name];
}