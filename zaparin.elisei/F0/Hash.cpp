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

size_t zaparin::HashTable::hashFunc(const std::string& word)
{
  size_t hash = 0;

  for (size_t i = 0; i < word.size(); i++)
  {
    hash += static_cast< size_t > (word[i]) * (i + 1) + static_cast<size_t> (word[i]);
  }

  return (hash % maxSize_);
}

bool zaparin::HashTable::insert(const std::string& word, size_t numOfWords)
{
  if (!table_)
  {
    table_ = new std::list< Node >[maxSize_];
  }

  if (size_ >= maxSize_ * rehashSize_)
  {
    size_t past_maxSize = maxSize_;

    maxSize_ *= 2;
    std::list< Node >* newTable = new std::list< Node >[maxSize_];

    for (size_t i = 0; i < past_maxSize; i++)
    {
      newTable[i] = table_[i];
    }

    std::swap(table_, newTable);

    delete[] newTable;
  }

  return insert(filter(word), numOfWords);
}

bool zaparin::HashTable::insert(std::string&& word, size_t numOfWords)
{
  if (word == "")
  {
    return 0;
  }

  size_t hash = hashFunc(word);
  std::list< Node >* tempList = &table_[hash];

  if (tempList->empty())
  {
    tempList->push_back(Node(word));
    allWords_ += numOfWords;
    size_++;
    return 1;
  }
  else
  {
    std::list< Node >::iterator iter_begin = tempList->begin();
    std::list< Node >::iterator iter_end = tempList->end();

    while (iter_begin != iter_end)
    {
      if (word == iter_begin->word_)
      {
        iter_begin->numOfWords_ += numOfWords;
        allWords_ += numOfWords;
        return 1;
      }
      iter_begin++;
    }

    tempList->push_back(Node(word));
    allWords_ += numOfWords;
    return 1;
  }
}

bool zaparin::HashTable::removeWord(const std::string& word)
{
  if (!table_)
  {
    std::cout << "Table is empty\n";
  }

  size_t hash = hashFunc(word);

  std::list< Node >::iterator iter_begin = table_[hash].begin();
  std::list< Node >::iterator iter_end = table_[hash].end();

  while (iter_begin != iter_end)
  {
    if (word == iter_begin->word_)
    {
      iter_begin->numOfWords_--;
      return 1;
    }
    iter_begin++;
  }

  std::cout << "No word in table\n";
  return 0;
}

bool zaparin::HashTable::deleteWord(const std::string& word)
{
  if (!table_)
  {
    std::cout << "Table is empty\n";
  }

  size_t hash = hashFunc(word);

  std::list< Node >::iterator iter_begin = table_[hash].begin();
  std::list< Node >::iterator iter_end = table_[hash].end();

  while (iter_begin != iter_end)
  {
    if (word == iter_begin->word_)
    {
      table_[hash].erase(iter_begin);
      return 1;
    }
    iter_begin++;
  }

  std::cout << "No word in table\n";
  return 0;
}

double zaparin::HashTable::getWordRate(const std::string& word)
{
  if (!table_)
  {
    std::cout << "Table is empty\n";
  }

  size_t hash = hashFunc(word);

  std::list< Node >::iterator iter_begin = table_[hash].begin();
  std::list< Node >::iterator iter_end = table_[hash].end();

  while (iter_begin != iter_end)
  {
    if (word == iter_begin->word_)
    {
      return ((double)(iter_begin->numOfWords_) / allWords_);
    }
    iter_begin++;
  }

  return -1.0;
}

std::string zaparin::HashTable::getHighestRateWord()
{
  if (!table_)
  {
    std::cout << "Table is empty\n";
  }

  size_t rate = 0;
  size_t highestRate = 0;
  std::string highestRateWord = "";

  for (size_t i = 0; i < maxSize_; i++)
  {
    std::list< Node >::iterator iter_begin = table_[i].begin();
    std::list< Node >::iterator iter_end = table_[i].end();

    while (iter_begin != iter_end)
    {
      rate = iter_begin->numOfWords_;
      if (rate > highestRate)
      {
        highestRate = rate;
        highestRateWord = iter_begin->word_;
      }
      iter_begin++;
    }
  }

  return highestRateWord;
}

