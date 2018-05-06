/**
 *  @file       loader.cc
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    1.0
 * 
 *  @brief ICP 2018, Project - Block Editor. Block Schema loader.
 *  
 *  @section Description
 * 
 *  
 */

#include <fstream>
#include <regex>

#include "loader.h"
#include "utilities.h"

// creates new blank scheme
std::shared_ptr<Scheme> Loader::createScheme(std::string scheme_name)
{
    return std::make_shared<Scheme>(scheme_name);
}

// loads and returns a scheme from the file_path
std::shared_ptr<Scheme> Loader::loadScheme(std::string file_path)
{
    // check the path format
    std::regex scheme_extensions("^.+\\.(scheme|sch)$");
    
    if ( std::regex_match(file_path, scheme_extensions) == false)
    {
       error(E_SCHEMA_LOAD, "Wrong scheme file extension format, or the path doesn't exist.");
    }

    // variable input
    std::string opcode, a, b, c, d;
    unsigned block_id, number_of_inputs, number_of_outputs;
    std::ifstream file (file_path);
    
    if (file.is_open())
    {
        // generic line
        std::string line;
        getline (file, line);
        
        // lowercase it
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);

        // check for the header
        if (line != "[blockeditor_scheme]")
        {
            error(E_SCHEMA_LOAD, "Wrong scheme file format! ");
        }

        // expect scheme name here
        getline (file, line);
        if (line.empty())
        {
            error(E_SCHEMA_LOAD, "Scheme name must be supplied");
        }

        // build new scheme
        std::shared_ptr<Scheme> new_scheme = std::make_shared<Scheme>(line);

        // expect either block or wire definitions
        while ( getline (file, line) )
        {
            // load line & lowercase it
            std::transform(line.begin(), line.end(), line.begin(), ::tolower);

            // always expect at least 3 arguments
            getline (file, a);  // wire: first_block_id  |  block: block_id
            getline (file, b);  // wire: out_port_id     |  block: number_of_inputs
            getline (file, c);  // wire: second_block_id |  block: number_of_outputs

            if(line == "wire")
            {
                getline (file, d); // in_port_id
                new_scheme->connect(std::stoul(a), std::stoul(b), std::stoul(c), std::stoul(d));
            }
            else
            {
                block_id = std::stoul(a);
                number_of_inputs = std::stoul(b);
                number_of_outputs = std::stoul(c);

                std::shared_ptr<Block> new_block;

                if(line == "sum")
                {
                    new_block = std::make_shared<Block>(block_id, SUM, t_simple, t_simple);
                    new_block->setOperation(SUM);
                }
                else if(line == "avg")
                {
                    new_block = std::make_shared<Block>(block_id, AVG, t_simple, t_simple);
                    new_block->setOperation(AVG);
                }
                else if(line == "min")
                {
                    new_block = std::make_shared<Block>(block_id, MIN, t_simple, t_simple);
                    new_block->setOperation(MIN);
                }
                else if(line == "max")
                {
                    new_block = std::make_shared<Block>(block_id, MAX, t_simple, t_simple);
                    new_block->setOperation(MAX);
                }
                else if(line == "count")
                {
                    new_block = std::make_shared<Block>(block_id, COUNT, t_simple, t_simple);
                    new_block->setOperation(COUNT);
                }
                else
                {
                    std::cout << "Unrecognized block type! Must be 'sum', 'avg', min' or 'max'" << std::endl;
                    file.close();
                    return nullptr;
                }

                // same for all block types
                new_scheme->blocks.push_back(new_block);
                new_scheme->last_block_id = block_id + 1;

                // set number of ports
                for(unsigned i = number_of_inputs; i > 2; i--)
                {
                    new_scheme->addBlockInPort(block_id);
                }
                for(unsigned i = number_of_outputs; i > 1; i--)
                {
                    new_scheme->addBlockOutPort(block_id);
                }
            }
        }
        file.close();
        return new_scheme;
    }
    return nullptr;
}

// saves the *scheme to the file_path
// TODO: if the file_path is not supplied, use some default location/extension and use the name of the scheme as filename
bool Loader::saveScheme(std::string file_path, std::shared_ptr<Scheme> scheme)
{
    if (!scheme)
    {
        error(E_SCHEMA_SAVE, "No scheme is currently active. Nothing to save.");
    }

    // check the path format
    std::regex scheme_extensions("^.+\\.(scheme|sch)$");
    if ( std::regex_match(file_path, scheme_extensions) == false)
    {
       error(E_SCHEMA_LOAD, "Wrong scheme file extension format, or the path is invalid.");
    }

    try
    {
        std::ofstream file (file_path);

        file << "[blockeditor_scheme]" << std::endl;
        file << scheme->getName() << std::endl;

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
        error(E_SCHEMA_LOAD, "Cannot open/read/close the schema file.");
        return false;
    }
    
    return true;
}