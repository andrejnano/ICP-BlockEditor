
// types.h

#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <iostream>
#include <map>

//#include "port.h"
//#include "blocks.h"



class Type
{
  protected:
    std::map<std::string, double> data;
};

class simple: public Type
{
    public:
        simple();
        setValue(double value);
        print();

};

#endif