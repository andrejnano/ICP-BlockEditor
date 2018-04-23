/**
 *  @file       scheduler.h
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    0.1
 * 
 *  @brief ICP 2018, Project - Block Editor. Scheduler header.
 *  
 *  @section Description
 * 
 */

#ifndef BLOCKEDITOR_SCHEDULER_H_
#define BLOCKEDITOR_SCHEDULER_H_

#include "blocks.h"

class Scheduler
{
  private:
    Block* current_block;

  public:
    Scheduler();
    ~Scheduler();

    void iterate_once();
    void iterate_all();
    Block* current_block();

};

#endif