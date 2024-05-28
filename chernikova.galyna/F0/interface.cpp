#include "interface.hpp"

void chernikova::printError(std::ostream& output)
{
  output << "<INVALID COMMAND>\n";
}

void chernikova::printEmptyError(std::ostream& output)
{
  output << "<EMPTY>\n";
}
