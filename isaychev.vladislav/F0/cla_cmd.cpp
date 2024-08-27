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
  size_t elem_count = 0;
  in >> elem_count;
  std::string str;
  size_t num = 0;
  for (size_t i = 0; i < elem_count; ++i)
  {
    in >> num >> str;
    list.add_element({{str}, num});
  }
}

void isaychev::load_saved(const std::string & file, std::map< std::string, FreqList > & col)
{
  std::fstream in(file.substr(file.find_last_of('-') + 1));
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
  }
}
