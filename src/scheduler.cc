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

#include <sstream>

#include <QInputDialog>

#include "scheduler.h"
#include "utilities.h"
#include "scheme.h"

/**
 * @brief Scheduler history memo creation
 */
// const ref version
SchedulerHistory::SchedulerHistory(const Scheduler& present) : 
    history_memo { present.history }, 
    current_scheme_memo { present.current_scheme },
    queued_blocks_memo { present.queued_blocks },
    visited_blocks_memo { present.visited_blocks }
{}

// pointer version TRY BOTH
// SchedulerHistory::SchedulerHistory(Scheduler *present) : 
//     history_memo { present->history }, 
//     current_scheme_memo { present->current_scheme },
//     queued_blocks_memo { present->queued_blocks },
//     visited_blocks_memo { present->visited_blocks }
// {}



/**
 * @brief prints identification numbers of blocks in scheduler
 */
void Scheduler::print()
{
    std::cout << "SCHEDULER: " << std::endl;
    
    for (std::list<unsigned>::iterator it = queued_blocks.begin(); it != queued_blocks.end(); ++it)
    {
        std::cout << " |" << *it << " | "<< std::endl;
    }
}

/**
 * @brief finds next block, which has set all input port values
 * @return pointer to next prepared block
 */
unsigned Scheduler::getNext()
{
    if(!queued_blocks.empty())
    {
        unsigned active_block_idx = queued_blocks.front();
        queued_blocks.pop_front();

        // get pointer to the block by ID
        std::shared_ptr<Block> active_block_ptr { current_scheme->getBlockByID(active_block_idx) };

        // if block is not prepared, pointer is pushed to the end of queue
        while (active_block_ptr->isPrepared() != true)
        {
            queued_blocks.push_back(active_block_idx);
            active_block_idx = queued_blocks.front();
            active_block_ptr = current_scheme->getBlockByID(active_block_idx);
            queued_blocks.pop_front();
        }

        return active_block_idx;
    }
    else
    {
        return 0;
    }
}


// bind some existing scheme to this scheduler
// TODO: probably rename, as it also resets the scheduler.. 
void Scheduler::bindScheme(std::shared_ptr<Scheme> scheme, QWidget* optional_parent)
{
    if (scheme)
    {
        current_scheme = scheme;
        resetQueue();
        
        switch (RUN_MODE)
        {
            case GUI_MODE: setFreeInputsGui(optional_parent); break;
            case CLI_MODE: setFreeInputs(); break;
            default: error(E_UNDEF,"undefined runmode");
        }
    }
    else
    {
        error(E_SCHEDULER, "Cannot bind NULL scheme.");
    }
}

// return pointer to the current active scheme
std::shared_ptr<Scheme> Scheduler::currentScheme()
{
    return current_scheme;
}


// reloads all the blocks from the scheme into the queue
void Scheduler::resetQueue()
{
    // empty the queue
    while(!queued_blocks.empty())
        queued_blocks.pop_front();

    // fill with the scheme blocks IDs
    for(unsigned i = 0; i < current_scheme->blocks.size(); i++)
        queued_blocks.push_back(current_scheme->blocks[i]->getBlockID());
}


/**
 * @brief Executes all steps until the queue is empty
 */
void Scheduler::run()
{
    this->checkCycles();

    while(!queued_blocks.empty())
    {
        this->step();
    }
    std::cout << "All blocks were computed in a single run!" << std::endl;
}


/**
 * @brief Executes a new step and creates a new history.
 */
void Scheduler::step()
{
    // create a snapshot of the current state
    history = std::make_shared<SchedulerHistory>(*this);

    // compute on the first 'prepared' block on the queue
    unsigned next_block_idx = getNext();

    if (next_block_idx > 0)
    {
        current_scheme->computeBlock(next_block_idx);
    }
    else
    {
        // No more blocks !
        std::cout << "Reached the end. All blocks were computed!" << std::endl;
    }
}


/**
 * @brief Go back to the previous state.
 */
void Scheduler::undo()
{
    if (history)
    {  
        // copy everything from the memo
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
    
    this->print();
}


/**
 * @brief Set values for ports which are unconnected (CLI)
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
 * @brief Set values  for ports which are unconnected (GUI)
 * @param parent widget for which to display
 */
void Scheduler::setFreeInputsGui(QWidget* parent)
{
    if (!parent)
        return;

    for(unsigned b = 0; b < current_scheme->blocks.size(); b++)
    {
        for(unsigned p = 0; p < current_scheme->blocks[b]->getInSize(); p++)
        {
            if(current_scheme->isConnected(current_scheme->blocks[b]->getBlockID(), true, p) == 1) // if port is not connected
            {
                // create input dialog for every required user input
               bool status;
               std::stringstream msgstream;
               msgstream << "Set the value of port " << current_scheme->blocks[b]->getBlockID() << " in block " <<  p << ": ";
               std::string const msg(msgstream.str());

               QString value = QInputDialog::getText(parent, "BlockEditor prompt", QString::fromStdString(msg), QLineEdit::Normal, "Value:", &status);

               current_scheme->blocks[b]->setInPortValue(p,"val", value.toDouble());
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
bool Scheduler::checkCyclesRecursion(std::shared_ptr<Block> actual_block, std::vector<unsigned> visited)
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
