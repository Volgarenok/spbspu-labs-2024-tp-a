#include <functional>
#include <iterator>
#include <numeric>
#include <limits>
#include <numeric>
#include <exception>
#include <unordered_map>
#include "commands.hpp"
#include "node.hpp"

int main(int argc, char* argv[])
{
  using namespace artemev;
  if (argc == 2)
  {
    std::string arg(argv[1]);
    if (arg == "--help")
    {
      printHelp();
      return 0;
    }
    else
    {
      std::cerr << "Invalid parameter\n";
      return 1;
    }
  }
  codesSheet codes;
  fileSheet files;
  codeText codeText;
  freqSheet freq;
  queueSheet queue;

  using Command = std::function< void(std::istream&) >;
  std::unordered_map< std::string, Command > commands;
  {
    using namespace std::placeholders;
    commands["create"] = std::bind(artemev::create, _1);
    commands["read"] = std::bind(artemev::read, _1, std::ref(files));
    commands["save"] = std::bind(artemev::save, _1, std::ref(files));
    commands["code"] = std::bind(artemev::code, _1, std::ref(codes), std::cref(files), std::ref(freq), std::ref(queue));
    commands["printtext"] = std::bind(artemev::printText, _1, std::ref(std::cout), std::cref(files));
    commands["printtable"] = std::bind(artemev::printTable, _1, std::ref(std::cout), std::cref(freq));
    commands["encode"] = std::bind(artemev::encode, _1, std::ref(codes), std::cref(files), std::ref(codeText));
    commands["write"] = std::bind(artemev::write, _1, std::ref(codeText), std::ref(codes), std::ref(freq), std::ref(queue));
    commands["uncode"] = std::bind(artemev::uncode, _1);
    commands["delete"] = std::bind(artemev::deleteFiles, _1);
    commands["size"] = std::bind(artemev::size, _1, std::ref(std::cout));
    commands["compare"] = std::bind(artemev::comparator, _1, std::ref(std::cout));
  }

  std::string cmd;
  while (std::cin >> cmd && !std::cin.eof())
  {
    try
    {
      commands.at(cmd)(std::cin);
    }
    catch (const std::out_of_range& e)
    {
      std::cout << "<INVALID_COMMAND>\n\n";
    }
    catch (const std::logic_error& e)
    {
      std::cout << e.what() << "\n\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  return 0;
}
