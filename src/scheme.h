/**
 *  @file       scheme.h
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    0.1
 * 
 *  @brief ICP 2018, Project - Block Editor. Scheme class header.
 *  
 *  @section Description
 * 
 *  
 */

#ifndef BLOCKEDITOR_SCHEME_H_
#define BLOCKEDITOR_SCHEME_H_

#include "port.h"
#include "blocks.h"
#include "scheduler.h"
#include "loader.h"

#define FIRST_ID 1001

struct wire{
    unsigned id_out;    // ID of output block (source)
    unsigned index_out; // index of output port in block
    unsigned id_in;     // ID of input block (target)
    unsigned index_in;  // index of input port in block
};

/**
 * @brief Class for the Block Scheme, contianing blocks connected to each other
 */
class Scheme final 
{
friend class Loader;            // enable the loader to access all of scheme data
friend class Scheduler;         // to enable direct loading into the scheduler

private:
    std::string name;           // name of the scheme
    unsigned block_id;          // current last available index for new block TODO:rename to current_/available_
    std::vector<Block*> blocks; // list of block pointers contained in the scheme
    std::vector<wire> wires;    // list of wires (connections) contained in the scheme
    Scheduler scheduler;        // TODO: shouldn't the scheduler use a scheme ? e.g. make this reverse.. 

public:
    Scheme(std::string new_name) : name {new_name}, block_id {FIRST_ID} {}

    // return the scheme name
    std::string getName();

    // returns the number of blocks
    unsigned getBlockCount();

    // increment actual ID value
    void incrementID();

    // adds new block to the scheme
    void addBlock(operation_type_t new_type, data_type_t input_type, data_type_t output_type);
    // removes block from the scheme
    void removeBlock(unsigned block_id);

        /* TODO: [REFACTOR?] */
    // sets a new value for a specific port
    void setBlockPortValue(unsigned block_id, unsigned port_num, std::string val_name, double new_value);

        /* TODO: [REFACTOR?] */
    // returns the value from a specific port
    double getBlockPortValue(unsigned block_id, unsigned port_num, std::string val_name);

        /* TODO: [PUT TO SCHEDULER], shceme should just return the pointer to the block */
    // executes the computation for the block and propagates the result
    void computeBlock(unsigned block_id);

    // connects ports from one block to another
    bool connect(unsigned out_block_id, unsigned out_port_index, unsigned in_block_id, unsigned in_port_index);

    // removes connection
    void removeConnection(unsigned out_block_id, unsigned out_port_index, unsigned in_block_id, unsigned in_port_index);

    // checks, if the port is connected
    int isConnected(unsigned block_id, bool is_input, unsigned port_index);

    /* TODO: [PUT TO SCHEDULER], shceme should just return the pointer to the block */
    // propagates the result to the other block
    void propagate(unsigned block_id);

    /* VERY USEFUL FOR THE SCHEDULER */
    // returns a pointer to the block looked up by ID
    Block* getBlockByID(unsigned searched_id);

    /* useful for CLI, TODO: create GUI version of this.. */
    // outputs information about the block
    void print();

    /* TODO: [??? block/scheduler/or scheme? ] */
    // handles ports in block
    void addBlockInPort(unsigned block_id);
    void addBlockOutPort(unsigned block_id);
    void removeBlockInPort(unsigned block_id, unsigned port_index);
    void removeBlockOutPort(unsigned block_id, unsigned port_index);

    /* TODO: [DEFINITELY SCHEDULER STUFF] */
    // check if there are cycles in scheme
    bool checkCycles();
    bool checkCyclesRecursion(Block* actual_block, std::vector<unsigned> visited);

    /* TODO: [???] */
    // asks to set free input ports
    void setFreeInputs();
    double getUserValue(unsigned block_id, unsigned port_index);

    /* TODO: [DEFINITELY SCHEDULER STUFF] */
    // makes next step of computation - computes next prepared block
    void step();

    /* TODO: [PROBABLY OK,.. still check] */
    // cooperation with scheduler
    void loadIntoScheduler();
    void printScheduler();

};


#endif
