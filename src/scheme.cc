/**
 *  @file       scheme.cc
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    0.1
 * 
 *  @brief ICP 2018, Project - Block Editor. Scheme class.
 *  
 *  @section Description
 * 
 *  
 */

#include "scheme.h"
#include "blocks.h"
#include "utilities.h"

/**
 * @brief print scheme name, calls print functions for blocks, and prints wires
 */
void Scheme::print()
{
    std::cout << "SCHEME NAME: " << this->name << std::endl;
    std::cout << "PORTS:" << std::endl;
    for(unsigned i = 0; i < this->blocks.size(); i++)
    {
        this->blocks[i]->print();
    }
    std::cout << "WIRES:" << std::endl;
    for(unsigned i = 0; i < this->wires.size(); i++)
    {
        std::cout << "  OUT: " << this->wires[i].id_out << " (" << this->wires[i].index_out 
                << ") | IN: " << this->wires[i].id_in << " (" << this->wires[i].index_in << ")" << std::endl;
    }
}

/**
 * @brief adds new block to scheme
 * @param new_type type of new block
 * @param input_type data type of block inputs
 * @param output_type data type of block outputs
 */
void Scheme::addBlock(operation_type_t new_type, data_type_t input_type, data_type_t output_type)
{
    // creates new block object
    Block* new_block = new Block(block_id, new_type, input_type, output_type);
    
    // sets operation type
    new_block->setOperation(new_type);

    // adds to the scheme
    this->blocks.push_back(new_block);

    block_id++;
}

/**
 * @brief removes block with given ID
 * @param block_id ID of block which should be removed
 */
void Scheme::removeBlock(unsigned block_id)
{
    // remove wires
    bool removed = true;
    while(removed == true)
    {
        removed = false;
        std::vector<wire>::iterator it_wire = this->wires.begin();
        for(; it_wire != this->wires.end(); it_wire++)
        {
            if((*it_wire).id_out == block_id || (*it_wire).id_in == block_id)
            {
                removed = true;
                break;
            }
        }
        if(removed == true)
        {
            this->wires.erase(it_wire);
        }
    }

    // remove blocks
    std::vector<Block*>::iterator it = this->blocks.begin();
    for(; it != this->blocks.end(); it++)
    {
        if((*it)->getBlockID() == block_id)
        {
            break;
        }
    }
    this->blocks.erase(it);
}

/**
 * @brief calls compute function for given block
 * @param block_id identification number of block
 */
void Scheme::computeBlock(unsigned block_id)
{
    if(this->getBlockByID(block_id) != NULL)
    {
        this->getBlockByID(block_id)->compute();
        this->propagate(block_id);
    }
}

/**
 * @brief sets value of port
 * @param block_id identification number of block
 * @param port_num index of port in block [0-n]
 * @param val_name name of value in data type ("val" in simple type)
 * @param new_value value to be set
 */
void Scheme::setBlockPortValue(unsigned block_id, unsigned port_num, std::string val_name, double new_value)
{
    if(this->getBlockByID(block_id) != nullptr)
    {
        this->getBlockByID(block_id)->setInPortValue(port_num, val_name, new_value);
    }
}

/**
 * @brief gets value of port
 * @param block_id identification number of block
 * @param port_num index of port in block [0-n]
 * @param val_name name of value in data type ("val" in simple type)
 * @return value of port
 */
double Scheme::getBlockPortValue(unsigned block_id, unsigned port_num, std::string val_name)
{
    if(this->getBlockByID(block_id) != nullptr)
    {
        return this->getBlockByID(block_id)->getOutPortValue(port_num, val_name);
    }
    return 0;
}

/**
 * @brief sets new wire between two ports
 * @param out_block_id id of source block
 * @param out_port_index index of output port in block
 * @param in_block_id id of targe block
 * @param in_port_index index of input port in block
 * @return true if success, false in case of failure
 */
