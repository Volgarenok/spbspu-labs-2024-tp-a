#include "cmdLineArgs.hpp"
#include <algorithm>
#include <fstream>
#include <functional>
#include <delimiterI.hpp>
#include "wordFreqPair.hpp"

void kravchenko::printHelp(std::ostream& out)
{
  out << "Система команд \"Частотный словарь\":\n";
  out << "1. scantext <dict> <text file>\n";
  out << "Проанализировать текст из файла <text file> на частотность и добавить эти данные в словарь <dict>.\n";
  out << "2. new <dict>\n";
  out << "Создает пустой новый словарь <dict>.\n";
  out << "3. list\n";
  out << "Вывести через пробел названия всех доступных словарей.\n";
  out << "4. remove <dict>\n";
  out << "Удалить словарь с именем <dict>.\n";
  out << "5. freq word <dict> <word>\n";
  out << "Вывести частоту слова <word> в словаре <dict>.\n";
  out << "6. freq least <dict> [n]\n";
  out << "Вывести n самых редко встречающихся слов в словаре <dict> в порядке возрастания частоты. Если n не указан,\n";
  out << "вывести 10 слов\n";
  out << "7. freq most <dict> [<n>]\n";
  out << "Вывести n самых часто встречающихся слов в словаре <dict> в порядке убывания частоты. Если n не указан,\n";
  out << "вывести 10 слов.\n";
  out << "8. save [<dict1> ... <dictn>]\n";
  out << "Сохранить все доступные словари в соответствующие файлы в формате <dict>.txt при отсутствии дополнительных\n";
  out << "параметров. Иначе сохранить таким образом только словари <dict1> ... <dictn>.\n";
  out << "9. intersect <new dict> <dict1> <dict2> [… <dictn>]\n";
  out << "Создать новый словарь <new dict> в виде пересечения словарей <dict1> и <dict2> … <dictn> (dict1 ∩ dict2 … ∩\n";
  out << "dictn).\n";
  out << "10. union <new dict> <dict1> <dict2> [… <dictn>]\n";
  out << "Создать новый словарь <new dict> в виде объединения словарей <dict1> и <dict2> … <dictn> (dict1 U dict2 … U\n";
  out << "dictn).\n";
  out << "11. difference <new dict> <dict1> <dict2> [… <dictn>]\n";
  out << "Создать новый словарь <new dict> в виде разности словаря <dict1> и <dict2> … <dictn> (dict1 \\ dict2 … \\ dictn).\n";
  out << "12. complement <new dict> <dict1> <dict2> [… <dictn>]\n";
  out << "Создать новый словарь <new dict> в виде относительного дополнения словаря <dict1> по отношению к <dict2> …\n";
  out << "<dictn>.\n";
}

void kravchenko::loadDict(const std::string& name, DictionaryMap& data)
{
  FrequencyDict loaded;
  std::ifstream file(name + ".txt");
  std::function< const std::pair< std::string, size_t >&(const WordFreqPair&) > getPair = &WordFreqPair::pairT;
  using inputIt = std::istream_iterator< WordFreqPair >;
  std::transform(inputIt{ file }, inputIt{}, std::inserter(loaded, loaded.begin()), getPair);
  file.close();
  data[name] = loaded;
}

void kravchenko::checkFile(const std::string& name, std::ostream& out)
{
  std::ifstream file(name + ".txt");
  WordFreqPair checked;
  while (file >> checked);
  out << ((file) ? "<VALID FILE>" : "<INVALID FILE>") << '\n';
}
