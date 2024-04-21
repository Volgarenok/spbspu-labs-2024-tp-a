#ifndef COMMAND_TYPE_HPP
#define COMMAND_TYPE_HPP

#include <string>
#include <istream>

namespace nikitov
{
  struct CommandType
  {
    std::string line;
  };

  std::istream& operator>>(std::istream& input, CommandType& value);
}
#endif