bool Scheme::connect(unsigned out_block_id, unsigned out_port_index, unsigned in_block_id, unsigned in_port_index)
{
    if(this->getBlockByID(out_block_id) == nullptr || this->getBlockByID(in_block_id) == nullptr)
    {
        std::cout << CL::FAIL << "block does not exist!" << CL::ENDC << std::endl;
        return false;// ID of block does not exist
    }
    if(this->getBlockByID(out_block_id)->getOutSize() <= out_port_index || this->getBlockByID(in_block_id)->getInSize() <= in_port_index)
    {
        std::cout << CL::FAIL << "index is out of vector!" << CL::ENDC << std::endl;
        return false;// index of port is out of vector               
    }
    if(isConnected(out_block_id, false, out_port_index) != 1 || isConnected(in_block_id, true, in_port_index) != 1)
    {
        std::cout << CL::FAIL << "port is already connected!" << CL::ENDC << std::endl;
        return false;// port is already connected 
    }
    wire tmp;
    tmp.id_out = out_block_id;
    tmp.index_out = out_port_index;
    tmp.id_in = in_block_id;
    tmp.index_in = in_port_index;
    this->wires.push_back(tmp);
    std::cout << CL::OKGREEN <<  "*conection made*" << CL::ENDC << std::endl;
    return true;
}

/**
 * @brief removes connection
 * @param out_block_id id of source block
 * @param out_port_index index of output port in block
 * @param in_block_id id of targe block
 * @param in_port_index index of input port in block
 */
void Scheme::removeConnection(unsigned out_block_id, unsigned out_port_index, unsigned in_block_id, unsigned in_port_index)
{
    std::vector<wire>::iterator it = this->wires.begin();
    for(; it != this->wires.end(); it++)
    {
        if((*it).id_out == out_block_id && (*it).index_out == out_port_index && (*it).id_in == in_block_id && (*it).index_in == in_port_index)
        {
            break;
        }
    }
    this->wires.erase(it);
}

/**
 * @brief check if port is connected
 * @param block_id ID of block
 * @param id_input true if finding input port, false if finding output port
 * @param port_index index of port in block
 * @return 0 if port is connected, 1 if not connected, -1 if port is not found
 */
int Scheme::isConnected(unsigned block_id, bool is_input, unsigned port_index)
{
    if(is_input)
    {
        if(this->getBlockByID(block_id) == NULL)
        {
            //std::cout << "*conection port NOT found*" << std::endl;
            return -1;
        }
        if(this->getBlockByID(block_id)->getInSize() <= port_index)
        {
            //std::cout << "*conection port NOT found*" << std::endl;
            return -1;
        }
        for(unsigned i = 0; i < this->wires.size(); i++)
        {
            if(this->wires[i].id_in == block_id && this->wires[i].index_in == port_index)
            {
                //std::cout << "*conection found*" << std::endl;
                return 0;
            }
        }
    }
    else
    {
        if(this->getBlockByID(block_id) == NULL)
        {
            //std::cout << "*conection port NOT found*" << std::endl;
            return -1;
        }
        if(this->getBlockByID(block_id)->getOutSize() <= port_index)
        {
            //std::cout << "*conection port NOT found*" << std::endl;
            return -1;
        }
        for(unsigned i = 0; i < this->wires.size(); i++)
        {
            if(this->wires[i].id_out == block_id && this->wires[i].index_out == port_index)
            {
                //std::cout << "*conection found*" << std::endl;
                return 0;
            }
        }

    }
    //std::cout << "*conection NOT found*" << std::endl;
    return 1;
}

/**
 * @brief propagate output value through wire or prints if port is not connected
 * @param block_id id of source block
 * @param port_index index of port in block
 * @return pointer to searched block, NULL if not found
 */
void Scheme::propagate(unsigned block_id)
{
    if(this->getBlockByID(block_id))
    {
        double result;
        bool found;
        for(unsigned p = 0; p < this->getBlockByID(block_id)->getOutSize(); p++)
        {
            result = this->getBlockByID(block_id)->getOutPortValue(p,"val");
            found = false;
            for(unsigned i = 0; i < this->wires.size(); i++)
            {
                if(this->wires[i].id_out == block_id && this->wires[i].index_out == p)
                {
                    this->setBlockPortValue(this->wires[i].id_in, this->wires[i].index_in, "val", result);
                    found = true;
                }
            }
            if(found == false)
            {
                std::cout << CL::OKBLUE << "~ RESULT AT FREE OUT PORT " << p << " IN BLOCK " << block_id << ": " << result << CL::ENDC << std::endl;
            }
        }
    }
}

