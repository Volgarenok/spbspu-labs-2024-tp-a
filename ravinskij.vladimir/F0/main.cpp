#include <functional>
#include <iostream>
#include <unordered_map>
#include <string>
#include <limits>
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace ravinskij;
  if (argc == 2)
  {
    std::string arg(argv[1]);
    if (arg == "--help")
    {
      printHelp(std::cout);
      return 0;
    }
    else
    {
      std::cerr << "Invalid parameter. --help is available.\n";
      return 1;
    }
  }
  encodesTable table;
  fileTable files;
  traverserTable traverses;

  using Command = std::function< void(std::istream&) >;
  std::unordered_map< std::string, Command > commands;
  using namespace std::placeholders;
  commands["add-text"] = std::bind(ravinskij::addText, _1, std::ref(files));
  commands["save-text"] = std::bind(ravinskij::saveText, _1, std::ref(files));
  commands["delete-text"] = std::bind(ravinskij::deleteText, _1, std::ref(files));
  commands["print-text"] = std::bind(ravinskij::printText, _1, std::ref(std::cout), std::cref(files));
  commands["create-encoding"] = std::bind(ravinskij::createEncoding, _1, std::ref(table), std::ref(traverses), std::cref(files));
  commands["delete-encoding"] = std::bind(ravinskij::deleteEncoding, _1, std::ref(table), std::ref(traverses));
  commands["encode"] = std::bind(ravinskij::encode, _1, std::cref(table), std::ref(files));
  commands["decode"] = std::bind(ravinskij::decode, _1, std::cref(traverses), std::ref(files));
  commands["add-encoding"] = std::bind(ravinskij::addEncoding, _1, std::ref(table), std::ref(traverses));
  commands["save-encoding"] = std::bind(ravinskij::saveEncoding, _1, std::cref(table), std::cref(traverses));
  commands["compare-encodings"] = std::bind(ravinskij::compareEncodings, _1, std::ref(std::cout), std::cref(files), std::cref(table));
  commands["print-files"] = std::bind(ravinskij::printFiles, _1, std::ref(std::cout), std::cref(files));
  commands["print-texts"] = std::bind(ravinskij::printTexts, _1, std::ref(std::cout), std::cref(files));
  commands["print-all"] = std::bind(ravinskij::printAll, _1, std::ref(std::cout), std::cref(files));

  std::string cmd;

  while (std::cin >> cmd)
  {
    try
    {
      commands.at(cmd)(std::cin);
    }
    catch (const std::out_of_range& e)
    {
      std::cout << "<INVALID_COMMAND>\n";
    }
    catch (const std::logic_error &e)
    {
      std::cout << "<INVALID_COMMAND>\n";
    }
    catch (...)
    {
      std::cerr << "UNEXPECTED ERROR\n";
      return 1;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  return 0;
}
