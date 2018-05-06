/**
 *  @file       loader.h
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    1.0
 * 
 *  @brief ICP 2018, Project - Block Editor. Block Schema loader header.
 *  
 *  @section Description
 * 
 *  
 */

#ifndef BLOCKEDITOR_LOADER_H_
#define BLOCKEDITOR_LOADER_H_

#include <memory>

#include "scheme.h"

class Loader
{
  public:
    // creates new blank scheme
    std::shared_ptr<Scheme> createScheme(std::string scheme_name);

    // loads and returns a scheme from the file_path
    std::shared_ptr<Scheme> loadScheme(std::string file_path);

    // saves the *scheme to the file_path
    bool saveScheme(std::string file_path, std::shared_ptr<Scheme> scheme);
};

#endif