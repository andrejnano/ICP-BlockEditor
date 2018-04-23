/**
 *  @file       port.h
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    0.1
 * 
 *  @brief ICP 2018, Project - Block Editor. Port class header.
 *  
 *  @section Description
 * 
 */

#ifndef BLOCKEDITOR_PORT_H_
#define BLOCKEDITOR_PORT_H_

#include <vector>
#include <iostream>
#include <map>
#include <list>

enum data_type_t {t_simple};

class Port
{
  protected:
    int id; // maybe not necessary, ports are now indexed by array index in block
    data_type_t type;
    bool is_set;
    std::map<std::string, double> data;

  public:
    Port(int new_id, data_type_t new_type);
    void setValue(std::string name, double value);
    double getValue(std::string name);
    void print();
    bool isSet();
};

#endif