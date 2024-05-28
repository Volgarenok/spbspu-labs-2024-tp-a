#include "commands.hpp"
#include <functional>
#include <fstream>
#include <Delimiter.hpp>
#include "interface.hpp"

void chernikova::doCommand(std::map< std::string, Dictionary >& dataBase, const std::string& command)
{

}

void chernikova::readData(std::map< std::string, Dictionary >& dataBase, std::istream& input)
{
  std::string fileName = "";
  std::string dictionaryName = "";

  input >> fileName >> PunctuationI{ ' ' } >> dictionaryName >> PunctuationI{ '\n' };

  if (!input)
  {
    handleError();
    return;
  }

  std::ifstream file(fileName);

  if (!file.is_open())
  {
    printError();
    return;
  }

  dataBase[dictionaryName].read(file);
}
