#include "userInterface.hpp"
#include <iostream>
#include <string>

std::ostream& petrov::UserInterface::deleteText(std::istream& in, std::ostream& out)
{
  std::string name;
  in >> name;

  auto deletable = texts_.find(name);
  if (deletable == texts_.end())
  {
    out << "<INVALID NAME>\n";
  }
  texts_.erase(deletable);
  return out;
}
