#include "Commands.hpp"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

void kumekova::showHelp()
{
  std::cout
      << "Available commands:\n"
      << "create <name1> <name2> ... - Creates a new dictionary with the "
         "specified names\n"
      << "insert <N> <key1> <key2> ... - Add an entry with the specified keys "
         "to the current dictionary\n"
      << "search <key> <name1> <name2> ... - Searches for an entry with the "
         "specified key in the specified dictionaries\n"
      << "delete <name> <key1> <key2> ... - Deletes an entry with the "
         "specified keys from the specified dictionary\n"
      << "remove <name1> <name2> ... - Deletes the specified dictionaries\n"
      << "compare <name1> <name2> - Compares two dictionaries and finds common "
         "keys\n"
      << "load <filename> <name1> - Loads text from a file into the specified "
         "dictionary.\n"
      << "top <N> <name1> <name2> - Shows the N most frequent words and their "
         "number in the specified dictionaries.\n"
      << "rare <N> <name1> <name2> ... - Finds rare words in the specified "
         "dictionaries\n"
      << "median - Calculates the median frequency of words among all "
         "dictionaries\n"
      << "print - Displays all available dictionaries, the contents of all "
         "dictionaries and the number of each word\n"
      << "clear <name1> <name2> ... - Clears the specified dictionaries\n"
      << "stats - Shows statistics of all dictionaries\n"
      << "help - Show this help message\n"
      << "exit - Exit the program\n";
}

void kumekova::printAllDictionaries(
    const std::unordered_map<std::string, FrequencyDictionary> &dictionaries,
    const std::string &currentDictionary)
{
  std::cout << "Available dictionaries:\n";
  std::for_each(dictionaries.begin(), dictionaries.end(),
                [&](const auto &pair)
                {
                  std::cout << "- " << pair.first;
                  if (pair.first == currentDictionary)
                  {
                    std::cout << " (current)";
                  }
                  std::cout << std::endl;
                });

  std::cout << "\nContents of all dictionaries:\n";
  std::for_each(dictionaries.begin(), dictionaries.end(),
                [&](const auto &pair)
                {
                  const auto &dictName = pair.first;
                  const auto &dictionary = pair.second;

                  std::cout << "Contents of dictionary '" << dictName << "':\n";
                  try
                  {
                    dictionary.print();
                  }
                  catch (const std::runtime_error &e)
                  {
                    std::cerr << "Error: " << e.what() << '\n';
                  }
                  std::cout << '\n';
                });
}

