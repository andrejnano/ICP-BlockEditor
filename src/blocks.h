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

class Block
{
  protected:
    std::map<std::string, double> data;

  public:

    std::vector<Port> in_ports;
    std::vector<Port> out_ports;
};

#endif