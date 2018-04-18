
// port.h

#ifndef PORT_H
#define PORT_H

#include <vector>
#include <iostream>
#include <map>
#include <list>

#include "types.h"

enum data_type {t_simple};

class Port
{
  protected:
    data_type type;
    std::list<Type> values;

  public:
    Port(data_type new_type);
};

#endif