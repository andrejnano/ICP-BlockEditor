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

/**
 * @brief adds new pointer to block into scheduler
 * @param scheme_block pointer to block in scheme
 */
void Scheduler::addBlock(Block *scheme_block)
{
    this->blocks.push_back(scheme_block);
}

/**
 * @brief prints identification numbers of blocks in scheduler
 */
void Scheduler::print()
{
    std::cout << "SCHEDULER: " << std::endl;
    for (std::list<Block*>::iterator it = this->blocks.begin(); it != this->blocks.end(); ++it){
        std::cout << "  " << (*it)->getBlockID() << std::endl;
    }
}

/**
 * @brief finds next block, which has set all input port values
 * @return pointer to next prepared block
 */
Block* Scheduler::getNext()
{
    if(this->blocks.empty())
    {
        return NULL;
    }
    Block* act_block = this->blocks.front();
    this->blocks.pop_front();
    while(act_block->isPrepared() != true)
    {
        this->blocks.push_back(act_block);// if block is not prepared, pointer is pushed at the end of queue
        act_block = this->blocks.front();
        this->blocks.pop_front();
    }
    return act_block;
}