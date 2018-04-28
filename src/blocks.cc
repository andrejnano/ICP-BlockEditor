/**
 *  @file       blocks.cc
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    0.1
 * 
 *  @brief ICP 2018, Project - Block Editor. Block class.
 *  
 *  @section Description
 * 
 */

#include <vector>
#include <iostream>
#include <iomanip>
#include <map>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

#include "blocks.h"
#include "utilities.h"



/**
 * @brief Block constructor
 * @param new_type type of block
 * @param new_id identification of block
 * @param input_type data type of input ports
 * @param output_type data type of result
 */
Block::Block(unsigned new_id, operation_type_t new_type, data_type_t input_type, data_type_t output_type) : id {new_id}
{
    operation_ = nullptr;
    this->block_type = new_type;
    this->in_type = input_type;
    this->out_type = output_type;
    this->in_ports.push_back(Port(2,t_simple));
    this->in_ports.push_back(Port(3,t_simple));
    this->out_ports.push_back(Port(5,t_simple));
}

/**
 * @brief Adds new input port to the block
 */
void Block::addNewInPort()
{
    this->in_ports.push_back(Port(1,this->in_type));
}

/**
 * @brief Adds new output port to the block
 */
void Block::addNewOutPort()
{
    this->out_ports.push_back(Port(1,this->out_type));
}

/**
 * @brief Removes input port at specified index in block
 */
void Block::removeInPort(unsigned port_index)
{
    this->in_ports.erase(this->in_ports.begin() + port_index);
}

/**
 * @brief Removes output port at specified index in block
 */
void Block::removeOutPort(unsigned port_index)
{
    this->out_ports.erase(this->out_ports.begin() + port_index);
}

/**
 * @brief Sets operation for the block
 * @param op_type type of operation
 */
void Block::setOperation(operation_type_t type)
{
  delete operation_;

  switch (type)
  {
    case SUM: operation_ = new SumOp(); break;
    case AVG: operation_ = new AvgOp(); break;
    case MIN: operation_ = new MinOp(); break;
    case MAX: operation_ = new MaxOp(); break;
    case COUNT: operation_ = new CountOp(); break;
  }
}

/**
 * @brief sets value of input port
 * @param port_num index of port in array [0-n]
 * @param val_name name of value which should be changed ("val" in simple type)
 * @param new_value new value of port
 */
void Block::setInPortValue(unsigned port_num, std::string val_name, double new_value)
{
    this->in_ports[port_num].setValue(val_name, new_value);
}

/**
 * @brief gets value of output port
 * @param port_num index of port in array [0-n]
 * @param val_name name of value to get ("val" in simple type)
 * @return value of port
 */
double Block::getOutPortValue(unsigned port_num, std::string val_name)
{
    return this->out_ports[port_num].getValue(val_name);
}

/**
 * @brief gets ID of block
 * @return identification number of block
 */
unsigned Block::getBlockID()
{
    return this->id;
}

/**
 * @brief gets number of input ports
 * @return size of inputs vector
 */
unsigned Block::getInSize()
{
    return this->in_ports.size();
}

/**
 * @brief gets number of output ports
 * @return size of outputs vector
 */
unsigned Block::getOutSize()
{
    return this->out_ports.size();
}

/**
 * @brief check if block has set values in all input ports
 * @return true if all input ports are set, false if some value is missing
 */
bool Block::isPrepared()
{
    for(unsigned i = 0; i < this->in_ports.size(); i++)
    {
        if(this->in_ports[i].isSet() == false)
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief gets type of block
 * @return string representating block type, empty string when not recognized
 */
std::string Block::getStringType()
{
    if(this->block_type == SUM)
    {
        return "sum";
    }
    else if(this->block_type == AVG)
    {
        return "avg";
    }
    else if(this->block_type == MIN)
    {
        return "min";
    }
    else if(this->block_type == MAX)
    {
        return "max";
    }
    else if(this->block_type == COUNT)
    {
        return "count";
    }
    else
    {
        return "";
    }
}

/**
 * @brief prints information about block and call print functions for ports
 */
void Block::print()
{
    cout << "\n+ -------- BLOCK #" << CL::BOLD << CL::UNDERLINE << this->id << CL::ENDC << " -------- +" << endl;
    cout << "| TYPE: " << CL::OKBLUE << CL::BOLD << std::left << std::setw(23);

    switch(this->block_type)
    {
        case SUM:   cout << "SUM"; break;
        case AVG:   cout << "AVG"; break;
        case MIN:   cout << "MIN"; break;
        case MAX:   cout << "MAX"; break;
        case COUNT: cout << "COUNT"; break;
        default:    cout << "UNKNOWN"; break;
    }
    cout << CL::ENDC << " |" << std::endl; 
    
    
    std::cout << "| INPUT PORTS: " << std::setw(18) << std::right << "|" << std::endl;
    for(unsigned i = 0; i < this->in_ports.size(); i++)
    {
        this->in_ports[i].print();
    }
    
    std::cout << "| OUTPUT PORTS: " << std::setw(17) << std::right << "|" << std::endl;
    for(unsigned i = 0; i < this->out_ports.size(); i++)
    {
        this->out_ports[i].print();
    }

    std::cout << "+ ----------------------------- +\n" << std::endl;
}

/*****************************************************************************/
// Specific operations
/*****************************************************************************/

/**
 * @brief executes the operation and sets output ports with the result
 */
void Operation::execute(std::vector<Port> &inputs, std::vector<Port> &outputs)
{
    double result = expression(inputs);

    for(unsigned i = 0; i < outputs.size(); i++)
    {
        outputs[i].setValue("val", result);
    }
}


/**
 * @brief SUM operation
 */
double SumOp::expression(std::vector<Port> inputs)
{
    double sum {0.0};

    for(unsigned i = 0; i < inputs.size(); i++)
    {
        sum += inputs[i].getValue("val");
    }

    return sum;
}

/**
 * @brief AVG operation
 */
double AvgOp::expression(std::vector<Port> inputs)
{
    double sum {0.0};

    for(unsigned i = 0; i < inputs.size(); i++)
    {
        sum += inputs[i].getValue("val");
    }

    return sum/inputs.size();
}

/**
 * @brief MIN operation
 */
double MinOp::expression(std::vector<Port> inputs)
{
    double min = inputs[0].getValue("val");

    for(unsigned i = 1; i < inputs.size(); i++)
    {
        if (min > inputs[i].getValue("val"))
            min = inputs[i].getValue("val");
    }

    return min;
}

/**
 * @brief MAX operation
 */
double MaxOp::expression(std::vector<Port> inputs)
{
    double max = inputs[0].getValue("val");

    for(unsigned i = 1; i < inputs.size(); i++)
    {
        if (max < inputs[i].getValue("val"))
            max = inputs[i].getValue("val");
    }

    return max;
}

/**
 * @brief COUNT operation
 */
double CountOp::expression(std::vector<Port> inputs)
{
    return inputs.size();
}