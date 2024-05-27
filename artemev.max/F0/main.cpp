#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <map>
#include <vector>
#include <iterator>
#include <numeric>
#include <limits>
#include <queue>
#include <algorithm>
#include <numeric>
#include <exception>
#include <climits>
#include "commands.hpp"
#include "node.hpp"

int main(int argc, char* argv[])
{
    using namespace artemev;
    using namespace std::placeholders;
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
  encodesSheet codes;
  fileSheet files;
  codeText codeText;
  freqSheet freq;
  queueSheet queue;

  using Command = std::function< void(std::istream &) >;
  std::unordered_map< std::string, Command > commands;
  {
    using namespace std::placeholders;
    commands["read"] = std::bind(artemev::read, _1, std::ref(files));
    commands["save"] = std::bind(artemev::save_text, _1, std::ref(files));
    commands["createCode"] = std::bind(artemev::createCode, _1, std::ref(codes), std::cref(files), std::ref(freq), std::ref(queue));
    commands["print"] = std::bind(artemev::print, _1, std::ref(std::cout), std::cref(files), std::cref(codes));
    commands["encode"] = std::bind(artemev::encode, _1, std::ref(codes), std::cref(files), std::ref(codeText));
    commands["write"] = std::bind(artemev::write, _1, std::ref(codeText), std::ref(codes), std::ref(files), std::ref(freq), std::ref(queue));
  }

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
      std::cout << e.what() << "\n";
    }
    catch (const std::exception &e)
    {
      std::cout << "<ERROR: " << e.what() << ">\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  return 0;
}
