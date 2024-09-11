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
