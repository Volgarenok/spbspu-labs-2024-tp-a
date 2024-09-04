#include "dictionary.hpp"

#include <stdexcept>

zagrivnyy::Dictionary::Dictionary():
  dict_()
{
}

void zagrivnyy::Dictionary::add(std::string word, Position pos)
{
  auto it = dict_.find(word);
  if (it != dict_.end())
  {
    it->second.push_back(pos);
  }
  else
  {
    std::vector< Position > positions = {pos};
    dict_.insert(std::make_pair(word, positions));
  }
}

void zagrivnyy::Dictionary::add(std::string word, std::vector< Position > positions)
{
  for (auto pos : positions)
  {
    add(word, pos);
  }
}

void zagrivnyy::Dictionary::remove(std::string word)
{
  dict_.erase(word);
}

void zagrivnyy::Dictionary::parse_table(std::vector< std::vector< std::string > > table)
{
  dict_.clear();
  for (long unsigned int row = 1; row <= table.size(); row++)
  {
    for (long unsigned int col = 1; col <= table[row - 1].size(); col++)
    {
      add(table[row - 1][col - 1], {row, col});
    }
  }
}

std::vector< std::vector< std::string > > zagrivnyy::Dictionary::generate_table() const
{
  std::vector< std::vector< std::string > > table;

  for (auto record : dict_)
  {
    for (auto pos : record.second)
    {
      if (table.size() < pos.row)
      {
        table.resize(pos.row);
      }
      if (table[pos.row - 1].size() < pos.col)
      {
        table[pos.row - 1].resize(pos.col);
      }

      table[pos.row - 1][pos.col - 1] = record.first;
    }
  }

  return table;
}

std::vector< zagrivnyy::Position > zagrivnyy::Dictionary::get(std::string word) const
{
  try
  {
    std::vector< Position > positions = dict_.at(word);
    return positions;
  }
  catch (const std::out_of_range &)
  {
    throw std::invalid_argument("warn: no such word in dictionary");
  }
}

std::ostream &zagrivnyy::operator<<(std::ostream &out, const Position &pos)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }

  out << '(' << pos.row << ';' << pos.col << ')';
  return out;
}
