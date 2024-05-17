#include "Commands.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <fstream>
#include "Dictionary.hpp"
#include "Utilites.hpp"

namespace
{
  struct isName
  {
    bool operator()(const erfurt::Dictionary& dictionary, const std::string& name)
    {
      return dictionary.getName() == name;
    }
  };
}

namespace erfurt
{
  using namespace std::placeholders;

  void makeInsert(std::istream& in, std::vector<Dictionary>& dictionaries, std::ostream& out)
  {
    setlocale(LC_ALL, "RU");
    std::string name;
    in >> name;
    auto iter = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), _1, name));
    if (iter != dictionaries.end())
    {
      std::string word;
      std::string translate;
      in >> word;
      std::getline(in, translate);
      iter->insert(word, translate);
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void makeFindTranslate(std::istream& in, std::vector<Dictionary>& dictionaries, std::ostream& out)
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

  void makeDelete(std::istream& in, std::vector<Dictionary>& dictionaries, std::ostream& out)
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

  void makePrint(std::istream& in, std::vector<Dictionary>& dictionaries, std::ostream& out)
  {
    std::string name;
    in >> name;
    auto iter = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), _1, name));
    if (iter != dictionaries.end())
    {
      for (const auto& it : *iter)
      {
        out << it.first << " - ";
        for (const auto& ite : *it.second)
        {
          out << ite << ' ';
        }
        out << '\n';
      }
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void makeIsTranslate(std::istream& in, std::vector<Dictionary>& dictionaries, std::ostream& out)
  {
    std::string name;
    in >> name;
    auto iter = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), _1, name));
    if (iter != dictionaries.end())
    {
      auto iterator = iter->begin();
      std::string word;
      while (iterator != iter->end())
      {
        out << (*iterator).first << '\n';
        in >> word;
        if (word == "end")
        {
          out << '\n';
          break;
        }
        if (std::find(iterator->second->begin(), iterator->second->end(), word) != iterator->second->end())
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

  void makeMerge(std::istream& in, std::vector<Dictionary>& dictionaries, std::ostream& out)
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
      while (pair1 != iter1->end() && pair2 != iter2->end())
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
          auto translate1 = *pair1->second;
          auto translate2 = *pair2->second;
          for (const auto& tr : translate2)
          {
            if (translate1.find(tr) == translate1.cend())
            {
              iter1->insert(pair1->first, tr);
            }
          }
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

  void makeCommon(std::istream& in, std::vector<Dictionary>& dictionaries, std::ostream& out)
  {
    std::string name1;
    std::string name2;
    in >> name1 >> name2;
    auto iter1 = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), _1, name1));
    auto iter2 = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), _1, name2));
    if (iter1 != dictionaries.end() && iter2 != dictionaries.end() && iter1 != iter2)
    {
      Dictionary result = createCommonDictionary(*iter1, *iter2);
      dictionaries.push_back(result);
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void makeUnique(std::istream& in, std::vector<Dictionary>& dictionaries, std::ostream& out)
  {
    std::string name1;
    std::string name2;
    in >> name1 >> name2;
    auto iter1 = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), _1, name1));
    auto iter2 = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), _1, name2));
    if (iter1 != dictionaries.end() && iter2 != dictionaries.end() && iter1 != iter2)
    {
      Dictionary result = createUniqueDictionary(*iter1, *iter2);
      dictionaries.push_back(result);
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void makeAddTranslate(std::istream& in, std::vector<Dictionary>& dictionaries, std::ostream& out)
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
          for (const auto& translate : *it2->second)
          {
            if (it1->second->find(translate) == it1->second->cend())
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

  void makeHelp(std::istream& in, std::vector<Dictionary>& dictionaries, std::ostream& out)
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
    out << "\tPrints the names of available dictionaries\n";
    out << "--ISTRANSLATE <dictionary>\n";
    out << "\tYou will need to write a translation of the word suggested by the program from the selected dictionary\n\n";
    out << "--MERGE <dictionary1> <dictionary2>\n";
    out << "\tWords from the second dictionary are added to the first dictionary\n\n";
    out << "--ADDCOMMON <dictionary1> <dictionary2>\n";
    out << "\tCreating a dictionary with common words for two dictionaries\n\n";
    out << "--ADDUNIQUE <dictionary1> <dictionary2>\n";
    out << "\tCreating a dictionary with different words for two dictionaries\n\n";
    out << "--SAVE <dictionary> <file>\n";
    out << "\tSaves the selected dictionary to the end of the selected file\n\n";
    out << "--PRINT <dictionary>\n";
    out << "\tPrint the selected dictionary\n";
  }

  void makePrintDictionaries(std::istream& in, std::vector<Dictionary>& dictionaries, std::ostream& out)
  {
    for (const auto& dict : dictionaries)
    {
      out << dict.getName() << " ";
    }
    out << '\n';
  }

  void makeSave(std::istream& in, std::vector<Dictionary>& dictionaries, std::ostream& out)
  {
    std::string name;
    std::string file;
    in >> name >> file;
    auto iter = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), _1, name));
    if (iter != dictionaries.end())
    {
      std::ofstream f(file, std::ios::binary | std::ios::app);
      if (!f)
      {
        throw std::logic_error("INVALID COMMAND");
      }
      f << iter->getName();
      f << '\n';
      for (const auto& it : *iter)
      {
        f << it.first << " - ";
        for (const auto& ite : *it.second)
        {
          f << ite << ' ';
        }
        f << '\n';
      }
      f << "END\n";
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }
}