#include "interface.hpp"
#include <limits>

void chernikova::printError(std::ostream& output)
{
  output << "<INVALID COMMAND>\n";
}

void chernikova::printEmptyError(std::ostream& output)
{
  output << "<EMPTY>\n";
}

void chernikova::fixStream(std::istream& input)
{
  input.clear();
  input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void chernikova::handleError(std::istream& input, std::ostream& output)
{
  printError(output);
  fixStream(input);
}
