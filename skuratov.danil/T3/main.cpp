#include <iostream>
#include <limits>
#include <functional>
#include <map>

namespace skuratov
{
  void cmd1(const int&, std::istream& in, std::ostream& out)
  {
    out << "Hi, this is CMD1" << '\n';
  }
  void cmd2(const int&, std::istream& in, std::ostream& out)
  {
    out << "Hi, this is CMD2" << '\n';
  }
  void cmd3(int&, std::istream& in, std::ostream& out)
  {
    out << "Hi, this is CMD3" << '\n';
  }
  void cmd4(std::istream& in, std::ostream& out)
  {
    out << "Hi, this is CMD4" << '\n';
    throw std::overflow_error{ "Overflow cmd4" };
  }
}

int main()
{
  int context = {};
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["CMD1"] = std::bind(skuratov::cmd1, context, _1, _2);
    cmds["CMD2"] = std::bind(skuratov::cmd2, context, _1, _2);
    cmds["CMD3"] = std::bind(skuratov::cmd3, context, _1, _2);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::overflow_error& e)
    {
      std::cerr << "<ERROR: " << e.what() << ">\n";
    }
    catch (const std::out_of_range&)
    {
      std::cerr << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
