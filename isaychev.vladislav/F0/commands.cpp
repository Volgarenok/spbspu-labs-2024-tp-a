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
    throw std::runtime_error("bad file");
  }
  if (col.find(str) != col.end())
  {
    throw std::runtime_error("list already exists");
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
    }
    l.insert(w);
  }

  if (l.list.empty())
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
    throw std::runtime_error("no name");
  }
  size_t res = col.erase(str);
  if (!res)
  {
    throw std::runtime_error("no list with such name");
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
  out << fl.list.at({read_specifier(in)}) << "\n";
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
  std::vector< size_t > sums(fl.list.size());
  std::transform(fl.list.begin(), fl.list.end(), sums.begin(), WordCounter());
  out << sums.back() << "\n";
}

void isaychev::get_unique(const collection_t & col, std::istream & in, std::ostream & out)
{
  const auto & fl = col.at(read_specifier(in));
  out << fl.list.size() << "\n";
}

void isaychev::print_extremes(const collection_t & col, const std::string & spec, std::istream & in, std::ostream & out)
{
  std::string str = std::move(read_specifier(in));
  size_t num = 0;
  in >> num;
  if (!in)
  {
    throw std::runtime_error("no number");
  }
  const auto & fl = col.at(str);
  if (num > fl.list.size())
  {
    num = fl.list.size();
  }
  std::vector< std::pair< Word, size_t > > temp(num);
  if (spec == "printfirstnpos")
  {
    std::copy_n(fl.list.begin(), temp.size(), temp.begin());
  }
  else if (spec == "printlastnpos")
  {
    std::copy_n(fl.list.rbegin(), temp.size(), temp.begin());
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
  FreqList temp;
  temp.list = fl1.list;
  using namespace std::placeholders;
  auto func = std::bind(&FreqList::add_element, &temp, _1);
  std::for_each(fl2.list.begin(), fl2.list.end(), func);
  col.insert({new_list, temp});
}

bool is_greater(const std::pair< isaychev::Word, size_t > & lhs, const std::pair< isaychev::Word, size_t > & rhs)
{
  return lhs.second > rhs.second;
}

void isaychev::print_descending(const collection_t & col, std::istream & in, std::ostream & out)
{
  const auto & fl = col.at(read_specifier(in));
  std::vector< std::pair< Word, size_t > > temp(fl.list.begin(), fl.list.end());
  std::sort(temp.begin(), temp.end(), is_greater);
  using output_iter_t = std::ostream_iterator< std::string >;
  std::transform(temp.begin(), temp.end(), output_iter_t{out, "\n"}, convert_to_str);
}
