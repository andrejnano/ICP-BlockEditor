/**
 *  @file       scheme.cc
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    0.1
 * 
 *  @brief ICP 2018, Project - Block Editor. Scheme class.
 *  
 *  @section Description
 * 
 *  
 */

#include "scheme.h"

/**
 * @brief Scheme constructor
 * @param new_name name of scheme
 */
Scheme::Scheme(std::string new_name)
{
    this->name = new_name;
    block_id = 1;// this ID will be set to first crated block
}

/**
 * @brief print scheme name, calls print functions for blocks, and prints wires
 */
void Scheme::print()
{
    std::cout << "SCHEME NAME: " << this->name << std::endl;
    std::cout << "PORTS:" << std::endl;
    for(unsigned i = 0; i < this->blocks.size(); i++)
    {
        this->blocks[i].print();
    }
    std::cout << "WIRES:" << std::endl;
    for(unsigned i = 0; i < this->wires.size(); i++)
    {
        std::cout << "  OUT: " << this->wires[i].id_out << " | IN: " << this->wires[i].id_in << std::endl;
    }
}

/**
 * @brief adds new block to scheme
 * @param new_type type of new block
 * @param input_type data type of block inputs
 * @param output_type data type of block outputs
 */
void Scheme::addBlock(block_type new_type, data_type input_type, data_type output_type)
{
    this->blocks.push_back(Block(new_type, block_id, input_type, output_type));
    block_id++;
}

/**
 * @brief calls compute function for given block
 * @param block_num index of block in vector [0-n]
 */
void Scheme::computeBlock(unsigned block_num)
{
    this->blocks[block_num].compute();
}

/**
 * @brief sets value of port
 * @param block_num index of block in vector [0-n]
 * @param port_num index of port in block [0-n]
 * @param val_name name of value in data type ("val" in simple type)
 * @param new_value value to be set
 */
void Scheme::setBlockPortValue(unsigned block_num, unsigned port_num, std::string val_name, double new_value)
{
    this->blocks[block_num].setPortValue(port_num, val_name, new_value);
}

/**
 * @brief sets new wire between two ports
 * @param out_port_id source - id of output port
 * @param in_port_id destination - id of input port
 */
void Scheme::connect(unsigned out_port_id, unsigned in_port_id)
{
    wire tmp;
    tmp.id_out = out_port_id;
    tmp.id_in = in_port_id;
    this->wires.push_back(tmp);
}