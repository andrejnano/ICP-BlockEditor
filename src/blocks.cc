/**
 *  @file       blocks.cc
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    0.1
 * 
 *  @brief ICP 2018, Project - Block Editor. Block class.
 *  
 *  @section Description
 * 
 */

#include <vector>
#include <iostream>
#include <map>

#include "blocks.h"

/**
 * @brief function which computes sum of values from input ports
 * @param inputs vector of input ports
 * @return sum of input values
 */
double c_sum(std::vector<Port> inputs)
{
    double result = 0;
    for(unsigned i = 0; i < inputs.size(); i++)
    {
        result += inputs[i].getValue("val");
    }
    return result;
}

/**
 * @brief Block constructor
 * @param new_type type of block
 * @param new_id identification of block
 * @param input_type data type of input ports
 * @param output_type data type of result
 */
Block::Block(block_type new_type, unsigned new_id, data_type input_type, data_type output_type)
{
    this->type = new_type;
    switch(new_type)
    {
        case b_sum:
            std::cout << "[new block (SUM)]" << std::endl;
            computation = c_sum;
            break;
        default:
            std::cout << "[trying to add unrecognized block]" << std::endl;
            break;
    }
    this->id = new_id;
    this->in_ports.push_back(Port(2,t_simple));
    this->in_ports.push_back(Port(3,t_simple));
    this->out_ports.push_back(Port(5,t_simple));
}

/**
 * @brief sets value of input port
 * @param port_num index of port in array [0-n]
 * @param val_name name of value which should be changed ("val" in simple type)
 * @param new_value new value of port
 */
void Block::setPortValue(unsigned port_num, std::string val_name, double new_value)
{
    this->in_ports[port_num].setValue(val_name, new_value);
}

/**
 * @brief call function to compute block operation and sets result to output ports
 */
void Block::compute()
{
    double result = c_sum(this->in_ports);
    for(unsigned i = 0; i < this->out_ports.size(); i++)
    {
        this->out_ports[i].setValue("val", result);
    }
}

/**
 * @brief prints information about block and call print functions for ports
 */
void Block::print()
{
    std::cout << "--------- BLOCK ---------" << std::endl;
    std::cout << "ID: " << this->id << std::endl;
    std::cout << "TYPE: " << this->id << std::endl;
    std::cout << "INPUTS:" << std::endl;
    for(unsigned i = 0; i < this->in_ports.size(); i++)
    {
        this->in_ports[i].print();
    }
    std::cout << "OUTPUTS:" << std::endl;
    for(unsigned i = 0; i < this->out_ports.size(); i++)
    {
        this->out_ports[i].print();
    }
    std::cout << "-------------------------" << std::endl;
}

