#include "commands.hpp"
#include <istream>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>
#include <fstream>

std::string read_specifier(std::istream & in)
{
  std::string str;
  in >> str;
  return str;
}

void isaychev::make_freqlist(collection_t & col, std::istream & in)
{
  std::string str = std::move(read_specifier(in));
  std::ifstream file(str);
  if (!file.is_open())
  {
    throw std::runtime_error("<INVALID_COMMAND>");
  }
  in >> str;
  if (str.empty() || col.find(str) != col.end())
  {
    throw std::runtime_error("<INVALID_COMMAND>");
  }

  FreqList l;
  Word w;
  while (!(file >> w).eof())
  {
    if (file.fail())
    {
      file.clear();
      continue;
    }
    l.insert(w);
  }

  if (l.empty())
  {
    std::runtime_error("<EMPTY>");
  }
  col[str] = l;
}

void isaychev::delete_freqlist(collection_t & col, std::istream & in)
{
  std::string str = std::move(read_specifier(in));
  if (str.empty())
  {
    throw std::runtime_error("<INVALID_COMMAND>");
  }
  size_t res = col.erase(str);
  if (!res)
  {
    throw std::runtime_error("<INVALID_COMMAND>");
  }
}

void isaychev::print(const collection_t & col, std::istream & in, std::ostream & out)
{
  const auto & res = col.at(read_specifier(in));
  std::vector< std::pair< Word, size_t > > temp(res.get_map().begin(), res.get_map().end());
  std::sort(temp.begin(), temp.end(), is_greater);
  using output_iter_t = std::ostream_iterator< std::string >;
  std::transform(temp.begin(), temp.end(), output_iter_t{out, "\n"}, convert_to_str);
}

void isaychev::count(const collection_t & col, std::istream & in, std::ostream & out)
{
  const auto & fl = col.at(read_specifier(in));
  out << fl.at({read_specifier(in)}) << "\n";
}

void isaychev::get_total(const collection_t & col, std::istream & in, std::ostream & out)
{
  const auto & fl = col.at(read_specifier(in));
  std::vector< size_t > sums(fl.size());
  std::transform(fl.get_map().begin(), fl.get_map().end(), sums.begin(), WordCounter());
  out << sums.back() << "\n";
}

void isaychev::get_unique(const collection_t & col, std::istream & in, std::ostream & out)
{
  const auto & fl = col.at(read_specifier(in));
  out << fl.size() << "\n";
}

void isaychev::print_extremes(const collection_t & col, const std::string & spec, std::istream & in, std::ostream & out)
{
  std::string str = std::move(read_specifier(in));
  size_t num = 0;
  in >> num;
  if (!in)
  {
    throw std::runtime_error("<INVALID_COMMAND>");
  }
  const auto & fl = col.at(str);
  if (num > fl.size())
  {
    num = fl.size();
  }
  std::vector< std::pair< Word, size_t > > temp(fl.get_map().begin(), fl.get_map().end());
  std::sort(temp.begin(), temp.end(), is_greater);
  using output_iter_t = std::ostream_iterator< std::string >;
  if (spec == "printfirst")
  {
    std::transform(temp.begin(), temp.begin() + num, output_iter_t{out, "\n"}, convert_to_str);
  }
  else if (spec == "printlast")
  {
    std::transform(temp.rbegin(), temp.rbegin() + num, output_iter_t{out, "\n"}, convert_to_str);
  }
}

isaychev::value_t merge_elems(const std::map< isaychev::Word, size_t > & col, const isaychev::value_t & rhs)
{
  auto it = col.find(rhs.first);
  if (it == col.end())
  {
    return rhs;
  }
  return {rhs.first, col.at(rhs.first) + rhs.second};
}

bool is_in(const std::map< isaychev::Word, size_t > & col, const std::pair< isaychev::Word, size_t > & rhs)
{
  return col.find(rhs.first) != col.end();
}

void isaychev::merge(collection_t & col, std::istream & in)
{
  std::string list, list2, new_list;
  in >> new_list >> list >> list2;
  if (new_list.empty())
  {
    throw std::runtime_error("<INVALID_COMMAND>");
  }
  const auto & fl1 = col.at(list);
  const auto & fl2 = col.at(list2);
  std::vector< std::pair< Word, size_t > > temp;
  using namespace std::placeholders;
  std::map< Word, size_t > temp2;
  auto functor = std::bind(merge_elems, std::cref(fl1.get_map()), _1);
  std::transform(fl2.get_map().begin(), fl2.get_map().end(), std::inserter(temp2, temp2.end()), functor);
  auto pred = std::bind(std::logical_not< bool >{}, std::bind(is_in, std::cref(fl1.get_map()), _1));
  std::copy_if(temp.begin(), temp.end(), std::back_inserter(temp), pred);
  col[new_list] = {std::move(temp2)};
}

const std::string & get_name(const std::pair< std::string, isaychev::FreqList > & rhs)
{
  return rhs.first;
}

void isaychev::get_names(const collection_t & col, std::ostream & out)
{
  if (!col.empty())
  {
    std::vector< std::string > temp(col.size());
    using output_iter_t = std::ostream_iterator< std::string >;
    std::transform(col.begin(), col.end(), temp.begin(), get_name);
    std::copy_n(temp.begin(), temp.size() - 1, output_iter_t{out, " "});
    out << temp.back() << "\n";
  }
}

isaychev::value_t intersect_elems(const std::map< isaychev::Word, size_t > & col, const isaychev::value_t & rhs)
{
  return {rhs.first, std::min(col.at(rhs.first), rhs.second)};
}

void isaychev::intersect(collection_t & col, std::istream & in)
{
  std::string list, list2, new_list;
  in >> new_list >> list >> list2;
  if (new_list.empty())
  {
    throw std::runtime_error("<INVALID_COMMAND>");
  }
  const auto & fl1 = col.at(list);
  const auto & fl2 = col.at(list2);
  std::vector< std::pair< Word, size_t > > temp;
  using namespace std::placeholders;
  auto pred = std::bind(is_in, std::cref(fl1.get_map()), _1);
  std::copy_if(fl2.get_map().begin(), fl2.get_map().end(), std::back_inserter(temp), pred);
  std::map< Word, size_t > temp2;
  auto functor = std::bind(intersect_elems, std::cref(fl1.get_map()), _1);
  std::transform(temp.begin(), temp.end(), std::inserter(temp2, temp2.end()), functor);
  col[new_list] = {std::move(temp2)};
}

void isaychev::execlude(collection_t & col, cmp_t cmp, std::istream & in)
{
  using namespace std::placeholders;
  std::string new_list, list;
  size_t total = 0;
  in >> new_list >> list >> total;
  if (!in)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  const auto & fl = col.at(list);
  std::map< Word, size_t > temp;
  std::pair< Word, size_t > value_cmp{{}, total};
  auto pred = std::bind(*cmp, std::cref(value_cmp), _1);
  std::copy_if(fl.get_map().begin(), fl.get_map().end(), std::inserter(temp, temp.end()), pred);
  if (temp.empty())
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  col[new_list] = {std::move(temp)};
}
