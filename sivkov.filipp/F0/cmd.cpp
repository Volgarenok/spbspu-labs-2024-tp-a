#include "cmd.hpp"
#include <vector>
#include <iostream>
#include <fstream>

namespace sivkov
{
  using map = std::map< std::string, std::map< std::string, std::string > >;
  void add_word(map & treeOfdic, std::istream& in)
  {
    std::string dictionaryName = "";
    std::string englishWord = "";
    if (!(in >> dictionaryName >> englishWord))
    {
      throw std::logic_error("Invalid arguments");
    }

    if (treeOfdic.find(dictionaryName) == treeOfdic.end())
    {
      throw std::logic_error("Dictionary not found");
    }

    std::map< std::string, std::string >& dictionary = treeOfdic[dictionaryName];

    if (dictionary.find(englishWord) == dictionary.end())
    {
      dictionary[englishWord] = "";
    }
  }

  void add_translation(map& treeOfdic, std::istream& in)
  {
    std::string dictionaryName = "";
    std::string englishWord = "";
    std::string russianWord = "";
    if (!(in >> dictionaryName >> englishWord >> russianWord))
    {
      throw std::logic_error("Invalid arguments");
    }

    if (treeOfdic.find(dictionaryName) == treeOfdic.end())
    {
      throw std::logic_error("Dictionary not found");
    }

    std::map< std::string, std::string >& dictionary = treeOfdic[dictionaryName];

    if (dictionary.find(englishWord) == dictionary.end())
    {
      throw std::logic_error("Word not found");
    }
    dictionary[englishWord] = russianWord;
  }

  void create_dictionary(map& treeOfdic, std::istream& in)
  {
    std::string dictionaryName;
    if (!(in >> dictionaryName))
    {
      throw std::logic_error("Invalid arguments");
    }

    if (treeOfdic.find(dictionaryName) != treeOfdic.end())
    {
      throw std::logic_error("Dictionary already exists");
    }
    treeOfdic[dictionaryName] = std::map< std::string, std::string >();
  }

  void remove_word(map& treeOfdic, std::istream& in)
  {
    std::string dictionaryName, englishWord;
    if (!(in >> dictionaryName >> englishWord))
    {
      throw std::logic_error("Invalid arguments");
    }

    if (treeOfdic.find(dictionaryName) == treeOfdic.end())
    {
      throw std::logic_error("Dictionary not found");
    }

    std::map< std::string, std::string >& dictionary = treeOfdic[dictionaryName];

    if (dictionary.find(englishWord) == dictionary.end())
    {
      throw std::logic_error("Word not found");
    }

    dictionary.erase(englishWord);
  }

  void list_words(const map& treeOfdic, std::istream& in, std::ostream& out)
  {
    std::string dictionaryName;
    if (!(in >> dictionaryName))
    {
      throw std::logic_error("Invalid arguments");
    }

    if (treeOfdic.find(dictionaryName) == treeOfdic.end())
    {
      throw std::logic_error("Dictionary not found");
    }

    const std::map< std::string, std::string >& dictionary = treeOfdic.at(dictionaryName);
    for (const auto& pair : dictionary)
    {
      out << pair.first << " - " << pair.second << "\n";
    }
  }

  void search_words(const map& treeOfdic, std::istream& in, std::ostream& out)
  {
    std::string line;

    if (!std::getline(in, line))
    {
      throw std::logic_error("Invalid arguments");
    }

    std::vector< std::string > words;
    std::string word;
    size_t pos = 0, prev_pos = 0;

    while ((pos = line.find(' ', prev_pos)) != std::string::npos)
    {
      word = line.substr(prev_pos, pos - prev_pos);
      if (!word.empty())
      {
        words.push_back(word);
      }
      prev_pos = pos + 1;
    }
    word = line.substr(prev_pos);
    if (!word.empty())
    {
      words.push_back(word);
    }

    if (words.empty())
    {
      throw std::logic_error("No dictionary name provided");
    }
    std::string dictionaryName = words[0];

    if (treeOfdic.find(dictionaryName) == treeOfdic.end())
    {
      throw std::logic_error("Dictionary not found");
    }

    const std::map< std::string, std::string >& dictionary = treeOfdic.at(dictionaryName);

    for (size_t i = 1; i < words.size(); ++i)
    {
      const std::string& searchWord = words[i];
      if (dictionary.find(searchWord) != dictionary.end())
      {
        out << searchWord << " - " << dictionary.at(searchWord) << "\n";
      }
      else
      {
        throw std::logic_error("Invalid arguments");
      }
    }
  }

  void delete_dictionary(map& treeOfdic, std::istream& in)
  {
    std::string dictionaryName;
    if (!(in >> dictionaryName))
    {
      throw std::logic_error("Invalid arguments");
    }

    if (treeOfdic.find(dictionaryName) == treeOfdic.end())
    {
      throw std::logic_error("Dictionary not found");
    }

    treeOfdic.erase(dictionaryName);
  }

  void rename_dictionary(map& treeOfdic, std::istream& in)
  {
    std::string dictionaryName = "";
    std::string newDictionaryName = "";
    if (!(in >> dictionaryName >> newDictionaryName))
    {
      throw std::logic_error("Invalid arguments");
    }
    if (treeOfdic.find(dictionaryName) == treeOfdic.end() || treeOfdic.find(newDictionaryName) != treeOfdic.end())
    {
      throw std::logic_error("Dictionary not found or new name already exists");
    }

    std::map< std::string, std::string > dictionary = treeOfdic[dictionaryName];
    treeOfdic.erase(dictionaryName);
    treeOfdic[newDictionaryName] = dictionary;
  }

