#include <iostream>
#include <unordered_map>
#include <limits>
#include <functional>
#include <map>
#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>
#include "commands.h"

using namespace lazareva;

int main(int argc, const char* argv[])
{
    HashTable tables;

    std::map<std::string, std::function<void(std::istream&, std::ostream&)>> commands;

    using namespace std::placeholders;
    commands["help"] = std::bind(help, std::ref(std::cout));
    commands["new"] = std::bind(new_table, std::ref(tables), _1);
    commands["delete"] = std::bind(delete_table, std::ref(tables), _1);
    commands["insert"] = std::bind(insert, std::ref(tables), _1);
    commands["remove"] = std::bind(remove_key, std::ref(tables), _1);
    commands["get"] = std::bind(get, std::ref(tables), _1, std::ref(std::cout));
    commands["load"] = std::bind(load, std::ref(tables), _1);
    commands["save"] = std::bind(save, std::ref(tables), _1);
    commands["list"] = std::bind(list, std::ref(tables), _1, std::ref(std::cout));
    commands["clear"] = std::bind(clear, std::ref(tables), _1);
    commands["resize"] = std::bind(resize, std::ref(tables), _1);
    commands["count_entries"] = std::bind(count_entries, std::ref(tables), _1, std::ref(std::cout));
    commands["list_tables"] = std::bind(list_tables, std::ref(tables), std::ref(std::cout));
    commands["check_table_exists"] = std::bind(check_table_exists, std::ref(tables), _1, std::ref(std::cout));

    std::string commandKey;
    std::cin >> commandKey;

    while (!std::cin.eof())
    {
        try
        {
            commands.at(commandKey)(std::cin, std::cout);
        }
        catch (const std::exception& e)
        {
            std::cout << e.what();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin >> commandKey;
    }

    return 0;
}

