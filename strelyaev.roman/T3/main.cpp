#include <fstream>
#include <vector>
#include <limits>
#include <iterator>
#include <string>
#include <functional>
#include <iostream>
#include "polygon.hpp"
#include "commands.hpp"

int main(int argc, char **argv)
{
  using namespace strelyaev;
  if (argc < 2)
  {
    std::cerr << "<NOT ENOUGH ARGUMENTS>\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    return 1;
  }
   std::vector< Polygon > polygons;

  using input_it_t = std::istream_iterator< Polygon >;
  while (!file.eof())
  {
    std::copy(input_it_t{ file }, input_it_t{}, std::back_inserter(polygons));
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  file.close();

  std::map<std::string, std::function<bool(const Polygon &)>> args;
  {
    using namespace std::placeholders;
    args["EVEN"] = std::bind(std::equal_to<double>{}, std::bind(std::modulus<size_t>{}, std::bind(size_getter, _1), 2), 0);
    args["ODD"] = std::bind(std::not_equal_to<double>{}, std::bind(std::modulus<size_t>{}, std::bind(size_getter, _1), 2), 0);
    args["MEAN"] = std::bind(std::equal_to<int>{}, 1, 1);
  }

  std::map<std::string, std::function<bool(const Polygon &)>> args_count;
  args_count["EVEN"] = args["EVEN"];
  args_count["ODD"] = args["ODD"];

  std::map<std::string, std::function<void(std::ostream &, std::istream &, const std::vector<Polygon> &)>> cmds;
  {
    using namespace std::placeholders;
    cmds["COUNT"] = std::bind(count_cmd, _1, _2, _3, args_count);
    cmds["AREA"] = std::bind(area_cmd, _1, _2, _3, args);
    cmds["MAX"] = std::bind(max_cmd, _1, _2, _3);
    cmds["MIN"] = std::bind(min_cmd, _1, _2, _3);
    cmds["PERMS"] = std::bind(perms_cmd, _1, _2, _3);
    cmds["MAXSEQ"] = std::bind(maxseq_cmd, _1, _2, _3);
  }
  std::string cmd_name = "";
  while (std::cin >> cmd_name)
  {
    try
    {
      cmds.at(cmd_name)(std::cout, std::cin, polygons);
      std::cout << "\n";
    }
    catch (const std::exception &e)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return 0;
}
