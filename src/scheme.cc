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
    block_id = 1001;// this ID will be set to first crated block
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
        std::cout << "  OUT: " << this->wires[i].id_out << " (" << this->wires[i].index_out << ") | IN: " << this->wires[i].id_in << " (" << this->wires[i].index_in << ")" << std::endl;
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
 * @param block_id identification number of block
 */
void Scheme::computeBlock(unsigned block_id)
{
    if(this->getBlockByID(block_id) != NULL)
    {
        this->getBlockByID(block_id)->compute();
    }
}

/**
 * @brief sets value of port
 * @param block_id identification number of block
 * @param port_num index of port in block [0-n]
 * @param val_name name of value in data type ("val" in simple type)
 * @param new_value value to be set
 */
void Scheme::setBlockPortValue(unsigned block_id, unsigned port_num, std::string val_name, double new_value)
{
    if(this->getBlockByID(block_id) != NULL)
    {
        this->getBlockByID(block_id)->setPortValue(port_num, val_name, new_value);
    }
}

/**
 * @brief sets new wire between two ports
 * @param out_port_id source - id of output port
 * @param in_port_id destination - id of input port
 */
void Scheme::connect(unsigned out_block_id, unsigned out_port_index, unsigned in_block_id, unsigned in_port_index)
{
    wire tmp;
    tmp.id_out = out_block_id;
    tmp.index_out = out_port_index;
    tmp.id_in = in_block_id;
    tmp.index_in = in_port_index;
    this->wires.push_back(tmp);
}

/**
 * @brief finds block with given ID
 * @param searched_id identification number of searched block
 * @return pointer to searched block, NULL if not found
 */
Block* Scheme::getBlockByID(unsigned searched_id)
{
    for(unsigned i = 0; i < this->blocks.size(); i++)
    {
        if(this->blocks[i].getBlockID() == searched_id)
        {
            return &(this->blocks[i]);
        }
    }
    return NULL;
}