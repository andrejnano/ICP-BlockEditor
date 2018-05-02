/**
 *  @file       loader.h
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    0.1
 * 
 *  @brief ICP 2018, Project - Block Editor. Block Schema loader header.
 *  
 *  @section Description
 * 
 *  
 */

#ifndef BLOCKEDITOR_LOADER_H_
#define BLOCKEDITOR_LOADER_H_

#include "scheme.h"

class Loader
{
  public:
    // creates new blank scheme
    Scheme * createScheme(std::string scheme_name);

    // loads and returns a scheme from the file_path
    Scheme * loadScheme(std::string file_path);

    // saves the *scheme to the file_path
    bool saveScheme(std::string file_path, Scheme *scheme);
};

#endif