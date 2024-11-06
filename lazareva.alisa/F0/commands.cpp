#include "commands.h"
#include <fstream>
#include <stdexcept>
#include <iterator>

void lazareva::help(std::ostream& out)
{
    out << "List of commands:\n";
    out << " - new <name> - create a new hash table\n";
    out << " - delete <name> - delete a hash table\n";
    out << " - insert <name> <key> <value> - insert or update a key-value pair\n";
    out << " - remove <name> <key> - remove a key-value pair\n";
    out << " - get <name> <key> - get value by key\n";
    out << " - load <name> <filename> - load data from file\n";
    out << " - save <name> <filename> - save data to file\n";
    out << " - list <name> - list all key-value pairs\n";
    out << " - clear <name> - clear the hash table\n";
    out << " - resize <name> <new_size> - resize the hash table\n";
}

void lazareva::new_table(HashTable& tables, std::istream& in)
{
    std::string name;
    in >> name;
    if (tables.count(name) > 0) {
        throw std::logic_error("<ALREADY EXISTS>\n");
    }
    tables[name] = {}; // Create an empty entry
}

void lazareva::delete_table(HashTable& tables, std::istream& in)
{
    std::string name;
    in >> name;
    if (tables.erase(name) == 0) {
        throw std::logic_error("<TABLE NOT FOUND>\n");
    }
}

void lazareva::insert(HashTable& tables, std::istream& in)
{
    std::string table, key, value;
    in >> table >> key >> value;

    if (tables.count(table) == 0) {
        throw std::logic_error("<TABLE NOT FOUND>\n");
    }
    tables[table][key] = value; // Insert or update
}

void lazareva::remove_key(HashTable& tables, std::istream& in)
{
    std::string table, key;
    in >> table >> key;

    if (tables.count(table) == 0) {
        throw std::logic_error("<TABLE NOT FOUND>\n");
    }
    if (tables[table].erase(key) == 0) {
        throw std::logic_error("<KEY NOT FOUND>\n");
    }
}

void lazareva::get(HashTable& tables, std::istream& in, std::ostream& out)
{
    std::string table, key;
    in >> table >> key;

    if (tables.count(table) == 0) {
        throw std::logic_error("<TABLE NOT FOUND>\n");
    }
    auto it = tables[table].find(key);
    if (it == tables[table].end()) {
        throw std::logic_error("<KEY NOT FOUND>\n");
    }
    out << "Value for " << key << ": " << it->second << "\n";
}

void lazareva::load(HashTable& tables, std::istream& in)
{
    std::string table, filename;
    in >> table >> filename;

    if (tables.count(table) == 0) {
        throw std::logic_error("<TABLE NOT FOUND>\n");
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::logic_error("<FILE NOT FOUND>\n");
    }

    std::string key, value;
    while (file >> key >> value) {
        tables[table][key] = value;
    }
}

void lazareva::save(HashTable& tables, std::istream& in)
{
    std::string table, filename;
    in >> table >> filename;

    if (tables.count(table) == 0) {
        throw std::logic_error("<TABLE NOT FOUND>\n");
    }

    std::ofstream file(filename);
    for (const auto& entry : tables[table]) {
        file << entry.first << " " << entry.second << "\n";
    }
}

void lazareva::list(HashTable& tables, std::istream& in, std::ostream& out)
{
    std::string table;
    in >> table;

    if (tables.count(table) == 0) {
        throw std::logic_error("<TABLE NOT FOUND>\n");
    }

    for (const auto& entry : tables[table]) {
        out << entry.first << ": " << entry.second << "\n";
    }
}

void lazareva::clear(HashTable& tables, std::istream& in)
{
    std::string table;
    in >> table;

    if (tables.count(table) == 0) {
        throw std::logic_error("<TABLE NOT FOUND>\n");
    }
    tables[table].clear();
}

void lazareva::resize(HashTable& tables, std::istream& in)
{
    std::string table;
    size_t newSize;
    in >> table >> newSize;

    if (tables.count(table) == 0) {
        throw std::logic_error("<TABLE NOT FOUND>\n");
    }
    // Resize logic can be added here if needed
    // Currently, this function just reports that resizing is done
}

