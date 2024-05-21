#include "commands.hpp"

std::string chernikova::inputCommand(std::istream& in)
{
  std::string command;
  getline(in, command);
  if (!in)
  {
    throw std::runtime_error("Error input");
  }

  return command;
}