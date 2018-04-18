
// types.cc

#include <vector>
#include <iostream>
#include <map>

#include "types.h"

simple::simple()
{
    this->data.insert(std::pair <std::string, double> ("val", 0.0));
}

simple::setValue(double value)
{
    this->data["val"] = value;
}

simple::print()
{
    std::cout << "val = " << this->data["val"] << std::endl;
}