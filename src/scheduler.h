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

#include <queue>
#include "blocks.h"
#include "scheme.h"


/*

  Scheduler's main job is to execute computation 
  on a single block at a time and then proceed to other blocks.. 

  There should exist a QUEUE of blocks to be computed.

  Actions:
    - step (only 1x)
    - run (the whole scheme)


  GUI NOTE: if a step occurs, there should be an event so the view is refreshed.

*/

class Scheduler;

/*
    Memento design pattern inspired history/undo solution
*/
class SchedulerHistory
{
friend class Scheduler;

private:
    SchedulerHistory* history_memo;
    Scheme* current_scheme_memo;
    std::queue<Block*> queued_blocks_memo; 
    std::vector<unsigned> visited_blocks_memo;

public:
    SchedulerHistory(Scheduler* recent) :
        history_memo { recent->history },
        current_scheme_memo { recent->current_scheme },
        queued_blocks_memo { recent->queued_blocks },
        visited_blocks_memo  { recent->visited_blocks }
    {}
};


class Scheduler
{
friend class SchedulerHistory;

private:
    SchedulerHistory* history;
    Scheme* current_scheme; // loaded scheme
    std::queue<Block*> queued_blocks; // blocks waiting in a queue
    std::vector<unsigned> visited_blocks; // history of execution

public:
    Scheduler() : history {nullptr}, current_scheme {nullptr},
    queued_blocks {std::queue<Block*>()}, visited_blocks {std::vector<unsigned>()}
    {}

    // bind some existing scheme to this scheduler
    void bindScheme(Scheme* scheme);

    // reloads all the blocks from the scheme into the queue
    void resetQueue();

    // starts executing the whole scheme
    void run();

    // executes just 1 step, creates new history
    void step();

    // undoes 1 step, loads the history
    void undo();

    // calls function to get input from user for every free input port
    void setFreeInputs();

    // returns pointer to next prepared (with all inputs set) block
    Block* getNext();

    // checks if there are any cycles in the scheme
    bool checkCycles();
    bool checkCyclesRecursion(Block* actual_block, std::vector<unsigned> visited);

    // prints identification numbers of blocks in scheduler
    // TODO: is really needed?
    void print();
    


};

#endif