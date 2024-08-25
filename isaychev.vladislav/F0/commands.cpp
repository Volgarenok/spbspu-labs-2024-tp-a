#include "commands.hpp"
#include <istream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>

void isaychev::make_freqlist(std::istream & in, std::map< std::string, FreqList > & col)
{
  std::string str;
  in >> str;
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

void isaychev::delete_freqlist(std::istream & in, std::map< std::string, FreqList > & col)
{
  std::string str;
  in >> str;
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

std::string convert_to_str(const std::pair< isaychev::Word, size_t > & rhs)
{
  return rhs.first.content + " " + std::to_string(rhs.second);
}

void isaychev::print(std::istream & in, std::ostream & out, std::map< std::string, FreqList > & col)
{
  std::string str;
  in >> str;
  auto res = col.find(str);
  if (res == col.end())
  {
    throw std::runtime_error("no list");
  }
  std::vector< std::string > temp((*res).second.list.size());
  std::transform((*res).second.list.begin(), (*res).second.list.end(), temp.begin(), convert_to_str);
  using output_iter_t = std::ostream_iterator< std::string >;
  std::copy_n(temp.begin(), temp.size(), output_iter_t{out, "\n"});
}

void isaychev::count(std::istream & in, std::ostream & out, std::map< std::string, FreqList > & col)
{
  std::string str;
  in >> str;
  const auto & fl = col.at(str);
  in >> str;
  out << fl.list.at({str}) << "\n";
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

void isaychev::get_total(std::istream & in, std::ostream & out, std::map< std::string, FreqList > & col)
{
  std::string str;
  in >> str;
  const auto & fl = col.at(str);
  std::vector< size_t > sums(fl.list.size());
  std::transform(fl.list.begin(), fl.list.end(), sums.begin(), WordCounter());
  out << sums.back() << "\n";
}
