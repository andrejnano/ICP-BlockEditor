
// blocks.h

#ifndef BLOCKS_H
#define BLOCKS_H

#include <vector>
#include <iostream>
#include <map>

#include "types.h"
#include "port.h"

class Block
{
  protected:
    std::map<std::string, double> data;
};

#endif