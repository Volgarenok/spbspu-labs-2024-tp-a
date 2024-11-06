#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdexcept>
#include <map>
#include <functional>
#include <limits>
#include "number_format.hpp"
#include "collection_commands.hpp"
#include "secondary_commands.hpp"

int main(int argc, char ** argv)
{
  using namespace erohin;
  if (argc == 2 && !strcmp(argv[1], "--help"))
  {
    printHelp(std::cout);
    return 0;
  }
  else if (argc == 3 && !strcmp(argv[1], "--check"))
  {
    checkDictionary(argv[2], std::cout);
    return 0;
  }
  numformat_t used_numformat = NUMBER;
  if (argc == 3)
  {
    std::string format_arg(argv[1]);
    if (format_arg.substr(0, 12) == "--numformat=")
    {
      std::map< std::string, numformat_t > format;
      format["NUMBER"] = NUMBER;
      format["PROPORTION"] = PROPORTION;
      format["FRACTIONAL"] = FRACTIONAL;
      format["PERCENTAGE"] = PERCENTAGE;
      try
      {
        used_numformat = format.at(format_arg.substr(12));
      }
      catch (const std::out_of_range &)
      {
        std::cerr << "Wrong number format\n";
        return 1;
      }
    }
    else
    {
      std::cerr << "Wrong CLA to identify numformat\n";
      return 2;
    }
  }
  else if (argc != 2)
  {
    std::cerr << "Wrong CLA's number\n";
    return 3;
  }
  std::fstream file(argv[argc - 1], std::ios::in);
  collection dict_context;
  inputCollection(dict_context, file);
  file.close();
  texts_source text_context;
  using command_func = std::function< void(std::istream &, std::ostream &) >;
  std::map< std::string, command_func > command;
  {
    using namespace std::placeholders;
    command["addtext"] = std::bind(addTextCommand, std::ref(text_context), _1, _2);
    command["removetext"] = std::bind(removeTextCommand, std::ref(text_context), _1, _2);
    command["createdict"] = std::bind(createDictCommand, std::ref(dict_context), std::cref(text_context), _1, _2);
    command["removedict"] = std::bind(removeDictCommand, std::ref(dict_context), _1, _2);
    command["print"] = std::bind(printCommand, std::cref(dict_context), _1, _2, used_numformat);
    command["count"] = std::bind(countCommand, std::cref(dict_context), _1, _2);
    command["sort"] = std::bind(sortCommand, std::cref(dict_context), _1, _2, used_numformat);
    command["find"] = std::bind(findCommand, std::cref(dict_context), _1, _2, used_numformat);
    command["top"] = std::bind(topCommand, std::ref(dict_context), _1, _2);
    command["bottom"] = std::bind(bottomCommand, std::ref(dict_context), _1, _2);
    command["differ"] = std::bind(differCommand, std::ref(dict_context), _1, _2);
    command["unite"] = std::bind(uniteCommand, std::ref(dict_context), _1, _2);
    command["intersect"] = std::bind(intersectCommand, std::ref(dict_context), _1, _2);
  }
  std::string command_name;
  std::cin >> command_name;
  while (!std::cin.eof())
  {
    try
    {
      command.at(command_name)(std::cin, std::cout);
    }
    catch (const std::underflow_error &)
    {
      std::cout << "<EMPTY>\n";
    }
    catch (const std::exception &)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::cin >> command_name;
  }
  file.open(argv[argc - 1], std::ios::trunc | std::ios::out);
  outputCollection(dict_context, file);
  file.close();
  return 0;
}
