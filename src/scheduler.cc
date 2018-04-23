/**
 *  @file       scheduler.cc
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    0.1
 * 
 *  @brief ICP 2018, Project - Block Editor. Scheduler class.
 *  
 *  @section Description
 * 
 */

#include "scheduler.h"


void Scheduler::addBlock(Block *scheme_block)
{
    this->blocks.push_back(scheme_block);
}

void Scheduler::print()
{
    std::cout << "SCHEDULER: " << std::endl;
    for(unsigned i = 0; i < this->blocks.size(); i++)
    {
        std::cout << "  " << this->blocks[i]->getBlockID() << std::endl;
    }
}