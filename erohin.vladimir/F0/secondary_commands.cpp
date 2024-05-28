#include "secondary_commands.hpp"
#include <iostream>
#include <fstream>
#include "format.hpp"
#include "input_output_collection.hpp"

void erohin::printHelp(std::ostream & output)
{
  output << "Использование: program [options] <freqdict> — запуск с загрузкой словаря из файла <freqdict>\n";
  output << "Создание и хранение частотного словаря, созданного на основе переданного текста. ";
  output << "Возможность изменять и просматривать содержимое нескольких частотных словарей.\n\n";
  output << "Аргументы командной строки:\n";
  output << "\t--help — \"помощь\" по программе\n";
  output << "\t--check — проверка корректности частотного словаря, записанного в файл\n";
  output << "\t--numformat=<format> — запуск программы с загрузкой словаря из файла <freqdict> и заданием стиля <format>\n";
  output << "\t<format> = { NUMBER, PROPORTION, FRACTIONAL, PERCANTAGE }\n\n";
  output << "Команды:\n";
  output << "\t1. addtext <text> <source>\n";
  output << "\tДобавить текст с именем <text>, прочитанный из файла <source>.";
  output << "\t2. removetext <text>\n";
  output << "\tУдалить текст с именем <text>.\n\n";
  output << "\t3. createdict <dict> <text>\n";
  output << "\tСоздать новый частотный словарь с именем <dict> на основе текста с именем <text>.\n\n";
  output << "\t4. removedict <dict>\n";
  output << "\tУдалить частотный словарь с именем <dict>.\n\n";
  output << "\t5. print <dict>\n";
  output << "\tВывести частотный словарь с именем <dict>.\n\n";
  output << "\t6. count <dict>\n";
  output << "\tВывести общее количество слов и количество уникальных слов в частотном словаре с именем <dict>.\n\n";
  output << "\t7. sort <dict>\n";
  output << "\tВывести частотный словарь <dict>, отсортированный по частоте встречающихся слов.\n\n";
  output << "\t8. find <dict> <word>\n";
  output << "\tНайти слово <word> в частотном словаря <dict> и вывести частоту его использований.\n\n";
  output << "\t9. top <new_dict> <dict> <top_number>\n";
  output << "\tСоздать частотный словарь <new_dict>, состоящий из первых <top_number> по частоте слов из словаря <dict>.\n\n";
  output << "\t10. bottom <new_dict> <dict> <bot_number>\n";
  output << "\tСоздать частотный словарь <new_dict>, состоящий из последних <bot_number> по частоте слов из словаря <dict>.\n\n";
  output << "\t11. differ <new_dict> <dict1> <dict2>\n";
  output << "\tСоздать частотный словарь <new_dict> на основе разницы элементов словаря <dict1> и <dict2>.\n\n";
  output << "\t12. unite <new_dict> <dict1> <dict2>\n";
  output << "\tСоздать частотный словарь <new_dict> на основе объединения элементов словаря <dict1> и <dict2>.\n\n";
  output << "\t13. intersect <new_dict> <dict1> <dict2>\n";
  output << "\tСоздать частотный словарь <new_dict> на основе пересечения элементов словаря <dict1> и <dict2>.\n\n";
}

void erohin::checkDictionary(const char * file_name, std::ostream & output)
{
  std::fstream file(file_name, std::ios::in);
  collection dict_context;
  std::string dict_name;
  file >> StringFormat{ dict_name, ':' };
  while (!file.eof())
  {
    if (file.fail())
    {
      break;
    }
    inputDictionary(dict_context[dict_name], file);
    if (!file)
    {
      file.clear();
    }
    file >> StringFormat{ dict_name, ':' };
  }
  file.close();
  output << "File contains " << (!file.eof() && file.fail() ? "incorrect" : "correct") << " frequency dictionaries.\n";
}
