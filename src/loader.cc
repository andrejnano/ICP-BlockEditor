/**
 *  @file       loader.cc
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    0.1
 * 
 *  @brief ICP 2018, Project - Block Editor. Block Schema loader.
 *  
 *  @section Description
 * 
 *  
 */

#include <fstream>

#include "loader.h"
#include "utilities.h"

// creates new blank scheme
Scheme * Loader::createScheme(std::string scheme_name)
{
    return new Scheme(scheme_name);
}

// loads and returns a scheme from the file_path
Scheme * Loader::loadScheme(std::string file_path)
{
    std::string opcode, a, b, c, d;
    unsigned id, ins, outs;
    std::ifstream file (file_path);
    if (file.is_open())
    {
        // TODO: get the scheme name... temp. blank name
        Scheme *new_scheme = new Scheme("no_name_supplied");

        while ( getline (file, opcode) )
        {
            std::cout << opcode << std::endl; // ?TODO: debug or ?  

            getline (file, a);
            getline (file, b);
            getline (file, c);
            if(opcode == "wire")
            {
                getline (file, d);
                new_scheme->connect(std::stoul(a), std::stoul(b), std::stoul(c), std::stoul(d));
            }
            else
            {
                id = std::stoul(a);
                ins = std::stoul(b);
                outs = std::stoul(c);
                Block* new_block;
                if(opcode == "sum")
                {
                    new_block = new Block(id, SUM, t_simple, t_simple);
                    new_block->setOperation(SUM);
                }
                else if(opcode == "avg")
                {
                    new_block = new Block(id, AVG, t_simple, t_simple);
                    new_block->setOperation(AVG);
                }
                else if(opcode == "min")
                {
                    new_block = new Block(id, AVG, t_simple, t_simple);
                    new_block->setOperation(AVG);
                }
                else if(opcode == "max")
                {
                    new_block = new Block(id, AVG, t_simple, t_simple);
                    new_block->setOperation(AVG);
                }
                else
                {
                    std::cout << "Unrecognized block type! Must be 'sum', 'avg', min' or 'max'" << std::endl;
                    file.close();
                    return nullptr;
                }

                // same for all block types
                new_scheme->blocks.push_back(new_block);
                new_scheme->block_id = id + 1; // TODO: ideally switch to incrementID() method

                // set number of ports
                for(unsigned i = ins; i > 2; i--)
                {
                    new_scheme->addBlockInPort(id);
                }
                for(unsigned i = outs; i > 1; i--)
                {
                    new_scheme->addBlockOutPort(id);
                }
            }
        }
        file.close();
        return new_scheme;
    }
    return nullptr;
}

// saves the *scheme to the file_path
bool Loader::saveScheme(std::string file_path, Scheme *scheme)
{
    // TODO: add exception handling.. 

    try
    {
        std::ofstream file (file_path);

        // blocks
        for(unsigned i = 0; i < scheme->blocks.size(); i++)
        {
            file << scheme->blocks[i]->getStringType() << std::endl;
            file << scheme->blocks[i]->getBlockID() << std::endl;
            file << scheme->blocks[i]->getInSize() << std::endl;
            file << scheme->blocks[i]->getOutSize() << std::endl;
        }

        // connections
        for(unsigned i = 0; i < scheme->wires.size(); i++)
        {
            file << "wire" << std::endl;
            file << scheme->wires[i].id_out << std::endl;
            file << scheme->wires[i].index_out << std::endl;
            file << scheme->wires[i].id_in << std::endl;
            file << scheme->wires[i].index_in << std::endl;
        }
        file.close();
    }
    catch(std::ofstream::failure e)
    {
        error(E_SCHEMA_LOAD, "Cannot open/read/close the schema file.", true);
    }
    
}