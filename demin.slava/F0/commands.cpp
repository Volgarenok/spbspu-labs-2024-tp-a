#include "commands.hpp"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

void demin::showHelp()
{
  std::cout << "--help: вывод справки" << std::endl;
  std::cout << "--check <FILE>: проверка корректности файла" << std::endl;
  std::cout << "read <FILE> <NAME>: чтение файла в список" << std::endl;
  std::cout << "out <NAME>: вывод перекрестных ссылок" << std::endl;
  std::cout << "add <NAME> <LINE> <NUMBER> <WORD>: вставка слова в строку" << std::endl;
  std::cout << "remove <NAME> <WORD>: удаление слова из списка" << std::endl;
  std::cout << "delete <NAME>: удаление списка" << std::endl;
  std::cout << "find <WORD> <NAME>: поиск слова в списке" << std::endl;
  std::cout << "combine <NEWNAME> <NAME1> <NAME2>: объединение двух списков" << std::endl;
  std::cout << "change <NAME> <WORD1> <WORD2>: замена двух слов местами" << std::endl;
  std::cout << "replace <NAME> <WORD> <NEWWORD>: замена слова на новое" << std::endl;
}

void demin::read(std::map< std::string, std::vector< std::string > > &refs, std::istream &in)
{
  std::string fileName, name;
  in >> fileName >> name;
  if (fileName.empty() || name.empty())
  {
    throw std::invalid_argument("");
  }
  else
  {
    std::ifstream file(fileName);
    if (!file)
    {
      throw std::invalid_argument("");
      return;
    }

    std::string line;
    while (getline(file, line))
    {
      refs[name].push_back(line);
    }
    file.close();
  }
}

void demin::out(std::map< std::string, std::vector< std::string > > &refs, std::istream &in, std::ostream &out)
{
  std::string name;
  in >> name;

  if (refs.find(name) == refs.end())
  {
    throw std::invalid_argument("");
    return;
  }

  for (const auto &line : refs[name])
  {
    out << line << std::endl;
  }
}

void demin::add(std::map< std::string, std::vector< std::string > > &refs, std::istream &in)
{
  std::string name, word;
  unsigned long int lineIndex, wordPos;
  in >> name >> lineIndex >> wordPos >> word;

  if (refs.find(name) == refs.end())
  {
    throw std::invalid_argument("");
    return;
  }

  if (lineIndex >= refs[name].size())
  {
    throw std::invalid_argument("");
    return;
  }

  std::istringstream iss(refs[name][lineIndex]);
  std::vector< std::string > words;
  std::string temp;
  while (iss >> temp)
  {
    words.push_back(temp);
  }

  if (wordPos > words.size())
  {
    throw std::invalid_argument("");
    return;
  }

  words.insert(words.begin() + wordPos, word);

  std::ostringstream oss;
  for (const auto &w : words)
  {
    oss << w << " ";
  }

  refs[name][lineIndex] = oss.str();
}

void demin::remove(std::map< std::string, std::vector< std::string > > &refs, std::istream &in)
{
  std::string name, word;
  in >> name >> word;
  if (refs.find(name) == refs.end())
  {
    throw std::invalid_argument("");
    return;
  }

  for (auto &line : refs[name])
  {
    size_t pos = line.find(word);
    while (pos != std::string::npos)
    {
      line.erase(pos, word.length());
      pos = line.find(word, pos);
    }
  }
}

void demin::deleteList(std::map< std::string, std::vector< std::string > > &refs, std::istream &in)
{
  std::string name;
  in >> name;

  if (refs.find(name) == refs.end())
  {
    throw std::invalid_argument("");
    return;
  }

  refs.erase(name);
}

void demin::find(std::map< std::string, std::vector< std::string > > &refs, std::istream &in, std::ostream &out)
{
  std::string word, name;
  in >> word >> name;

  if (refs.find(name) == refs.end())
  {
    throw std::invalid_argument("");
    return;
  }

  for (const auto &line : refs[name])
  {
    if (line.find(word) != std::string::npos)
    {
      out << line << std::endl;
    }
  }
}

void demin::combine(std::map< std::string, std::vector< std::string > > &refs, std::istream &in)
{
  std::string newName, name1, name2;
  in >> newName >> name1 >> name2;

  if (refs.find(name1) == refs.end() || refs.find(name2) == refs.end())
  {
    throw std::invalid_argument("");
    return;
  }

  for (size_t i = 0; i < std::min(refs[name1].size(), refs[name2].size()); ++i)
  {
    refs[newName].push_back(refs[name1][i] + " " + refs[name2][i]);
  }
}

void demin::change(std::map< std::string, std::vector< std::string > > &refs, std::istream &in)
{
  std::string name, word1, word2;
  in >> name >> word1 >> word2;

  if (refs.find(name) == refs.end())
  {
    throw std::invalid_argument("");
    return;
  }

  for (auto &line : refs[name])
  {
    size_t pos1 = line.find(word1);
    size_t pos2 = line.find(word2);
    if (pos1 != std::string::npos && pos2 != std::string::npos)
    {
      std::swap(line[pos1], line[pos2]);
    }
  }
}
