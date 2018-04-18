
// port.cc

#include <vector>
#include <iostream>
#include <map>
#include <list>

#include "port.h"

Port::Port(data_type new_type)
{
    this->type = new_type;
    this->values.clear();
}