#include <iostream>
#include <vector>
#include <map>

#include "CrossRefs.hpp"
#include "Commands.hpp"
#include "Utility.hpp"

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Filename argument missing\n";
    return 1;
  }
  if (argc == 3 && std::string(argv[2]) == "--help")
  {
    stepanchenko::helpCmd(std::cout);
  }
  std::ifstream fin(argv[1]);
  if (!fin.is_open())
  {
    std::cout << "File cannot be opened\n";
    return 2;
  }

  std::vector< stepanchenko::CrossRefs > cross_refs = stepanchenko::createCrossRefsFromFile(fin);

  using namespace std::placeholders;
  std::map< std::string, std::function< void(std::istream& in) > > cmd;
  cmd["CREATE"] = std::bind(stepanchenko::create_tableCmd, std::ref(cross_refs), _1);
  cmd["ADDTOTABLE"] = std::bind(stepanchenko::add_to_tableCmd, std::ref(cross_refs), _1);
  cmd["GETINTERSECTION"] = std::bind(stepanchenko::get_intersectionCmd, std::ref(cross_refs), _1);
  cmd["PRINTLINES"] = std::bind(stepanchenko::print_linesCmd, std::ref(cross_refs), _1, std::ref(std::cout));
  cmd["PRINT"] = std::bind(stepanchenko::printCmd, std::ref(cross_refs), _1, std::ref(std::cout));
  cmd["DELETELINES"] = std::bind(stepanchenko::delete_linesCmd, std::ref(cross_refs), _1);
  cmd["MOVEDOWN"] = std::bind(stepanchenko::move_lines_downCmd, std::ref(cross_refs), _1);
  cmd["GETSELECTION"] = std::bind(stepanchenko::get_intersectionCmd, std::ref(cross_refs), _1);
  cmd["VIEW"] = std::bind(stepanchenko::viewCmd, std::ref(cross_refs), std::ref(std::cout));
  cmd["SAVE"] = std::bind(stepanchenko::saveCmd, _1, std::ref(cross_refs));

  while (!std::cin.eof())
  {
    std::string command;
    if (std::cin >> command)
    {
      try
      {
        cmd.at(command)(std::cin);
        std::cout << '\n';
      }
      catch (const std::out_of_range&)
      {
        std::cout << "<INVALID COMMAND>" << '\n';
      }
      catch (const std::logic_error& e)
      {
        std::cout << e.what() << '\n';
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
     }
  }

  return 0;
}
