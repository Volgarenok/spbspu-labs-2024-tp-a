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
      out << "<INVALID COMMAND>\n";
    }
    else
    {
      try
      {
        if (!dicts.at(dict).insert(word, trans))
        {
          out << "<INVALID COMMAND>\n";
        }
      }
      catch (...)
      {
        out << "<INVALID COMMAND>\n";
      }
    }
  }

  void search(const std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out)
  {
    std::string dict;
    std::string word;
    in >> dict >> word;
    if (!isWord(word))
    {
      out << "<INVALID COMMAND>\n";
    }
    else
    {
      try
      {
        auto trans = dicts.at(dict).search(word);
        if (!trans)
        {
          out << "<INVALID COMMAND>\n";
        }
        else
        {
          std::copy((*trans).begin(), (*trans).end(), std::ostream_iterator<std::string>(out, " "));
          out << "\n";
        }
      }
      catch (...)
      {
        out << "<INVALID COMMAND>\n";
      }

    }
  }

  void remove(std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out)
  {
    std::string dict;
    std::string word;
    in >> dict >> word;
    if (!isWord(word))
    {
      out << "<INVALID COMMAND>\n";
    }
    else
    {
      try
      {
        if (!dicts.at(dict).remove(word))
        {
          out << "<INVALID COMMAND>\n";
        }
      }
      catch (...)
      {
        out << "<INVALID COMMAND>\n";
      }

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
      out << "<INVALID COMMAND>\n";
    }
    else
    {
      try
      {
        if (!dicts.at(dict).removetranslation(word, trans))
        {
          out << "<INVALID COMMAND>\n";
        }
      }
      catch (...)
      {
        out << "<INVALID COMMAND>\n";
      }
    }
  }

  void searchShort(const std::map< std::string, kozakova::ERDictionary >& dicts, std::istream& in, std::ostream& out)
  {
    std::string dict;
    std::string word;
    in >> dict >> word;
    if (!isWord(word))
    {
      out << "<INVALID COMMAND>\n";
    }
    else
    {
      try
      {
        out << dicts.at(dict).searchShort(word) << "\n";
      }
      catch (...)
      {
        out << "<INVALID COMMAND>\n";
      }
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
      out << "<INVALID COMMAND>\n";
    }
    else
    {
      try
      {
        auto inter = dicts.at(dict).searchSame(word1, word2);
        if (inter.size() == 0)
        {
          out << "<NOT THE SAME>\n";
        }
        else
        {
          std::copy(inter.begin(), inter.end(), std::ostream_iterator<std::string>(out, " "));
          out << "\n";
        }
      }
      catch (...)
      {
        out << "<INVALID COMMAND>\n";
      }
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
      out << "<INVALID COMMAND>\n";
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
      out << "<INVALID COMMAND>\n";
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
      if (inter.size() == 0)
      {
        out << "<INVALID COMMAND>\n";
      }
      else
      {
        dicts[name] = ERDictionary{ inter };
        out << "<INTERSECT SUCCESSFULLY>\n";
      }
    }
    catch (...)
    {
      out << "<INVALID COMMAND>\n";
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
