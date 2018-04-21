/**
 *  @file       blocks.h
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    0.1
 * 
 *  @brief ICP 2018, Project - Block Editor. Block class header.
 *  
 *  @section Description
 *  
 */

#ifndef BLOCKEDITOR_BLOCKS_H_
#define BLOCKEDITOR_BLOCKS_H_

#include <vector>
#include <iostream>
#include <map>

#include "port.h"

// enumeration contanining block types
enum block_type {b_sum};

class Block
{
  protected:
    int id;
    block_type type;
    double (*computation)(std::vector<Port>);// pointer to function, which return result from input ports array
    std::vector<Port> in_ports;
    std::vector<Port> out_ports;

  public:
    Block(block_type new_type, unsigned new_id, data_type input_type, data_type output_type);
    void setPortValue(unsigned port_num, std::string val_name, double new_value);
    unsigned getBlockID();
    void compute();
    void print();
};

#endif