#include "cla_cmd.hpp"
#include <algorithm>
#include <ostream>
#include <fstream>
#include <functional>

void isaychev::print_help(std::ostream & out)
{
  out << "command info coming soon";
}

isaychev::value_t read_value(std::istream & in)
{
  size_t n = 0;
  std::string str;
  in >> n >> str;
  return {{str}, n};
}

std::pair< std::string, isaychev::FreqList > read_list(std::istream & in)
{
  std::string name;
  size_t elem_count = 0;
  in >> name >> elem_count;
  std::map< isaychev::Word, size_t > temp;
  auto generator = std::bind(read_value, std::ref(in));
  std::generate_n(std::inserter(temp, temp.end()), elem_count, generator);
  return {name, isaychev::FreqList(std::move(temp))};
}

void isaychev::load_saved(const std::string & file, std::map< std::string, FreqList > & col)
{
  std::fstream in(file.substr(file.find_first_not_of('-')));
  if (!in.is_open())
  {
    throw std::runtime_error("bad file");
  }
  size_t count = 0;
  in >> count;
  auto generator = std::bind(read_list, std::ref(in));
  std::generate_n(std::inserter(col, col.end()), count, generator);
}
