/**
 *  @file       scheduler.h
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    1.0
 * 
 *  @brief ICP 2018, Project - Block Editor. Scheduler header.
 *  
 *  @section Description
 * 
 */

#ifndef BLOCKEDITOR_SCHEDULER_H_
#define BLOCKEDITOR_SCHEDULER_H_

#include <queue>

#include <QWidget>

#include "blocks.h"
#include "scheme.h"


class SchedulerHistory;
class Scheduler;

/**
 * @brief SchedulerHistory class - Memento des. pattern inspired snapshot object
 * @desc SchedulerHistory is a history snapshot used for undo function in the scheduler.
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

/**
 * @brief Scheduler class
 * @desc Scheduler is an object managing the order of computation in the scheme.
 * It is able to run, step and undo the commands, it also checks for cycles in the scheme.
 */
class Scheduler
{
friend class SchedulerHistory;

private:
    std::shared_ptr<SchedulerHistory> history;   // previous state
    std::shared_ptr<Scheme> current_scheme;      // loaded scheme
    std::list<unsigned> queued_blocks;           // blocks waiting in a queue
    std::vector<unsigned> visited_blocks;        // history of execution

public:
    Scheduler() : 
        history {nullptr}, 
        current_scheme {nullptr}, 
        queued_blocks {std::list<unsigned>()}, 
        visited_blocks { std::vector<unsigned>()}
    {}

    // bind some existing scheme to this scheduler
    void bindScheme(std::shared_ptr<Scheme> scheme, QWidget* optional_parent = 0);

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
    void setFreeInputsGui(QWidget* parent);

    // returns index to next prepared (with all inputs set) block
    unsigned getNext();

    // checks if there are any cycles in the scheme
    bool checkCycles();
    bool checkCyclesRecursion(std::shared_ptr<Block> actual_block, std::vector<unsigned> visited);

    // prints identification numbers of blocks in scheduler
    void print();

    // reset port values
    void resetPortValues();

};

#endif
