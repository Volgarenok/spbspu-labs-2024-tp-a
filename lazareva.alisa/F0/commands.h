#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>
#include <unordered_map>

namespace lazareva
{
    using HashTable = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

    void help(std::ostream& out);
    void new_table(HashTable& tables, std::istream& in);
    void delete_table(HashTable& tables, std::istream& in);
    void insert(HashTable& tables, std::istream& in);
    void remove_key(HashTable& tables, std::istream& in);
    void get(HashTable& tables, std::istream& in, std::ostream& out);
    void load(HashTable& tables, std::istream& in);
    void save(HashTable& tables, std::istream& in);
    void list(HashTable& tables, std::istream& in, std::ostream& out);
    void clear(HashTable& tables, std::istream& in);
    void resize(HashTable& tables, std::istream& in);
    void count_entries(HashTable& tables, std::istream& in, std::ostream& out);
    void list_tables(HashTable& tables, std::ostream& out);
    void check_table_exists(HashTable& tables, std::istream& in, std::ostream& out);
}

#endif
