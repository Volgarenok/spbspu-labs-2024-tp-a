#include "Commands.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>
#include "Dictionary.hpp"
#include "Utilites.hpp"

namespace
{
  struct isName
  {
    bool operator()(const erfurt::Dictionary & dictionary, const std::string & name)
    {
      return dictionary.getName() == name;
    }
  };
}

namespace erfurt
{
  using namespace std::placeholders;

  void makeInsert(std::istream & in, std::vector< Dictionary > & dictionaries)
  {
    setlocale(LC_ALL, "RU");
    std::string name;
    in >> name;
    auto iter = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), _1, name));
    if (iter != dictionaries.end())
    {
      std::string word;
      std::string translate;
      in >> word >> translate;
      iter->insert(word, translate);
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void makeFindTranslate(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out)
  {
    std::string name;
    in >> name;
    auto iter = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), _1, name));
    if (iter != dictionaries.end())
    {
      std::string word;
      in >> word;
      iter->printTranslate(out, word);
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void makeDelete(std::istream & in, std::vector< Dictionary > & dictionaries)
  {
    std::string name;
    in >> name;
    auto iter = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), _1, name));
    if (iter != dictionaries.end())
    {
      std::string word;
      in >> word;
      if (!iter->deleteWord(word))
      {
        throw std::logic_error("INVALID COMMAND");
      }
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void makePrint(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out)
  {
    std::string name;
    in >> name;
    auto iter = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), _1, name));
    if (iter != dictionaries.end())
    {
      for (const auto & it : *iter)
      {
        out << it.first << " - ";
        std::copy(it.second.cbegin(), it.second.cend(), std::ostream_iterator< std::string >{out, " "});
        out << '\n';
      }
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void makeIsTranslate(std::istream & in, std::vector< Dictionary > & dictionaries, std::ostream & out)
  {
    std::string name;
    in >> name;
    auto iter = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), _1, name));
    if (iter != dictionaries.end())
    {
      auto iterator = iter->cbegin();
      std::string word;
      while (iterator != iter->cend())
      {
        out << (*iterator).first << '\n';
        in >> word;
        if (word == "end")
        {
          out << '\n';
          break;
        }
        if (std::find(iterator->second.cbegin(), iterator->second.cend(), word) != iterator->second.cend())
        {
          out << "YES\n";
        }
        else
        {
          out << "NO\n";
        }
        iterator++;
      }
    }
  }

  void makeMerge(std::istream & in, std::vector< Dictionary > & dictionaries)
  {
    std::string name1;
    std::string name2;
    in >> name1 >> name2;
    auto iter1 = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), _1, name1));
    auto iter2 = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), _1, name2));
    if (iter1 != dictionaries.end() && iter2 != dictionaries.end() && iter1 != iter2)
    {
      auto pair1 = iter1->begin();
      auto pair2 = iter2->begin();
      while (pair1 != iter1->cend() && pair2 != iter2->cend())
      {
        if (pair1->first > pair2->first)
        {
          iter1->insert({ pair2->first, pair2->second });
          pair2++;
        }
        else if (pair1->first < pair2->first)
        {
          pair1++;
        }
        else
        {
          std::set_intersection(pair1->second.cbegin(), pair1->second.cend(), pair2->second.cbegin(), pair2->second.cend(),
            std::inserter((*iter1)[pair1->first], (*iter1)[pair1->first].begin()));
          pair1++;
          pair2++;
        }
      }
      while (pair2 != iter2->end())
      {
        iter1->insert({ pair2->first, pair2->second });
        pair2++;
      }
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void makeCommon(std::istream & in, std::vector< Dictionary > & dictionaries)
  {
    std::string name;
    std::string name1;
    std::string name2;
    in >> name >> name1 >> name2;
    auto iter1 = std::find_if(dictionaries.cbegin(), dictionaries.cend(), std::bind(isName(), _1, name1));
    auto iter2 = std::find_if(dictionaries.cbegin(), dictionaries.cend(), std::bind(isName(), _1, name2));
    if (iter1 != dictionaries.cend() && iter2 != dictionaries.cend() && iter1 != iter2)
    {
      Dictionary result = createCommonDictionary(*iter1, *iter2, name);
      dictionaries.push_back(std::move(result));
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void makeUnique(std::istream & in, std::vector< Dictionary > & dictionaries)
  {
    std::string name;
    std::string name1;
    std::string name2;
    in >> name >> name1 >> name2;
    auto iter1 = std::find_if(dictionaries.cbegin(), dictionaries.cend(), std::bind(isName(), _1, name1));
    auto iter2 = std::find_if(dictionaries.cbegin(), dictionaries.cend(), std::bind(isName(), _1, name2));
    if (iter1 != dictionaries.cend() && iter2 != dictionaries.cend() && iter1 != iter2)
    {
      Dictionary result = createUniqueDictionary(*iter1, *iter2, name);
      dictionaries.push_back(std::move(result));
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void makeAddTranslate(std::istream & in, std::vector< Dictionary > & dictionaries)
  {
    std::string name1;
    std::string name2;
    std::string word;
    in >> name1 >> name2 >> word;
    auto iter1 = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), _1, name1));
    auto iter2 = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), _1, name2));
    {
      if (iter1 != dictionaries.end() && iter2 != dictionaries.end() && iter1 != iter2)
      {
        auto it1 = iter1->search(word);
        auto it2 = iter2->search(word);
        if (it1 != iter1->end() && it2 != iter2->end())
        {
          for (const auto & translate : it2->second)
          {
            if (it1->second.find(translate) == it1->second.cend())
            {
              iter1->insert(it2->first, translate);
            }
          }
        }
        else
        {
          throw std::logic_error("INVALID COMMAND");
        }
      }
      else
      {
        throw std::logic_error("INVALID COMMAND");
      }
    }
  }

  void makeHelp(std::ostream & out)
  {
    out << "--INSERT <dictionary> <word> <translate>\n";
    out << "\tInserts a pair - a word and a translation into the selected dictionary\n\n";
    out << "--FINDTRANSLATE <dictionary> <word>\n";
    out << "\tPrint the translation of a word from the selected dictionary\n\n";
    out << "--DELETE <dictionary> <word>\n";
    out << "\tRemoves a word from the selected dictionary\n\n";
    out << "--ADDTRANSLATE <dictionary1> <dictionary2> <word>\n";
    out << "\tAdd a translation of a word from one dictionary to another\n\n";
    out << "--PRINTDICTIONARIES\n";
    out << "\tPrints the names of available dictionaries\n\n";
    out << "--ISTRANSLATE <dictionary>\n";
    out << "\tYou will need to write a translation of the word suggested by the program from the selected dictionary\n\n";
    out << "--MERGE <dictionary1> <dictionary2>\n";
    out << "\tWords from the second dictionary are added to the first dictionary\n\n";
    out << "--ADDCOMMON <new dictionary> <dictionary1> <dictionary2>\n";
    out << "\tCreating a dictionary with common words for two dictionaries\n\n";
    out << "--ADDUNIQUE <new Dictionary> <dictionary1> <dictionary2>\n";
    out << "\tCreating a dictionary with different words for two dictionaries\n\n";
    out << "--SAVE <dictionary> <file>\n";
    out << "\tSaves the selected dictionary to the end of the selected file\n\n";
    out << "--PRINT <dictionary>\n";
    out << "\tPrint the selected dictionary\n\n";
    out << "--CREATEDICTIONARY <dictionary>\n";
    out << "\tCreating a new dictionary\n";
  }

  void makePrintDictionaries(std::vector< Dictionary > & dictionaries, std::ostream & out)
  {
    std::transform(dictionaries.cbegin(), dictionaries.cend(), std::ostream_iterator<std::string>{out, " "},
      std::bind(& Dictionary::getName, std::placeholders::_1));
    out << '\n';
  }

  void makeSave(std::istream & in, std::vector< Dictionary > & dictionaries)
  {
    std::string name;
    std::string file;
    in >> name >> file;
    auto iter = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), _1, name));
    if (iter != dictionaries.end())
    {
      std::ofstream f(file);
      if (!f)
      {
        throw std::logic_error("INVALID COMMAND");
      }
      f << iter->getName();
      f << '\n';
      for (const auto & it : *iter)
      {
        f << it.first << " - ";
        for (const auto & ite : it.second)
        {
          f << ite << ' ';
        }
        f << '\n';
      }
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void makeOpen(std::istream & in, std::vector< Dictionary > & dictionaries)
  {
    std::string file;
    in >> file;
    std::ifstream fin(file);
    if (!fin)
    {
      throw std::logic_error("INVALID COMMAND");
    }
    while (!fin.eof())
    {
      Dictionary dictionary;
      fin >> dictionary;
      if (!dictionary.getName().empty())
      {
        dictionaries.push_back(std::move(dictionary));
      }
    }
  }

  void makeCreate(std::istream & in, std::vector< Dictionary > & dictionaries)
  {
    std::string name;
    in >> name;
    if (std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), _1, name)) == dictionaries.end())
    {
      Dictionary dict(name);
      dictionaries.push_back(std::move(dict));
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }
}
