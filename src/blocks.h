/**
 *  @file       blocks.h
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    1.0
 * 
 *  @brief ICP 2018, Project - Block Editor. Block class header.
 *  
 *  @section Description
 *  
 */

#ifndef BLOCKEDITOR_BLOCKS_H_
#define BLOCKEDITOR_BLOCKS_H_

#include <vector>
#include <iostream>
#include <map>
#include <memory>

#include "port.h"


enum operation_type_t
{
  SUM,
  AVG,
  MIN,
  MAX,
  COUNT
};

/* 
  Inspired by Strattegy pattern

  each block has a 'compute()' method which executes private virtual method, 
  specified by the operation type for the block. Operation can be changed dynamically.
*/

class Operation
{
  public:
    Operation() {}
    virtual ~Operation() {} // needs to be virtual, as the delete is called on sub class

    // outside interface for executing
    void execute(std::vector<Port> &inputs, std::vector<Port> &outputs);

  private:
    // internal expression execution, defined for each specific operation
    virtual double expression(std::vector<Port>) = 0;

};

class SumOp : public Operation
{
  public:
    SumOp(): Operation(){}

  private:
    double expression(std::vector<Port> inputs) override;
};

class AvgOp: public Operation
{
  public:
    AvgOp(): Operation(){}

  private:
    double expression(std::vector<Port> inputs) override;
};

class MinOp : public Operation
{
  public:
    MinOp(): Operation(){}

  private:
    double expression(std::vector<Port> inputs) override;
};

class MaxOp : public Operation
{
  public:
    MaxOp(): Operation(){}

  private:
    double expression(std::vector<Port> inputs) override;
};

class CountOp : public Operation
{
  public:
    CountOp(): Operation(){}

  private:
    double expression(std::vector<Port> inputs) override;
};


class Block
{
  private:
    Operation* operation_;

  protected:
    unsigned id;
    operation_type_t block_type;
    data_type_t in_type;
    data_type_t out_type;
    std::vector<Port> in_ports;
    std::vector<Port> out_ports;

  public:
    Block(unsigned new_id, operation_type_t new_type, data_type_t input_type, data_type_t output_type);
    
    inline ~Block()
    {
      delete operation_;
    }

    // adds new input port
    void addNewInPort();

    // adds new output port
    void addNewOutPort();

    // removes input port
    void removeInPort(unsigned port_index);

    // adds new output port
    void removeOutPort(unsigned port_index);

    // sets value for single IN port
    void setInPortValue(unsigned port_num, std::string val_name, double new_value);

    // return the value of single OUT port
    double getOutPortValue(unsigned port_num, std::string val_name);
    
    // return the block ID
    unsigned getBlockID();

    // return the number of IN ports inside the block
    unsigned getInSize();

    // return the number of OUT ports inside the block
    unsigned getOutSize();

    // sets type of operation for the block
    void setOperation(operation_type_t op_type);
    
    // computation specific for each operation type
    inline void compute()
    {
      operation_->execute(in_ports, out_ports);
    }

    // prints information about the block
    void print();

    // returns true if block has set values in all input port
    bool isPrepared();

    // return string representating type of block
    std::string getStringType();

    // removes values in input ports
    void resetInPortValues(unsigned port_index);

    // removes values in output ports
    void resetOutPortValues(unsigned port_index);


    // TODO: refactor
    std::vector<Port> getInPorts()
    {
        return in_ports;
    }

    std::vector<Port> getOutPorts()
    {
        return out_ports;
    }
};


#endif