void kumekova::processCommand(
    std::unordered_map<std::string, FrequencyDictionary> &dictionaries,
    std::string &currentDictionary)
{
  std::unordered_map<std::string, std::function<void(std::istringstream &)>>
      commands;

  commands["create"] = [&dictionaries](std::istringstream &iss)
  {
    std::string name;
    std::vector<std::string> names;

    while (iss >> name)
    {
      names.push_back(name);
    }

    if (names.empty())
    {
      std::cerr << "Error: No names provided for create command.\n";
    }
    else
    {
      std::vector<std::string> existingDicts;
      std::copy_if(names.begin(), names.end(),
                   std::back_inserter(existingDicts),
                   [&dictionaries](const std::string &dictName)
                   {
                     return dictionaries.find(dictName) != dictionaries.end();
                   });

      std::for_each(existingDicts.begin(), existingDicts.end(),
                    [](const std::string &dictName)
                    {
                      std::cerr << "Error: Dictionary '" << dictName
                                << "' already exists.\n";
                    });

      std::for_each(names.begin(), names.end(),
                    [&dictionaries](const std::string &dictName)
                    {
                      if (dictionaries.find(dictName) == dictionaries.end())
                      {
                        dictionaries[dictName];
                        std::cout << "Dictionary '" << dictName << "' created.\n";
                      }
                    });
    }
  };

  commands["insert"] = [&dictionaries](std::istringstream &iss)
  {
    int N;
    iss >> N;

    if (N <= 0)
    {
      throw std::invalid_argument("Frequency N must be a positive integer.");
    }

    std::string dictName;
    iss >> dictName;

    if (dictionaries.find(dictName) == dictionaries.end())
    {
      std::cerr << "Error: Dictionary '" << dictName << "' does not exist.\n";
      return;
    }

    std::string line;
    std::getline(iss, line);

    if (line.empty() || std::all_of(line.begin(), line.end(), isspace))
    {
      throw std::invalid_argument("Key cannot be empty");
    }

    std::istringstream wordsStream(line);
    std::vector<std::string> words;

    std::copy_if(std::istream_iterator<std::string>(wordsStream),
                 std::istream_iterator<std::string>(),
                 std::back_inserter(words),
                 [](const std::string &word)
                 {
                   return !word.empty();
                 });

    for (const auto &w : words)
    {
      if (w.empty())
      {
        throw std::invalid_argument("Key cannot be empty");
      }

      for (int i = 0; i < N; ++i)
      {
        dictionaries[dictName].insert(w);
      }
    }

    std::cout << "Inserted words into dictionary '" << dictName
              << "' with frequency " << N << ".\n";
  };

  commands["search"] = [&dictionaries](std::istringstream &iss)
  {
    std::string key;
    iss >> key;

    if (key.empty())
    {
      throw std::invalid_argument("Key cannot be empty");
    }

    std::vector<std::string> dictNames{std::istream_iterator<std::string>(iss),
                                       std::istream_iterator<std::string>()};

    bool found = false;

    std::for_each(dictNames.begin(), dictNames.end(),
                  [&dictionaries, &found, &key](const std::string &dictName)
                  {
                    if (dictionaries.find(dictName) != dictionaries.end())
                    {
                      const auto &dictionary = dictionaries[dictName];
                      int count = dictionary.count(key);
                      if (count > 0)
                      {
                        std::cout << "Key '" << key << "' found in dictionary '"
                                  << dictName << "' with count: " << count
                                  << "\n";
                        found = true;
                      }
                    }
                    else
                    {
                      std::cerr << "Warning: Dictionary '" << dictName
                                << "' does not exist.\n";
                    }
                  });

    if (!found)
    {
      throw std::invalid_argument("Key '" + key +
                                  "' not found in any specified dictionary.");
    }
  };

  commands["delete"] = [&dictionaries](std::istringstream &iss)
  {
    std::string dictName;
    iss >> dictName;

    if (dictionaries.find(dictName) == dictionaries.end())
    {
      std::cerr << "Error: Dictionary '" << dictName << "' does not exist.\n";
      return;
    }

    std::vector<std::string> keys{std::istream_iterator<std::string>(iss),
                                  std::istream_iterator<std::string>()};

    std::for_each(keys.begin(), keys.end(),
                  [&dictionaries, &dictName](const std::string &k)
                  {
                    if (dictionaries[dictName].count(k) == 0)
                    {
                      throw std::invalid_argument(
                          "Key '" + k + "' not found in dictionary '" +
                          dictName + "'.");
                    }
                  });

    std::for_each(keys.begin(), keys.end(),
                  [&dictionaries, &dictName](const std::string &k)
    {
                    dictionaries[dictName].remove(k);
                    std::cout << "Key '" << k << "' removed from dictionary '"
                              << dictName << "'.\n";
                  });
  };

  commands["remove"] = [&dictionaries](std::istringstream &iss)
  {
    std::vector<std::string> dictNames;
    std::string name;

    while (iss >> name)
    {
      dictNames.push_back(name);
    }

    std::for_each(dictNames.begin(), dictNames.end(),
                  [&](const std::string &dictName)
                  {
                    if (dictionaries.erase(dictName) > 0)
                    {
                      std::cout << "Dictionary '" << dictName
                                << "' has been removed.\n";
                    }
                    else
                    {
                      std::cerr << "Error: Dictionary '" << dictName
                                << "' does not exist.\n";
                    }
                  });
  };

  commands["compare"] = [&dictionaries](std::istringstream &iss)
  {
    std::vector<std::string> dictNames{std::istream_iterator<std::string>(iss),
                                       std::istream_iterator<std::string>()};

    if (dictNames.size() != 2)
    {
      std::cerr
          << "Error: Exactly two dictionary names are required for comparison.\n";
      return;
    }

    if (std::any_of(dictNames.begin(), dictNames.end(),
                    [&dictionaries](const std::string &dictName)
                    {
                      return dictionaries.find(dictName) == dictionaries.end();
                    }))
    {
      std::cerr << "Error: One or more specified dictionaries do not exist.\n";
      return;
    }

    const auto &keys1 = dictionaries[dictNames[0]].getKeys();
    const auto &keys2 = dictionaries[dictNames[1]].getKeys();

    std::vector<std::string> commonKeys;
    std::set_intersection(keys1.begin(), keys1.end(), keys2.begin(),
                          keys2.end(), std::back_inserter(commonKeys));

    if (!commonKeys.empty())
    {
      std::cout << "Common keys in the specified dictionaries: ";
      for (const auto &key : commonKeys)
      {
        std::cout << key << " ";
      }
      std::cout << std::endl;
    }
    else
    {
      std::cout << "No common keys found in the specified dictionaries.\n";
    }
  };

  commands["load"] = [&dictionaries](std::istringstream &iss)
  {
    std::string filename;
    iss >> filename;

    std::string dictName;
    iss >> dictName;

    if (dictionaries.find(dictName) == dictionaries.end())
    {
      std::cerr << "Error: Dictionary '" << dictName << "' does not exist.\n";
      return;
    }

    std::ifstream file(filename);
    if (!file.is_open())
    {
      throw std::runtime_error("Could not open file: " + filename);
    }

    std::string word;
    while (file >> word)
    {
      dictionaries[dictName].insert(word);
    }

    std::cout << "Loaded words from file '" << filename
              << "' into specified dictionary '" << dictName << "'.\n";
  };

  commands["rare"] = [&dictionaries](std::istringstream &iss)
  {
    size_t N;
    iss >> N;

    std::vector<std::string> dictNames;
    std::string dictName;

    while (iss >> dictName)
    {
      dictNames.push_back(dictName);
    }

    for (const auto &name : dictNames)
    {
      if (dictionaries.find(name) == dictionaries.end())
      {
        throw std::invalid_argument("Dictionary '" + name +
                                    "' does not exist.");
      }
    }

    std::unordered_map<std::string, std::pair<int, std::vector<std::string>>>
        wordInfo;

    for (const auto &name : dictNames)
    {
      const auto &dictionary = dictionaries[name];
      for (const auto &key : dictionary.getKeys())
      {
        int frequency = dictionary.count(key);
        wordInfo[key].first += frequency;
        wordInfo[key].second.push_back(name);
      }
    }

    std::vector<std::pair<std::string, int>> rareWords;
    for (const auto &entry : wordInfo)
    {
      if (entry.second.first <= 1)
      {
        rareWords.push_back({entry.first, entry.second.first});
      }
    }

    std::sort(rareWords.begin(), rareWords.end(),
              [](const auto &a, const auto &b)
              {
                return a.second < b.second;
              });

    if (rareWords.size() > N)
    {
      rareWords.resize(N);
    }

    if (rareWords.empty())
    {
      std::cout << "No rare words found in the specified dictionaries.\n";
    }
    else
    {
      for (const auto &rareWord : rareWords)
      {
        const auto &word = rareWord.first;
        const auto &sources = wordInfo[word].second;
        std::cout << "Word: '" << word << "' found in dictionaries: ";
        for (const auto &src : sources)
        {
          std::cout << src << " ";
        }
        std::cout << std::endl;
      }
    }
  };

  commands["median"] = [&dictionaries](std::istringstream &)
  {
    if (dictionaries.empty())
    {
      std::cerr << "Error: No dictionaries available.\n";
      return;
    }

    try
    {
      double medianFrequency =
          FrequencyDictionary::medianAcrossDictionaries(dictionaries);
      std::cout << "Median frequency of words across specified dictionaries: "
                << medianFrequency << "\n";
    }
    catch (const std::runtime_error &e)
    {
      std::cerr << "Error: " << e.what() << '\n';
    }
  };

  commands["print"] = [&dictionaries,
                       &currentDictionary](std::istringstream &)
  {
    printAllDictionaries(dictionaries, currentDictionary);
    std::cout << "Contents of the current dictionary '" << currentDictionary
              << "':\n";
    try
    {
      dictionaries[currentDictionary].print();
    }
    catch (const std::runtime_error &e)
    {
      std::cerr << "Error: " << e.what() << '\n';
    }
  };

  commands["clear"] = [&dictionaries](std::istringstream &iss)
  {
    std::vector<std::string> dictNames;
    std::string name;

    while (iss >> name)
    {
      dictNames.push_back(name);
    }

    std::for_each(dictNames.begin(), dictNames.end(),
                  [&](const std::string &dictName)
                  {
                    if (dictionaries.find(dictName) != dictionaries.end())
                    {
                      dictionaries[dictName].clear();
                      std::cout << "Dictionary '" << dictName
                                << "' has been cleared.\n";
                    }
                    else
                    {
                      std::cerr << "Error: Dictionary '" << dictName
                                << "' does not exist.\n";
                    }
                  });
  };

  commands["stats"] = [&dictionaries](std::istringstream &iss)
  {
    std::vector<std::string> dictNames;
    std::string name;

    while (iss >> name)
    {
      dictNames.push_back(name);
    }

    if (dictNames.empty())
    {
      std::cout << "Statistics for all dictionaries:\n";
      std::for_each(dictionaries.begin(), dictionaries.end(),
                    [](const auto &pair)
                    {
                      const auto &dictName = pair.first;
                      const auto &dictionary = pair.second;
                      std::cout << "Dictionary '" << dictName << "': ";
                      dictionary.stats();
                    });
    }
    else
    {
      for (const auto &dictName : dictNames)
      {
        if (dictionaries.find(dictName) != dictionaries.end())
        {
          std::cout << "Statistics for dictionary '" << dictName << "': ";
          dictionaries[dictName].stats();
        }
        else
        {
          std::cerr << "Error: Dictionary '" << dictName << "' does not exist.\n";
        }
      }
    }
  };

  commands["help"] = [](std::istringstream &)
  {
    showHelp();
  };

  commands["exit"] = [](std::istringstream &)
  {
    std::exit(0);
  };

  std::string command;
  std::cout << "> ";
  std::getline(std::cin, command);

  if (command.empty())
  {
    return;
  }

  std::istringstream iss(command);
  std::string action;
  iss >> action;

  auto cmdIt = commands.find(action);
  if (cmdIt != commands.end())
  {
    try
    {
      cmdIt->second(iss);
    }
    catch (const std::invalid_argument &e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
  else
  {
    std::cout << "Unknown command. Type help for a list of commands.\n";
  }
}
