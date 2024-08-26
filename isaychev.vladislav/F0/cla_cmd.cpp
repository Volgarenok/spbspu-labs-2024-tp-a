#include "cla_cmd.hpp"
#include <algorithm>
#include <ostream>
#include <fstream>

void isaychev::print_help(std::ostream & out)
{
  out << "command info coming soon";
}

void read_list(std::istream & in, isaychev::FreqList & list)
{
  std::string str;
  size_t num = 0;
  while (in >> num >> str)
  {
    list.add_element({{str}, num});
  }
}

void isaychev::load_saved(std::map< std::string, FreqList > & col, const std::string & file)
{
  std::fstream in(file);
  if (!in.is_open())
  {
    throw std::runtime_error("bad file");
  }
  std::string name;
  while (in >> name)
  {
    if (in.eof())
    {
      break;
    }
    read_list(in, col[name]);
    in.clear();
  }
}
