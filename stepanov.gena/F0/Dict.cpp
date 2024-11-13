#include "Dict.h"
#include <string>
#include <iostream>
#include <map>
#include "Commands.h"

using TextMap = std::multimap<std::string, std::pair<size_t, size_t>>;

stepanov::Commands::Commands()
{
  dict1_.insert({"INPUT", input});
  dict1_.insert({"REMOVE", remove});
  dict1_.insert({"DELBYWORD", delByWord});

  dict2_.insert({"OUTPUT", output});

  dict3_.insert({"ADDLINE", addLine});

  dict4_.insert({"ADD", add});
  dict4_.insert({"MERGE", merge});
  dict4_.insert({"INTERSECTION", intersection});
  dict4_.insert({"SUBSTRACT", substract});
  dict4_.insert({"CHANGE", change});

  dict5_.insert({"DELETE", deleteMap});

  dict6_.insert({"SWAPSTR", swapStr});

  dict7_.insert({"OUTPUT", output});
}

void stepanov::Commands::runCommand(std::istream& in, std::ostream& out)
{
  std::map<std::string, TextMap> textMaps;

  while (in)
  {
    std::string command;
    in >> command;

    try
    {
      auto func = dict1_.at(command);
      std::string mapName, fileName;
      in >> mapName >> fileName;
      func(textMaps, mapName, fileName);
    }
    catch (...)
    {
    }

    try
    {
      auto func = dict2_.at(command);
      std::string mapName;
      in >> mapName;
      func(textMaps, mapName, out);
    }
    catch (...)
    {
    }

    try
    {
      auto func = dict3_.at(command);
      std::string mapName, str;
      size_t pos;
      in >> mapName >> str >> pos;
      func(textMaps, mapName, str, pos);
    }
    catch (...)
    {
    }

    try
    {
        auto func = dict4_.at(command);
        std::string mapName3, mapName1, mapName2;
        in >> mapName3 >> mapName1 >> mapName2;
        func(textMaps, mapName3, mapName1, mapName2);
    }
    catch (...)
    {
    }

    try
    {
      auto func = dict5_.at(command);
      std::string mapName;
      in >> mapName;
      func(textMaps, mapName);
    }
    catch (...)
    {
    }

    try
    {
      auto func = dict6_.at(command);
      std::string mapName;
      size_t pos1, pos2;
      in >> mapName >> pos1 >> pos2;
      func(textMaps, mapName, pos1, pos2);
    }
    catch (...)
    {
    }
  }
}