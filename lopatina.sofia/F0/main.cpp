#include <iostream>
#include <fstream>
#include <string>

/*
Параметры командной строки:
program [options] input.txt
--help – «помощь» по программе
--check <file name> проверка файла <text name> на наличие текста, подходящего для словаря

Система команд:
1. Команда: create <dictionary> <file>
Создает частотный словарь <dictionary> для файла <file>.
Если словарь с именем <dictionary> уже существует или файла с именем <file> не существует, то выводит сообщение <INVALID COMMAND>

2. Команда: print <dictionary> <key>
Выводит элемент словаря <dictionary> с ключом <key> (частоту встречаемости слова <key>).
Если такого словаря не существует или элемента с таким ключом в словаре нет, то выводит сообщение <INVALID COMMAND>
Пример:
print dict1 "banana"
print dict2 "monkey"
Ожидаемый результат:
 32
 <INVALID COMMAND>

3. Команда: print <dictionary>
Выводит словарь <dictionary>.
Если такого словаря не существует, то выводит сообщение <INVALID COMMAND>, или если словарь пуст, то выводит <EMPTY>
Пример:
 print dict1
 print dict2
 print dict3
Ожидаемый результат:
 banana: 32
 apple: 78
 …
 <EMPTY>
 <INVALID COMMAND>

4. Команда: sort <dictionary>
Сортирует словарь <dictionary> по частоте встречаемости слов (от более к менее частому).
Если такого словаря не существует, то выводит сообщение <INVALID COMMAND>.

5. Команда: delete <dictionary> <key>
Удаляет элемент <key> из словаря <dictionary>. Если такого элемента или словаря не существует, то выводит сообщение <INVALID COMMAND>.

6. Команда: delete <dictionary>
Удаляет словарь <dictionary>. Если такого словаря не существует, то выводит сообщение <INVALID COMMAND>.

7. Команда: compare <dictionary1> <dictionary2>
Сравнивает словари <dictionary1> и <dictionary2>, выводит 1 если они одинаковы или 0 если нет.
Если хотя бы одного словаря не существует, то выводит сообщение <INVALID COMMAND>.
Пример:
 compare dict1 dict2
 compare dict1 dict3
Ожидаемый результат:
 0
 <INVALID COMMAND>

8. Команда: combine <dictionary1> <dictionary2> <dictionary to combine>
Объединяет два словаря <dictionary1> и <dictionary2> в созданный <dictionary to combine>.
Если хотя бы одного словаря из <dictionary1> и <dictionary2> не существует, то выводит сообщение <INVALID COMMAND>.
Если <dictionary to combine> уже существует, то выводит сообщение <INVALID COMMAND>.

9. Команда: intersect <dictionary1> <dictionary2> <dictionary to intersect>
Создает словарь <dictionary to intersect> из пересечения словарей <dictionary1> и <dictionary2>.
Если хотя бы одного словаря из <dictionary1> и <dictionary2> не существует, то выводит сообщение <INVALID COMMAND>.
Если <dictionary to intersect> уже существует, то выводит сообщение <INVALID COMMAND>.

10. Команда: subtract <dictionary1> <dictionary2> <dictionary to subtract>
Создает словарь <dictionary to subtract>, в который помещает элементы <dictionary1> не входящие в <dictionary2>.
Если хотя бы одного словаря из <dictionary1> и <dictionary2> не существует, то выводит сообщение <INVALID COMMAND>.
Если <dictionary to subtract> уже существует, то выводит сообщение <INVALID COMMAND>.

11. Команда: mostfrequent <dictionary> <amount>
Выводит самые часто встречающиеся слова из словаря <dictionary> в количестве <amount>.
Если словаря <dictionary> не существует, то выводит сообщение <INVALID COMMAND>.
Если количество элементов в словаре меньше <amount>, то просто выводит все элементы словаря.
Если словарь пуст выводит <EMPTY>.
Пример:
 mostfrequent dict1 3
 mostfrequent dict3 90
Ожидаемый результат:
 apple: 78
 orange: 63
 banana: 32
 <INVALID COMMAND>
*/


using map_of_dicts = std::map< std::string, std::map< std::string, size_t > >;

class Dictionary
{
public:
  Dictionary() = default;
  ~Dictionary() = default;

  void add_word(std::string & word)
  {
    auto iter = words_.find(word);
    if (iter != end())
    {
      ++(*iter).second;
      return;
    }
    insert(std::pair< std::string, size_t >(word, 0));
  }

private:
  std::map< std::string, size_t > words_;
};


/*
void createCmd(map_of_dicts & dictionaries, std::istream & in)
{
  std::string dictionary_name = "", word = "";
  in >> dictionary_name;
  //in >> file_name;
  //проверка
  Dictionary popopo;
  while (in)
  {
    in >> word;
    popopo.add(word);
  }
  dictionaries.insert(std::pair< std::string, Dictionary>(dictionary_name, popopo));
}

void printCmd(dicts & map_of_dict, std::istream & in)
{
}

void sortCmd(dicts & map_of_dict, std::istream & in)
{
}

void deleteCmd(dicts & map_of_dict, std::istream & in)
{
}

void compareCmd(dicts & map_of_dict, std::istream & in)
{
}

void combineCmd(dicts & map_of_dict, std::istream & in)
{
}

void intersectCmd(dicts & map_of_dict, std::istream & in)
{
}

void subtractCmd(dicts & map_of_dict, std::istream & in)
{
}

void mostfrequentCmd(dicts & map_of_dict, std::istream & in)
{
}
*/

int main(int argc, char ** argv)
{
  if (argc == 2 && std::string(argv[1]) == "--help")
  {
    std::cout << "HELP\n";
  }
  else if (argc == 3 && std::string(argv[1]) == "--check")
  {
    std::cout << "CHECK\n";
    std::ifstream input(argv[2]);
    if (!input)
    {
      std::cerr << "No such file\n";
      return 1;
    }
  }

  std::map< std::string, std::map< std::string, size_t > > map_of_dict = {};
  std::map< std::string, Dictionary > dictionaries;
  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    //cmds["create"] = std::bind(createCmd, dictionaries, _1);
    //cmds["print"] = std::bind(printCmd, map_of_dict, _1, _2);
    //cmds["sort"] = std::bind(sortCmd, map_of_dict, _1);
    //cmds["delete"] = std::bind(deleteCmd, map_of_dict, _1);
    //cmds["compare"] = std::bind(compareCmd, map_of_dict, _1, _2);
    //cmds["combine"] = std::bind(combineCmd, map_of_dict, _1);
    //cmds["intersect"] = std::bind(intersectCmd, map_of_dict, _1);
    //cmds["subtract"] = std::bind(subtractCmd, map_of_dict, _1);
    //cmds["mostfrequent"] = std::bind(mostfrequentCmd, map_of_dict, _1, _2);
  }
  for (dictionaries.begin();)

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
