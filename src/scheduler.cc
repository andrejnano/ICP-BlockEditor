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
#include "utilities.h"
#include "scheme.h"

/**
 * @brief prints identification numbers of blocks in scheduler
 */
// void Scheduler::print()
// {
//     std::cout << "SCHEDULER: " << std::endl;
//     for (std::list<Block*>::iterator it = queued_blocks.begin(); it != this->blocks.end(); ++it){
//         std::cout << "  " << (*it)->getBlockID() << std::endl;
//     }
// }

/**
 * @brief finds next block, which has set all input port values
 * @return pointer to next prepared block
 */
Block* Scheduler::getNext()
{
    if(!queued_blocks.empty())
    {
        Block* active_block = queued_blocks.front();
        queued_blocks.pop();
        
        // if block is not prepared, pointer is pushed to the end of queue
        while (active_block->isPrepared() != true)
        {
            queued_blocks.push(active_block);
            active_block = queued_blocks.front();
            queued_blocks.pop();
        }

        return active_block;
    }
    else
    {
        return nullptr;
    }
}


// bind some existing scheme to this scheduler
void Scheduler::bindScheme(Scheme* scheme)
{
    if (scheme)
    {
        current_scheme = scheme;
        resetQueue();
        setFreeInputs(); // what about GUI?
    }
    else
    {
        error(E_SCHEDULER, "Cannot bind NULL scheme.");
    }
}

// return pointer to the current active scheme
Scheme* Scheduler::currentScheme()
{
    return current_scheme;
}


// reloads all the blocks from the scheme into the queue
void Scheduler::resetQueue()
{
    // empty the queue
    while(!queued_blocks.empty())
        queued_blocks.pop();

    // fill with the scheme blocks
    for(unsigned i = 0; i < current_scheme->blocks.size(); i++)
        queued_blocks.push(current_scheme->blocks[i]);
}

// starts executing the whole scheme
void Scheduler::run()
{
    while(!queued_blocks.empty)
    {
        step();
    }
    std::cout << "all blocks were computed!" << std::endl;
}

/**
 * @brief Executes a new step and creates a new history.
 */
void Scheduler::step()
{
    // TODO: possible improvement: do 'redo'
    //       if the step is the same 

    history = new SchedulerHistory(this);

    // compute on the first 'prepared' block on the queue
    Block* next_block = getNext();
    if (next_block)
    {
        current_scheme->computeBlock(next_block->getBlockID);
    }
    else
    {
        // No more blocks !
        std::cout << "all blocks were computed!" << std::endl;
    }
}

/**
 * @brief Go back to the previous state.
 */
void Scheduler::undo()
{
    if (history)
    {
        current_scheme = history->current_scheme_memo;
        queued_blocks = history->queued_blocks_memo;
        visited_blocks = history->visited_blocks_memo;

        // important to be the last thing copied, so the ptr is not lost
        history = history->history_memo;
    }
    else
    {
        error(E_SCHEDULER, "Cannot undo. Nothing was done yet.");
    }
}


/**
 * @brief gradually sets all the ports which require user input
 */
void Scheduler::setFreeInputs()
{
    // note: Scheduler class is a 'friend' of the Scheme class
    //       Therefore, it has access to all of it's members.

    for(unsigned b = 0; b < current_scheme->blocks.size(); b++)
    {
        for(unsigned p = 0; p < current_scheme->blocks[b]->getInSize(); p++)
        {
            if(current_scheme->isConnected(current_scheme->blocks[b]->getBlockID(), true, p) == 1) // if port is not connected
            {
                current_scheme->blocks[b]->setInPortValue(p,"val", current_scheme->getUserValue(current_scheme->blocks[b]->getBlockID(), p));
            }
        }
    }
}


/**
 * @brief checks if there are cycles in scheme
 * @return true if scheme is ok, false if cycle is detected
 */
bool Scheduler::checkCycles()
{
    std::vector<unsigned> visited;
    std::cout << "CHECKING CYCLES:" << std::endl;
    for(unsigned i = 0; i < current_scheme->blocks.size(); i++)
    {
        if(this->checkCyclesRecursion(current_scheme->blocks[i], visited) == false)
        {
            return false;
        }
    }
    return true;
}


/**
 * @brief recursive function for checking cycles
 * @param actual_block actual checked block
 * @param visited vector containing identification numbers of already visited blocks
 * @return true if block is visited first time, false if cycle is detected
 */
bool Scheduler::checkCyclesRecursion(Block* actual_block, std::vector<unsigned> visited)
{
    std::cout << "  in block " << actual_block->getBlockID() << " <";
    for(unsigned i = 0; i < visited.size(); i++)
    {
        std::cout << " " << visited[i];
    }
    std::cout << " >" << std::endl;

    // checking if this block was already visited
    for(unsigned i = 0; i < visited.size(); i++)
    {
        if(visited[i] == actual_block->getBlockID())
        {
            std::cout << "  I HAVE BEEN HERE! " << actual_block->getBlockID() << std::endl;
            return false;
        }
    }
    
    bool ret = true;
    std::vector<unsigned> new_visited = visited;
    new_visited.push_back(actual_block->getBlockID());

    // calling this function for next blocks
    for(unsigned i = 0; i < current_scheme->wires.size(); i++)
    {
        if(current_scheme->wires[i].id_out == actual_block->getBlockID())
        {
            if(this->checkCyclesRecursion(current_scheme->getBlockByID(current_scheme->wires[i].id_in), new_visited) == false)
            {
                ret = false;
            }
        }
    }
    return ret;  
}