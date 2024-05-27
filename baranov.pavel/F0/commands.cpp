#include "commands.hpp"
#include <fstream>
#include "dictFunctions.hpp"

void baranov::create(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dictName;
  in >> dictName;
  dicts[dictName];
  if (in.peek() != '\n')
  {
    std::string fileName;
    in >> fileName;
    std::ifstream file(fileName);
    fillDict(dicts[dictName], file);
  }
}
