#include "Dict.h"
#include <string>
#include <iostream>
#include <map>
#include "Commands.h"

using TextMap = std::multimap<std::string, std::pair<size_t, size_t>>;

stepanov::Commands::Commands()
{
  dict1_.insert({"input", input});
  dict1_.insert({"remove", remove});
  dict1_.insert({"delByWord", delByWord});

  dict2_.insert({"output", output});

  dict3_.insert({"addLine", addLine});

  dict4_.insert({"add", add});
  dict4_.insert({"merge", merge});
  dict4_.insert({"intersection", intersection});
  dict4_.insert({"substract", substract});
  dict4_.insert({"change", change});

  dict5_.insert({"deleteMap", deleteMap});

  dict6_.insert({"swapStr", swapStr});

  dict7_.insert({"output", output});
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