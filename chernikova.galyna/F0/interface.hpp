#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>

namespace chernikova
{
  void printError(std::ostream& output = std::cout);
  void printEmptyError(std::ostream& output = std::cout);
  void fixStream(std::istream& input);
}

#endif