  void count_words(const map& treeOfdic, std::istream& in, std::ostream& out)
  {
    std::string dictionaryName = "";
    if (!(in >> dictionaryName))
    {
      throw std::logic_error("Invalid arguments");
    }

    if (treeOfdic.find(dictionaryName) == treeOfdic.end())
    {
      throw std::logic_error("Dictionary not found");
    }

    const std::map< std::string, std::string >& dictionary = treeOfdic.at(dictionaryName);
    out << dictionary.size() << "\n";
  }

  void merge_dictionaries(map& treeOfdic, std::istream& in)
  {
    std::string line;

    if (!std::getline(in, line) || line.empty())
    {
      throw std::out_of_range("Invalid arguments");
    }

    std::vector< std::string > words;
    std::string word;
    size_t pos = 0, prev_pos = 0;

    while ((pos = line.find(' ', prev_pos)) != std::string::npos)
    {
      word = line.substr(prev_pos, pos - prev_pos);
      if (!word.empty())
      {
        words.push_back(word);
      }
      prev_pos = pos + 1;
    }

    word = line.substr(prev_pos);
    if (!word.empty())
    {
      words.push_back(word);
    }

    if (words.empty())
    {
      throw std::out_of_range("Invalid arguments");
    }

    std::string newDictionaryName = words.front();
    words.erase(words.begin());

    if (treeOfdic.find(newDictionaryName) != treeOfdic.end())
    {
      throw std::out_of_range("New dictionary name already exists");
    }

    std::map< std::string, std::string > newDictionary;

    for (const std::string& dictionaryName : words)
    {
      if (treeOfdic.find(dictionaryName) == treeOfdic.end())
      {
        throw std::out_of_range("Invalid arguments");
      }

      std::map< std::string, std::string >& dictionary = treeOfdic[dictionaryName];

      for (const auto& pair : dictionary)
      {
        newDictionary[pair.first] = pair.second;
      }
    }

    treeOfdic[newDictionaryName] = newDictionary;
  }

  void repeating_words(const map& treeOfdic, std::istream& in, std::ostream& out)
  {
    std::string line;

    if (!std::getline(in, line))
    {
      throw std::logic_error("Error reading dictionaries");
    }

    if (line.empty())
    {
      throw std::out_of_range("No dictionaries specified");
    }

    std::vector< std::string > dictionaryNames;
    std::string dictionaryName;
    size_t pos = 0, prev_pos = 0;

    while ((pos = line.find(' ', prev_pos)) != std::string::npos)
    {
      dictionaryName = line.substr(prev_pos, pos - prev_pos);
      if (!dictionaryName.empty())
      {
        dictionaryNames.push_back(dictionaryName);
      }
      prev_pos = pos + 1;
    }

    dictionaryName = line.substr(prev_pos);
    if (!dictionaryName.empty())
    {
      dictionaryNames.push_back(dictionaryName);
    }

    if (dictionaryNames.empty())
    {
      throw std::out_of_range("No dictionaries specified");
    }

    for (const auto& name : dictionaryNames)
    {
      if (treeOfdic.find(name) == treeOfdic.end())
      {
        throw std::out_of_range("One or more dictionaries not found");
      }
    }

    std::map< std::string, int > wordCount;

    for (const std::string& name : dictionaryNames)
    {
      const std::map< std::string, std::string >& dictionary = treeOfdic.at(name);
      for (const auto& pair : dictionary)
      {
        const std::string& word = pair.first;
        if (wordCount.find(word) != wordCount.end())
        {
          wordCount[word]++;
        }
        else
        {
          wordCount[word] = 1;
        }
      }
    }

    size_t commonWordCount = 0;
    for (const auto& pair : wordCount)
    {
      if (pair.second == dictionaryNames.size())
      {
        commonWordCount++;
      }
    }

    out << commonWordCount << "\n";
  }

  void save(const map& treeOfdic, const std::string& filename)
  {
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
      throw std::logic_error("Cannot open file");
    }

    for (const auto& pair : treeOfdic)
    {
      outFile << pair.first;

      const std::map< std::string, std::string >& dictionary = pair.second;
      for (const auto& inner_pair : dictionary)
      {
        outFile << " " << inner_pair.first << " " << inner_pair.second;
      }

      outFile << "\n";
    }
  }

  void help(std::ostream& out)
  {
    out << "add_translation <словарь> <слово> <перевод> - Добавить перевод\n";
    out << "add_word <словарь> <слово> - Добавить слово\n";
    out << "count_words <словарь> - Вывод кол-ва слов\n";
    out << "create <словарь> - Создать словарь\n";
    out << "delete_dictionary <словарь> - Удалить словарь\n";
    out << "list_words <словарь> - Вывод списка слов\n";
    out << "merge <новый_словарь> <словарь1> <словарь2> ... <словарьN> - Создать новый словарь из старых\n";
    out << "remove_word <словарь> <слово> - Удалить слово\n";
    out << "rename_dictionary <словарь> <новое_название> - Переименовать словарь\n";
    out << "repeating_words <словарь1> <словарь2> ... <словарьN> - Поиск одинаковых слов в указанных словарях\n";
    out << "search <словарь> <слово1> <слово2> ... <словоN> - Поиск слова\n";
  }
}

