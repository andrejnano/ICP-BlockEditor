/**
 *  @file       scheme.h
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    1.0
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

#define FIRST_ID 1001

struct wire
{
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
    unsigned last_block_id;     // current last available index for new block
    std::vector<std::shared_ptr<Block>> blocks; // list of block pointers contained in the scheme
    std::vector<wire> wires;    // list of wires (connections) contained in the scheme

public:
    Scheme(std::string new_name) :
        name {new_name},
        last_block_id {FIRST_ID}
    {}

    // return the scheme name
    std::string getName();

    // adds new block to the scheme
    void addBlock(operation_type_t new_type, data_type_t input_type, data_type_t output_type);
    
    // removes block from the scheme
    void removeBlock(unsigned block_id);

    // sets a new value for a specific port
    void setBlockPortValue(unsigned block_id, unsigned port_num, std::string val_name, double new_value);

    // returns the value from a specific port
    double getBlockPortValue(unsigned block_id, unsigned port_num, std::string val_name);

    // executes the computation for the block and propagates the result
    void computeBlock(unsigned block_id);

    // connects ports from one block to another
    bool connect(unsigned out_block_id, unsigned out_port_index, unsigned in_block_id, unsigned in_port_index);

    // removes connection
    void removeConnection(unsigned out_block_id, unsigned out_port_index, unsigned in_block_id, unsigned in_port_index);

    // checks, if the port is connected
    int isConnected(unsigned block_id, bool is_input, unsigned port_index);

    // propagates the result to the other block
    void propagate(unsigned block_id);

    // returns a pointer to the block looked up by ID
    std::shared_ptr<Block> getBlockByID(unsigned searched_id);

    // outputs information about the block to the terminal
    void print();

    // handles ports in block
    void addBlockInPort(unsigned block_id);
    void addBlockOutPort(unsigned block_id);
    void removeBlockInPort(unsigned block_id, unsigned port_index);
    void removeBlockOutPort(unsigned block_id, unsigned port_index);

    // get input from user for some port
    double getUserValue(unsigned block_id, unsigned port_index);

    std::vector<std::shared_ptr<Block>> getBlockPointers();
    std::vector<wire> getWires();
};


#endif
