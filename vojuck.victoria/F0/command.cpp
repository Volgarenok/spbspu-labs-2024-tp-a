#include "command.hpp"

void vojuck::printHelp(std::ostream & output)
{
//1
  output << "1.Make new  dictionary:\n";
  output << "  make <dictionary_name>\n";
  output << "2.Delete dictionary:\n";
  output << "  delete <dictionary_name>\n";
  output << "3.Load words from file to the dictionary:\n";
  output << "  load <dictionary_name> <file_name>\n";
  output << "4.Add word to the dictionary:\n";
  output << "  add <dictionary_name> <word>\n";
  output << "5.Save dictionary to the file:\n";
  output << "  save <dictionary_name> <file_name>\n";
  output << "6.Remove word from the dictionary:\n";
  output << "  remove <dictionary_name> <word>\n";
  output << "7.Print frequency of the word in the dictionary:\n";
  output << "  count <dictionary_name> <word>\n";
  output << "8.print dictionary and their frequency";
  output << "  print <dictionary_name>\n";
  output << "9.Merge two dictionaries:\n";
  output << "  merge <dictionary_name1> <dictionary_name2> <total_name>\n";
  output << "10.Create a dictionary containing words and their frequencies\n";
  output << "  that are in the first and second dictionary,\n";
  output << "  but are missing words  that are in both:\n";
  output << "  merge_unique <dictionary_name1> <dictionary_name2> <total_name>\n";
  output << "11.Create a dictionary with intersection of two dictionary \n";
  output << "   intersection <dictionary_name1> <dictionary_name2>  <total_name>\n";
}
void vojuck::increaseDict(dict_t & dict, std::istream & input)
{
  std::string word;
  while (input >> word)
  {
    std::string cleanWord;
    for (size_t i = 0; i < word.length(); ++i)
    {
      char c = word[i];
      if (std::isalpha(c))
      {
        cleanWord += std::tolower(c);
      }
    }
    if (!cleanWord.empty())
    {
      dict[cleanWord]++;
    }
  }
}
//1
void vojuck::makeCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output)
{
  std::string dictName;
  input >> dictName;
  if (dicts.find(dictName) != dicts.end())
  {
    throw std::logic_error("<ALREADY EXISTS>\n");
  }
  dicts[dictName];
  if (input.peek() != '\n')
  {
    std::string fileName;
    input >> fileName;
    std::ifstream file(fileName);
    if (!file.is_open())
    {
      throw std::logic_error("Couldn`t open file" + fileName + "\n");
    }
    vojuck::increaseDict(dicts[dictName], file);
  }
  output << "The dictionary " << dictName << " has been created.\n";
}
void vojuck::saveDictToFile(std::ofstream & file, dict_t::const_iterator it, dict_t::const_iterator end)
{
  while (it != end)
  {
    file << it->first << " " << it->second << "\n";
    ++it;
  }
}
