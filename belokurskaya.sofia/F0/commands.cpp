#include "commands.hpp"

#include <functional>
#include <algorithm>

void belokurskaya::cmd::createDict(std::vector< EngRusDict >& vector, std::istream& in)
{
  std::string name;
  in >> name;
  if (subcmd::containsEngRusDict(vector, name))
  {
    throw std::runtime_error("Use a different name");
  }
  EngRusDict newErd(name);
  vector.push_back(newErd);
}

void belokurskaya::cmd::removeDict(std::vector< EngRusDict >& vector, std::istream& in)
{
  std::string name;
  in >> name;
  vector.erase(vector.begin() + subcmd::findIndexDict(vector, name));
}

void belokurskaya::cmd::add(std::vector< EngRusDict >& vector, std::istream& in)
{
  std::string name;
  bool flag = true;
  in >> name;
  size_t i = subcmd::findIndexDict(vector, name);
  std::string key, translation;
  in >> key >> translation;
  try
  {
    vector[i].addTranslation(key, translation);
  }
  catch (const std::invalid_argument&)
  {
    vector[i].addWord(key);
    vector[i].addTranslation(key, translation);
  }
}

void belokurskaya::cmd::remove(std::vector< EngRusDict >& vector, std::istream& in)
{
  std::string name;
  bool flag = true;
  in >> name;
  size_t i = subcmd::findIndexDict(vector, name);
  std::string key, translation;
  in >> key >> translation;
  if (translation == "ALL")
  {
    vector[i].removeWord(key);
    vector[i].addWord(key);
  }
  else
  {
    try
    {
      vector[i].removeTranslation(key, translation);
    }
    catch (const std::invalid_argument&)
    {
      throw std::runtime_error("Key not found or translation not associated with the key");
    }
  }
}

bool belokurskaya::cmd::subcmd::containsEngRusDict(std::vector< EngRusDict >& vector, std::string name)
{
  using namespace std::placeholders;
  return std::any_of(vector.begin(), vector.end(), std::bind(std::equal_to< std::string >(),
    std::bind(&EngRusDict::getName, _1), name)
  );
}

size_t belokurskaya::cmd::subcmd::findIndexDict(std::vector< EngRusDict >& vector, std::string name)
{
  using namespace std::placeholders;
  auto it = std::find_if(vector.begin(), vector.end(), std::bind(std::equal_to< std::string >(),
    std::bind(&belokurskaya::EngRusDict::getName, _1), name)
  );
  if (it != vector.end())
  {
    return std::distance(vector.begin(), it);
  }
  throw std::runtime_error("The dictionary with the specified name was not found");
}