std::string zaparin::HashTable::getLowestRateWord()
{
  if (!table_)
  {
    std::cout << "Table is empty\n";
  }

  size_t rate = 0;
  size_t lowestRate = allWords_ + 1;
  std::string lowestRateWord = "";

  for (size_t i = 0; i < maxSize_; i++)
  {
    std::list< Node >::iterator iter_begin = table_[i].begin();
    std::list< Node >::iterator iter_end = table_[i].end();

    while (iter_begin != iter_end)
    {
      rate = iter_begin->numOfWords_;
      if (rate < lowestRate)
      {
        lowestRate = rate;
        lowestRateWord = iter_begin->word_;
      }
      iter_begin++;
    }
  }

  return lowestRateWord;
}

bool::zaparin::HashTable::getThreeHighestRateWords()
{
  if (!table_)
  {
    std::cout << "Table is empty\n";
  }

  size_t rate = 0;
  size_t highestRate = 0;
  std::queue< std::string > words;

  for (size_t i = 0; i < maxSize_; i++)
  {
    std::list< Node >::iterator iter_begin = table_[i].begin();
    std::list< Node >::iterator iter_end = table_[i].end();

    while (iter_begin != iter_end)
    {
      rate = iter_begin->numOfWords_;
      if (rate >= highestRate)
      {
        highestRate = rate;
        words.push(iter_begin->word_);
      }
      if (words.size() > 3)
      {
        words.pop();
      }
      iter_begin++;
    }
  }

  for (; !words.empty(); words.pop())
  {
    std::cout << words.front() << " ";
  }
  std::cout << "\n";

  return 1;
}

bool zaparin::HashTable::getWordsWithRate(double leftBorder, double rightBorder)
{
  if (!table_)
  {
    std::cout << "Table is empty\n";
    return 0;
  }

  double rate = 0.0;

  for (size_t i = 0; i < maxSize_; i++)
  {
    std::list< Node >::iterator iter_begin = table_[i].begin();
    std::list< Node >::iterator iter_end = table_[i].end();

    while (iter_begin != iter_end)
    {
      rate = (double)(iter_begin->numOfWords_) / allWords_;
      if (rate >= leftBorder && rate <= rightBorder)
      {
        std::cout << iter_begin->word_ << "\n";
      }
      iter_begin++;
    }
  }

  return 1;
}

bool zaparin::HashTable::mergeDicts(const HashTable& dict1, const HashTable& dict2)
{
  std::list< Node >::iterator iter_begin, iter_end;
  std::string word;

  if (dict1.table_)
  {
    for (size_t i = 0; i < dict1.maxSize_; i++)
    {
      iter_begin = dict1.table_[i].begin();
      iter_end = dict1.table_[i].end();

      while (iter_begin != iter_end)
      {
        word = iter_begin->word_;
        insert(word, iter_begin->numOfWords_);
        iter_begin++;
      }
    }
  }

  if (dict2.table_)
  {
    for (size_t i = 0; i < dict2.maxSize_; i++)
    {
      iter_begin = dict2.table_[i].begin();
      iter_end = dict2.table_[i].end();

      while (iter_begin != iter_end)
      {
        word = iter_begin->word_;
        insert(word, iter_begin->numOfWords_);
        iter_begin++;
      }
    }
  }

  return 1;
}

bool zaparin::HashTable::print(std::ostream& out)
{
  if (!table_)
  {
    std::cout << "Table is empty\n";
  }

  std::list< Node >::iterator iter_begin, iter_end;

  for (size_t i = 0; i < maxSize_; i++)
  {
    iter_begin = table_[i].begin();
    iter_end = table_[i].end();

    out << i << ": ";
    while (iter_begin != iter_end)
    {
      out << iter_begin->numOfWords_ << " " << iter_begin->word_ << ", ";
      iter_begin++;
    }
    out << "\n";
  }

  return 1;
}
