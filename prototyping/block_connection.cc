
// connect using vectors of input/output blocks

#include <vector>
#include <iostream>

class BlockObject
{
  private:
    std::vector<BlockObject*> in;
    std::vector<BlockObject*> out;
};