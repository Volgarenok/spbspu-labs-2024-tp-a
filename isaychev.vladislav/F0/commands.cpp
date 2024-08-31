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
  while (file)
  {
    file >> w;
    if (file.eof())
    {
      break;
    }
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
  out << res;
}

void isaychev::count(const collection_t & col, std::istream & in, std::ostream & out)
{
  const auto & fl = col.at(read_specifier(in));
  out << fl.at({read_specifier(in)}) << "\n";
}

class WordCounter
{
 public:
  WordCounter():
   sum_(0)
  {}

  size_t operator()(const std::pair< isaychev::Word, size_t > & rhs)
  {
    sum_ += rhs.second;
    return sum_;
  }

 private:
  size_t sum_;
};

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
  std::vector< std::pair< Word, size_t > > temp(num);
  if (spec == "printfirstnpos")
  {
    std::copy_n(fl.get_map().begin(), temp.size(), temp.begin());
  }
  else if (spec == "printlastnpos")
  {
    std::copy_n(fl.get_map().rbegin(), temp.size(), temp.begin());
  }
  using output_iter_t = std::ostream_iterator< std::string >;
  std::transform(temp.begin(), temp.end(), output_iter_t{out, "\n"}, convert_to_str);
}

void isaychev::merge(collection_t & col, std::istream & in)
{
  std::string list, list2, new_list;
  in >> new_list >> list >> list2;
  const auto & fl1 = col.at(list);
  const auto & fl2 = col.at(list2);
  FreqList temp = fl1;
  using namespace std::placeholders;
  auto func = std::bind(&FreqList::add_element, &temp, _1);
  std::for_each(fl2.get_map().begin(), fl2.get_map().end(), func);
  col.insert({new_list, temp});
}

bool is_greater(const std::pair< isaychev::Word, size_t > & lhs, const std::pair< isaychev::Word, size_t > & rhs)
{
  return lhs.second > rhs.second;
}

void isaychev::print_descending(const collection_t & col, std::istream & in, std::ostream & out)
{
  const auto & fl = col.at(read_specifier(in));
  std::vector< std::pair< Word, size_t > > temp(fl.get_map().begin(), fl.get_map().end());
  std::sort(temp.begin(), temp.end(), is_greater);
  using output_iter_t = std::ostream_iterator< std::string >;
  std::transform(temp.begin(), temp.end(), output_iter_t{out, "\n"}, convert_to_str);
}

const std::string & get_name(const std::pair< std::string, isaychev::FreqList > & rhs)
{
  return rhs.first;
}

void isaychev::get_names(const collection_t & col, std::istream & in, std::ostream & out)
{
  std::vector< std::string > temp(col.size());
  using output_iter_t = std::ostream_iterator< std::string >;
  std::transform(col.begin(), col.end(), temp.begin(), get_name);
  std::copy_n(temp.begin(), temp.size() - 1, output_iter_t{out, " "});
  out << temp.back() << "\n";
}
