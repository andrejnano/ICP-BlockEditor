
// port.h

#ifndef PORT_H
#define PORT_H

#include <vector>
#include <iostream>
#include <map>
#include <list>


enum data_type {t_simple};

class Port
{
  protected:
    data_type type;
    std::map<std::string, double> data;

  public:
    Port(data_type new_type);
    void setValue(std::string name, double value);
    void print();
};

#endif