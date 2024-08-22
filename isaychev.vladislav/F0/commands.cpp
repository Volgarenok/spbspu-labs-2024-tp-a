#include "commands.hpp"
#include <istream>
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
    l.insert(w);
    if (file.eof())
    {
      break;
    }
    if (file.fail())
    {
      file.clear();
    }
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
