#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <functional>
#include "ERDictionary.hpp"

namespace kozakova
{
  void insert(std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out)
  {
    std::string dict;
    std::string word;
    std::string trans;
    in >> dict >> word >> trans;
    if (!isWord(word) || !isTrans(trans))
    {
      throw std::logic_error("INVALID COMMAND");
    }
    try
    {
      if (!dicts.at(dict).insert(word, trans))
      {
        throw std::logic_error("INVALID COMMAND");
      }
    }
    catch (...)
    {
      throw std::logic_error("INVALID COMMAND");
    }

  }

  void search(const std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out)
  {
    std::string dict;
    std::string word;
    in >> dict >> word;
    if (!isWord(word))
    {
      throw std::logic_error("INVALID COMMAND");
    }
    try
    {
      auto trans = dicts.at(dict).search(word);
      if (!trans)
      {
        throw std::logic_error("INVALID COMMAND");
      }
      std::copy((*trans).begin(), (*trans).end(), std::ostream_iterator<std::string>(out, " "));
      out << "\n";
    }
    catch (...)
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void remove(std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out)
  {
    std::string dict;
    std::string word;
    in >> dict >> word;
    if (!isWord(word))
    {
      throw std::logic_error("INVALID COMMAND");
    }
    try
    {
      if (!dicts.at(dict).remove(word))
      {
        throw std::logic_error("INVALID COMMAND");
      }
    }
    catch (...)
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void removeTranslation(std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out)
  {
    std::string dict;
    std::string word;
    std::string trans;
    in >> dict >> word >> trans;
    if (!isWord(word) || !isTrans(trans))
    {
      throw std::logic_error("INVALID COMMAND");
    }
    try
    {
      if (!dicts.at(dict).removetranslation(word, trans))
      {
        throw std::logic_error("INVALID COMMAND");
      }
    }
    catch (...)
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void searchShort(const std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out)
  {
    std::string dict;
    std::string word;
    in >> dict >> word;
    if (!isWord(word))
    {
      throw std::logic_error("INVALID COMMAND");
    }
    try
    {
      out << dicts.at(dict).searchShort(word) << "\n";
    }
    catch (...)
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void searchSame(const std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out)
  {
    std::string dict;
    std::string word1;
    std::string word2;
    in >> dict >> word1 >> word2;
    if (!isWord(word1) || !isWord(word2))
    {
      throw std::logic_error("INVALID COMMAND");
    }
    try
    {
      auto inter = dicts.at(dict).searchSame(word1, word2);
      if (inter.size() == 0)
      {
        throw std::logic_error("INVALID COMMAND");
      }
      std::copy(inter.begin(), inter.end(), std::ostream_iterator<std::string>(out, " "));
      out << "\n";
    }
    catch (...)
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void identical(const std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out)
  {
    std::string dict1;
    std::string dict2;
    in >> dict1 >> dict2;
    try
    {
      if (dicts.at(dict1) == dicts.at(dict2))
      {
        out << "<YES>\n";
      }
      else
      {
        out << "<NO>\n";
      }
    }
    catch (...)
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void combine(std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out)
  {
    std::string dict1;
    std::string dict2;
    in >> dict1 >> dict2;
    try
    {
      dicts.at(dict1).dictionary.insert(dicts.at(dict2).dictionary.begin(), dicts.at(dict2).dictionary.end());
      dicts.at(dict1).combine(dicts.at(dict2));
      out << "<COMBINE SUCCESSFULLY>\n";
    }
    catch (...)
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void intersection(std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out)
  {
    std::string dict1;
    std::string dict2;
    std::string name;
    in >> dict1 >> dict2 >> name;
    try
    {
      std::unordered_map< std::string, std::set< std::string > > inter= intersect(dicts.at(dict1), dicts.at(dict2));
      if (inter.empty())
      {
        throw std::logic_error("INVALID COMMAND");
      }
      dicts[name] = ERDictionary{ inter };
      out << "<INTERSECT SUCCESSFULLY>\n";
    }
    catch (...)
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void save(const std::map< std::string, kozakova::ERDictionary >& dicts, const std::string& fname)
  {
    std::ofstream file(fname);
    file.clear();
    using namespace std::placeholders;
    std::for_each(dicts.begin(), dicts.end(), std::bind(kozakova::print, std::ref(file), _1));
    file.close();
  }
}