/**
 * @brief finds block with given ID
 * @param searched_id identification number of searched block
 * @return pointer to searched block, NULL if not found
 */
Block* Scheme::getBlockByID(unsigned searched_id)
{
    for(unsigned i = 0; i < this->blocks.size(); i++)
    {
        if(this->blocks[i]->getBlockID() == searched_id)
        {
            return this->blocks[i];
        }
    }
    return nullptr;
}

/**
 * @brief adds new input port to given block
 * @param block_id identification number of block
 */
void Scheme::addBlockInPort(unsigned block_id)
{
    if(this->getBlockByID(block_id) != NULL)
    {
        this->getBlockByID(block_id)->addNewInPort();
    }
}

/**
 * @brief adds new output port to given block
 * @param block_id identification number of block
 */
void Scheme::addBlockOutPort(unsigned block_id)
{
    if(this->getBlockByID(block_id) != NULL)
    {
        this->getBlockByID(block_id)->addNewOutPort();
    }
}

/**
 * @brief removes input port in given block
 * @param block_id identification number of block
 * @param port_index index of port in given block
 */
void Scheme::removeBlockInPort(unsigned block_id, unsigned port_index)
{
    if(this->getBlockByID(block_id) != NULL)
    {
        this->getBlockByID(block_id)->removeInPort(port_index);
    }
}

/**
 * @brief removes output port in given block
 * @param block_id identification number of block
 * @param port_index index of port in given block
 */
void Scheme::removeBlockOutPort(unsigned block_id, unsigned port_index)
{
    if(this->getBlockByID(block_id) != NULL)
    {
        this->getBlockByID(block_id)->removeOutPort(port_index);
    }
}

/**
 * @brief checks if there are cycles in scheme
 * @return true if scheme is ok, false if cycle is detected
 */
bool Scheme::checkCycles()
{
    std::vector<unsigned> visited;
    std::cout << "CHECKING CYCLES:" << std::endl;
    for(unsigned i = 0; i < this->blocks.size(); i++)
    {
        if(this->checkCyclesRecursion(this->blocks[i], visited) == false)
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
bool Scheme::checkCyclesRecursion(Block* actual_block, std::vector<unsigned> visited)
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
    for(unsigned i = 0; i < this->wires.size(); i++)
    {
        if(this->wires[i].id_out == actual_block->getBlockID())
        {
            if(this->checkCyclesRecursion(this->getBlockByID(this->wires[i].id_in), new_visited) == false)
            {
                ret = false;
            }
        }
    }
    return ret;  
}

/**
 * @brief calls function to get input from user for every free input port
 */
void Scheme::setFreeInputs()
{
    for(unsigned b = 0; b < blocks.size(); b++)
    {
        for(unsigned p = 0; p < this->blocks[b]->getInSize(); p++)
        {
            if(this->isConnected(this->blocks[b]->getBlockID(), true, p) == 1)// if port is not connected
            {
                this->blocks[b]->setInPortValue(p,"val", this->getUserValue(this->blocks[b]->getBlockID(), p));
            }
        }
    }
}

double Scheme::getUserValue(unsigned block_id, unsigned port_index)
{
    std::cout << "Set the value of port " << port_index << " in block " << block_id << ": ";
    std::string val;
    std::cin >> val; 
    return std::stod(val);
}

/**
 * @brief loads pointer to blocks into scheduler
 */
void Scheme::loadIntoScheduler()
{
    for(unsigned i = 0; i < this->blocks.size(); i++)
    {
        this->scheduler.addBlock(this->blocks[i]);
    }
}

/**
 * @brief prints blocks stored in scheduler
 */
void Scheme::printScheduler()
{
    this->scheduler.print();
}

/**
 * @brief gets next prepared block from scheduler and computes it
 */
void Scheme::step()
{
    Block* next_block = this->scheduler.getNext();
    if(next_block == NULL)
    {
        std::cout << "all blocks were computed!" << std::endl;
    }
    else
    {
        this->computeBlock(next_block->getBlockID()); // computeBlock function contains also propagating result
    }
}