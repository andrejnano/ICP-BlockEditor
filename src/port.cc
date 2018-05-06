/**
 *  @file       port.cc
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    1.0
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



/**
 * @brief Port constructor
 * @param new_id identification of port (probably unnecessary)
 * @param new_type type of data in port
 */
Port::Port(unsigned new_id, data_type_t new_type)
{
    this->Id = new_id;
    this->type = new_type;
    this->is_set = false;
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
    std::cout << "|  ~ PORT ["<< this->Id <<"][";

    switch(this->type)
    {
        case t_simple:
            std::cout << CL::BOLD << "SIMPLE" << CL::ENDC << "]: ";
            
            if(this->is_set)
            {
                std::cout << std::setw(8) << std::left << this->data["val"] << " |" <<  std::endl;
            }
            else
            {
                std::cout << CL::WARNING << std::setw(8) << std::left << "*" << CL::ENDC << " |" <<  std::endl;
            }
            break;
        default:
            std::cout << CL::FAIL << "UNKNOWN" << CL::ENDC << "] {}"
            << std::setw(7) << " |" << std::endl;
            break;
    }
}

void Port::setValue(std::string name, double value)
{
    this->data[name] = value;
    this->is_set = true;
}

double Port::getValue(std::string name)
{
    return this->data[name];
}

bool Port::isSet()
{
    return this->is_set;
}

unsigned Port::getId()
{
    return this->Id;
}
