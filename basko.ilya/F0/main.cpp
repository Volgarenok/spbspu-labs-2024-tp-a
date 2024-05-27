#include <iostream>

void show_help()
{
  std::cout << "Список доступных команд" << endl;
  std::cout << "load [filename] - Загрузка файла" << endl;
  std::cout << "insert [word][number] - Добавление, вводим слово и номер строки" << endl;
  std::cout << "delete [word] - Удаление" << endl;
  std::cout << "search [word] - Поиск" << endl;
  std::cout << "show - Вывод" << endl;
  std::cout << "exit - Выход" << endl;
}

int main()
{
  return 0;
}
