/**
 *  @file       utilities.h
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    0.1
 * 
 *  @brief ICP 2018, Project - Block Editor. Utilities header.
 *  
 *  @section Description
 *  
 */

#ifndef BLOCKEDITOR_MISC_H_
#define BLOCKEDITOR_MISC_H_

#include <string>
#include <cstdio>  //required for printf

enum err_code_t
{
  // default success exit
  SUCCESS         = 0,

  // internal application errors
  E_INTERNAL      = 11,
  E_FILE_IO       = 12,
  E_UNDEF         = 13,

  // block schema specific
  E_SCHEMA_LOAD   = 21,
  E_SCHEMA_SAVE   = 22,
  E_SCHEMA_OTHER  = 23,

  // block specific 
  E_BLOCK_CREATE  = 31,
  E_BLOCK_WORK    = 32,

  // scheduler specific
  E_SCHEDULER     = 40

};

// usage: cout << CL::OKGREEN << "some text" << CL::ENDC << ... 
namespace CL {
  auto const OKBLUE     = "\033[94m";
  auto const OKGREEN    = "\033[92m";
  auto const WARNING    = "\033[93m";
  auto const FAIL       = "\033[91m";
  auto const ENDC       = "\033[0m";
  auto const BOLD       = "\033[1m";
  auto const UNDERLINE  = "\033[4m";
}


// default is to exit, but can be turned of by passing false
void error(err_code_t error_code, std::string error_msg, bool do_exit=true);

// show help and usage informations
void help();

// printout separator line
void separator(int chosen_char);

// printout headline
void headline(int chosen_char, std::string headline_text);

// printout paragraph offset text
void paragraph(std::string text);


#endif // BLOCKEDITOR_MISC_H_
