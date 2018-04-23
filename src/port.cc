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
#include <map>
#include <list>

#include "port.h"

/**
 * @brief Port constructor
 * @param new_id identification of port (probably unnecessary)
 * @param new_type type of data in port
 */
Port::Port(int new_id, data_type new_type)
{
    this->id = new_id;
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
    //std::cout << "----" << std::endl;
    std::cout << "  PORT TYPE: - " << this->type << std::endl;
    switch(this->type)
    {
        case t_simple:
            if(this->is_set)
            {
                std::cout << "    VALUES: val - " << this->data["val"] << std::endl;
            }
            else
            {
                std::cout << "    VALUES NOT SET" << std::endl;
            }
            break;
        default:
            std::cout << "    neplatny typ" << std::endl;
            break;
    }
    //std::cout << "----" << std::endl;
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