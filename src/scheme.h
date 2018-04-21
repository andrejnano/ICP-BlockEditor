/**
 *  @file       scheme.h
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    0.1
 * 
 *  @brief ICP 2018, Project - Block Editor. Scheme class header.
 *  
 *  @section Description
 * 
 *  
 */

#ifndef BLOCKEDITOR_SCHEME_H_
#define BLOCKEDITOR_SCHEME_H_

#include "port.h"
#include "blocks.h"

struct wire{
    unsigned id_out; // ID of output block (source)
    unsigned index_out; // index of output port in block
    unsigned id_in; // ID of input block (target)
    unsigned index_in; // index of input port in block
};

class Scheme
{
  private:
    std::string name;
    unsigned block_id;
    std::vector<Block> blocks;
    std::vector<wire> wires;
  public:
    Scheme(std::string new_name);
    void addBlock(block_type new_type, data_type input_type, data_type output_type);
    void setBlockPortValue(unsigned block_id, unsigned port_num, std::string val_name, double new_value);
    double getBlockPortValue(unsigned block_id, unsigned port_num, std::string val_name);
    void computeBlock(unsigned block_id);
    bool connect(unsigned out_block_id, unsigned out_port_index, unsigned in_block_id, unsigned in_port_index);
    int isConnected(unsigned block_id, bool is_input, unsigned port_index);
    void propagate(unsigned block_id);
    Block* getBlockByID(unsigned searched_id);
    void print();
};

#endif