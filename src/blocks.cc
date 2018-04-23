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
#include <map>

#include "blocks.h"


/**
 * @brief Block constructor
 * @param new_type type of block
 * @param new_id identification of block
 * @param input_type data type of input ports
 * @param output_type data type of result
 */
Block::Block(unsigned new_id, data_type input_type, data_type output_type) : id {new_id}
{
    operation_ = nullptr;
    this->in_ports.push_back(Port(2,t_simple));
    this->in_ports.push_back(Port(3,t_simple));
    this->out_ports.push_back(Port(5,t_simple));
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
 * @brief prints information about block and call print functions for ports
 */
void Block::print()
{
    std::cout << "--------- BLOCK ---------" << std::endl;
    std::cout << "ID: " << this->id << std::endl;
    // std::cout << "TYPE: " << this->type << std::endl; // @TODO: replace 
    
    std::cout << "INPUTS:" << std::endl;
    for(unsigned i = 0; i < this->in_ports.size(); i++)
    {
        this->in_ports[i].print();
    }
    
    std::cout << "OUTPUTS:" << std::endl;
    for(unsigned i = 0; i < this->out_ports.size(); i++)
    {
        this->out_ports[i].print();
    }
    std::cout << "-------------------------" << std::endl;
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