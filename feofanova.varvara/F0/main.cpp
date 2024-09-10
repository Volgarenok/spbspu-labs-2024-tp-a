#include"hash_table.cpp"
#include <string>
#include <clocale>
#include <windows.h>

class ConsoleCP
{
	int oldin;
	int oldout;

public:
	ConsoleCP(int cp)
	{
		oldin = GetConsoleCP();
		oldout = GetConsoleOutputCP();
		SetConsoleCP(cp);
		SetConsoleOutputCP(cp);
	}
	~ConsoleCP()
	{
		SetConsoleCP(oldin);
		SetConsoleOutputCP(oldout);
	}
};


int main()
{
	ConsoleCP cp(1251);
	hash_table<std::string> dictionary;

	while (true)
	{
		std::cout << "¬ведите одну из доступных команд: add, delete, find, print" << std::endl;
		std::string command;
		std::cin >> command;
		if (command == "add")
		{
			std::cout << "¬ведите слово на английском: ";
			std::string word;
			std::cin >> word;
			std::cout << "¬ведите его перевод: ";
			std::string trans;
			std::cin >> trans;
			std::cout << trans << std::endl;
			if (!dictionary.Find(word)) { dictionary.Add(word, trans); }
			dictionary.Add(word, trans);
		}
		else if (command == "delete")
		{
			std::cout << "¬ведите слово на английском которoе хотите удалить: ";
			std::string key;
			std::cin >> key;
			dictionary.Remove(key);
		}
		else if (command == "find")
		{
			std::cout << "¬ведите слово на английском которое хотите найти: ";
			std::string key;
			std::cin >> key;
			std::cout << std::boolalpha << dictionary.Find(key) << std::endl;
		}
		else if (command == "print")
		{
			dictionary.Print();
		}
		else { std::cout << "<INVALID COMMAND>" << std::endl; }
	}
}
