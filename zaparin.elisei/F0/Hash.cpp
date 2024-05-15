#include "Hash.hpp"
#include <functional>
#include <exception>
#include <algorithm>
#include <queue>
#include "delimeter.hpp"

zaparin::HashTable::HashTable()
{
  size_ = 0;
  allWords_ = 0;
  maxSize_ = defaultSize_;
  table_ = nullptr;
}

zaparin::HashTable::HashTable(size_t nol)
{
  size_ = 0;
  allWords_ = 0;
  maxSize_ = nol;
  table_ = new std::list< Node >[maxSize_];
}

zaparin::HashTable::HashTable(const HashTable& table)
{
  if (this != &table)
  {
    size_ = table.size_;
    allWords_ = table.allWords_;
    maxSize_ = table.maxSize_;

    table_ = new std::list< Node >[maxSize_];

    std::list< Node >::iterator iter_begin, iter_end;
    std::list< Node >* tempList;

    for (int i = 0; i < maxSize_; i++)
    {
      tempList = &table.table_[i];

      iter_begin = tempList->begin();
      iter_end = tempList->end();

      while (iter_begin != iter_end)
      {
        insert(iter_begin->word_);
        iter_begin++;
      }
    }
  }
}

zaparin::HashTable::HashTable(HashTable&& table)
{
  size_ = table.size_;
  allWords_ = table.allWords_;
  maxSize_ = table.maxSize_;
  table_ = table.table_;
}

zaparin::HashTable::~HashTable()
{
  delete[] table_;
}

zaparin::HashTable& zaparin::HashTable::operator=(const HashTable& table)
{
  if (this == &table)
  {
    return *this;
  }

  size_ = table.size_;
  allWords_ = table.allWords_;
  maxSize_ = table.maxSize_;

  table_ = new std::list< Node >[maxSize_];

  std::list< Node >::iterator iter_begin, iter_end;
  std::list< Node >* tempList;

  for (size_t i = 0; i < maxSize_; i++)
  {
    tempList = &table.table_[i];

    iter_begin = tempList->begin();
    iter_end = tempList->end();

    while (iter_begin != iter_end)
    {
      insert(iter_begin->word_);
      iter_begin++;
    }
  }

  return *this;
}

zaparin::HashTable& zaparin::HashTable::operator=(HashTable&& table)
{
  size_ = table.size_;
  allWords_ = table.allWords_;
  maxSize_ = table.maxSize_;
  table_ = table.table_;

  return *this;
}
