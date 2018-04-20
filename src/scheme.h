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

// wire structure. out: output port of source block | in: input port of target block
struct wire{
    unsigned id_out;
    unsigned id_in;
};

class Scheme
{
  private:
    std::string name;
    std::vector<Block> blocks;
    std::vector<wire> wires;
  public:
    Scheme(std::string new_name);
    void addBlock(block_type new_type, unsigned new_id, data_type input_type, data_type output_type);
    void setBlockPortValue(unsigned block_num, unsigned port_num, std::string val_name, double new_value);
    void computeBlock(unsigned block_num);
    void connect(unsigned out_port_id, unsigned in_port_id);
    void print();
};

#endif