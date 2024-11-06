#include <iostream>
#include <unordered_map>
#include <map>
#include <functional>
#include "commands.h"

using namespace lazareva;

int main() {
    HashTable tables;

    std::map<std::string, std::function<void(std::istream&, std::ostream&)>> commands;
    commands["help"] = std::bind(help, std::ref(std::cout));
    commands["new"] = std::bind(new_table, std::ref(tables), std::placeholders::_1);
    commands["delete"] = std::bind(delete_table, std::ref(tables), std::placeholders::_1);
    commands["insert"] = std::bind(insert, std::ref(tables), std::placeholders::_1);
    commands["remove"] = std::bind(remove_key, std::ref(tables), std::placeholders::_1);
    commands["get"] = std::bind(get, std::ref(tables), std::placeholders::_1, std::ref(std::cout));
    commands["load"] = std::bind(load, std::ref(tables), std::placeholders::_1);
    commands["save"] = std::bind(save, std::ref(tables), std::placeholders::_1);
    commands["list"] = std::bind(list, std::ref(tables), std::placeholders::_1, std::ref(std::cout));
    commands["clear"] = std::bind(clear, std::ref(tables), std::placeholders::_1);
    commands["resize"] = std::bind(resize, std::ref(tables), std::placeholders::_1);

    std::string commandKey;
    while (std::cin >> commandKey) {
        try {
            commands.at(commandKey)(std::cin, std::cout);
        }
        catch (const std::exception& e) {
            std::cout << e.what();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return 0;
}

