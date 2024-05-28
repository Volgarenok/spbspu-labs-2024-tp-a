#ifndef ARGUEMENTS_HPP
#define ARGUEMENTS_HPP

#include <map>
#include <string>
#include "interface.hpp"
#include "Dictionary.hpp"

namespace chernikova
{
  bool processArguements(char* argv[], int argc, std::map< std::string, Dictionary >& dataBase);
}

#endif
