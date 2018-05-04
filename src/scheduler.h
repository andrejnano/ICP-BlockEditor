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

class SchedulerHistory;
class Scheduler;

/*
    Memento design pattern inspired history/undo solution
*/
class SchedulerHistory
{
friend class Scheduler;

private:
    std::shared_ptr<SchedulerHistory> history_memo;
    std::shared_ptr<Scheme> current_scheme_memo;
    std::list<unsigned> queued_blocks_memo; 
    std::vector<unsigned> visited_blocks_memo;

public:
    // const ref version
    SchedulerHistory(const Scheduler& present);

};


class Scheduler
{
friend class SchedulerHistory;

private:
    std::shared_ptr<SchedulerHistory> history;              // previous state
    std::shared_ptr<Scheme> current_scheme;                 // loaded scheme
    std::list<unsigned> queued_blocks;      // blocks waiting in a queue
    std::vector<unsigned> visited_blocks;   // history of execution

public:
    Scheduler() : 
        history {nullptr}, 
        current_scheme {nullptr}, 
        queued_blocks {std::list<unsigned>()}, 
        visited_blocks { std::vector<unsigned>()}
    {}

    // bind some existing scheme to this scheduler
    void bindScheme(std::shared_ptr<Scheme> scheme);

    // current scheme getter
    std::shared_ptr<Scheme> currentScheme();

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

    // returns index to next prepared (with all inputs set) block
    unsigned getNext();

    // checks if there are any cycles in the scheme
    bool checkCycles();
    bool checkCyclesRecursion(std::shared_ptr<Block> actual_block, std::vector<unsigned> visited);

    // prints identification numbers of blocks in scheduler
    // TODO: is really needed?
    void print();

};

#endif