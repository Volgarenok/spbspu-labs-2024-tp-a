#include "non_interactive_cmd.hpp"
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

void isaychev::load_saved(std::map< std::string, FreqList > & col)
{
  std::fstream in("saved");
  if (!in.is_open())
  {
    throw std::runtime_error("bad file");
  }
  size_t count = 0;
  in >> count;
  auto generator = std::bind(read_list, std::ref(in));
  std::generate_n(std::inserter(col, col.end()), count, generator);
}

void output_name_and_content(std::ostream & out, const std::pair< std::string, isaychev::FreqList> & rhs)
{
  out << rhs.first << ' ' << rhs.second.size() << '\n';
  out << rhs.second;
}

void isaychev::save(const collection_t & col)
{
  using namespace std::placeholders;
  std::ofstream file("saved");
  file << col.size() << "\n";
  auto functor = std::bind(output_name_and_content, std::ref(file), _1);
  std::for_each(col.begin(), col.end(), functor);
}
