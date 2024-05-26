#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iosfwd>
#include <map>
#include <set>
#include <string>

namespace demidenko
{
  class Dictionary;
  class Record
  {
    friend class Dictionary;

  public:
    Record(std::string&& word, std::set< std::string >&& translations);

  private:
    std::string word_;
    std::set< std::string > translations_;
  };

  class Dictionary
  {
  public:
    Dictionary();
    bool addRecord(Record&& record);
    bool removeRecord(Record&& record);
    friend std::istream& operator>>(std::istream& in, Dictionary& dictionary);

  private:
    std::map< std::string, std::set< std::string > > tree_;
  };
  std::istream& operator>>(std::istream& in, Dictionary& dictionary);
}

#endif
