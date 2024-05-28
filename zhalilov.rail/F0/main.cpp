#include <iostream>
#include <functional>
#include <limits>

#include "commands.hpp"

void clearStream(std::istream &in)
{
  in.clear();
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

int main()
{
  using namespace zhalilov;
  using varModule = std::map< std::string, std::list< InfixToken > >;
  using modulesMap = std::map< std::string, varModule >;
  modulesMap modules;

  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > commands;
  std::string history = "history";

  using namespace std::placeholders;
  commands["calc"] = std::bind(calc, std::cref(modules), std::cref(history), _1, _2);
  commands["modulesadd"] = std::bind(modulesadd, std::ref(modules), _1, _2);
  commands["modulesdelete"] = std::bind(modulesdelete, std::ref(modules), _1, _2);

  commands["modulesvaradd"] = std::bind(modulesvaradd, std::ref(modules), _1, _2);
  commands["modulesvardelete"] = std::bind(modulesvardelete, std::ref(modules), _1, _2);

  commands["modulesshow"] = std::bind(modulesshow, std::cref(modules), _1, _2);

  commands["modulesimport"] = std::bind(modulesimport, std::ref(modules), _1, _2);
  commands["modulesexport"] = std::bind(modulesexport, std::ref(modules), _1, _2);

  commands["historyshow"] = std::bind(historyshow, std::cref(history), _1, _2);
  commands["historyclear"] = std::bind(historyclear, std::cref(history), _1, _2);

  modules.insert(std::make_pair("main", varModule{}));

  while (!std::cin.eof())
  {
    std::string command;
    std::cin >> command;
    try
    {
      commands.at(command)(std::cin, std::cout);
    }
    catch (const std::out_of_range &e)
    {
      std::cerr << "command doesn't exist\n";
      clearStream(std::cin);
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
      clearStream(std::cin);
    }
  }
}
