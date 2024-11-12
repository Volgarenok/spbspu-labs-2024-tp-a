#include "command.hpp"

void vojuck::printHelp(std::ostream & output)
{
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
