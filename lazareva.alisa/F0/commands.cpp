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
    out << " - count_entries <name> - get number of entries in the table\n";  
    out << " - list_tables - list all available tables\n";  
    out << " - check_table_exists <name> - check if a table exists\n";  
}

void lazareva::new_table(HashTable& tables, std::istream& in)
{
    std::string name;
    in >> name;

   
    if (name.empty()) {
        throw std::logic_error("<TABLE NAME CANNOT BE EMPTY>\n");
    }

    
    if (tables.count(name) > 0) {
        throw std::logic_error("<TABLE ALREADY EXISTS>\n");
    }

    tables[name] = {};  
    std::cout << "Table '" << name << "' created successfully.\n";
}

void lazareva::delete_table(HashTable& tables, std::istream& in)
{
    std::string name;
    in >> name;

    
    if (name.empty()) {
        throw std::logic_error("<TABLE NAME CANNOT BE EMPTY>\n");
    }

    
    if (tables.erase(name) == 0) {
        throw std::logic_error("<TABLE NOT FOUND>\n");
    }

    std::cout << "Table '" << name << "' deleted successfully.\n";
}

void lazareva::insert(HashTable& tables, std::istream& in)
{
    std::string table, key, value;
    in >> table >> key >> value;

    
    if (table.empty() || key.empty() || value.empty()) {
        throw std::logic_error("<TABLE, KEY, AND VALUE CANNOT BE EMPTY>\n");
    }

    
    if (tables.count(table) == 0) {
        throw std::logic_error("<TABLE NOT FOUND>\n");
    }

    
    tables[table][key] = value;
    std::cout << "Inserted/Updated key-value pair (" << key << ": " << value << ") in table '" << table << "'.\n";
}

void lazareva::remove_key(HashTable& tables, std::istream& in)
{
    std::string table, key;
    in >> table >> key;

    
    if (table.empty() || key.empty()) {
        throw std::logic_error("<TABLE AND KEY CANNOT BE EMPTY>\n");
    }

    
    if (tables.count(table) == 0) {
        throw std::logic_error("<TABLE NOT FOUND>\n");
    }

    
    if (tables[table].erase(key) == 0) {
        throw std::logic_error("<KEY NOT FOUND>\n");
    }

    std::cout << "Key '" << key << "' removed from table '" << table << "'.\n";
}

void lazareva::get(HashTable& tables, std::istream& in, std::ostream& out)
{
    std::string table, key;
    in >> table >> key;

    
    if (table.empty() || key.empty()) {
        throw std::logic_error("<TABLE AND KEY CANNOT BE EMPTY>\n");
    }

    
    if (tables.count(table) == 0) {
        throw std::logic_error("<TABLE NOT FOUND>\n");
    }

    
    auto it = tables[table].find(key);
    if (it == tables[table].end()) {
        throw std::logic_error("<KEY NOT FOUND>\n");
    }

    out << "Value for key '" << key << "' in table '" << table << "': " << it->second << "\n";
}

void lazareva::load(HashTable& tables, std::istream& in)
{
    std::string table, filename;
    in >> table >> filename;

    
    if (table.empty() || filename.empty()) {
        throw std::logic_error("<TABLE AND FILENAME CANNOT BE EMPTY>\n");
    }

    
    if (tables.count(table) == 0) {
        throw std::logic_error("<TABLE NOT FOUND>\n");
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::logic_error("<FAILED TO OPEN FILE>\n");
    }

    
    std::string key, value;
    while (file >> key >> value) {
        tables[table][key] = value;
    }

    std::cout << "Data loaded successfully from file '" << filename << "' into table '" << table << "'.\n";
}

void lazareva::save(HashTable& tables, std::istream& in)
{
    std::string table, filename;
    in >> table >> filename;

    
    if (table.empty() || filename.empty()) {
        throw std::logic_error("<TABLE AND FILENAME CANNOT BE EMPTY>\n");
    }

    
    if (tables.count(table) == 0) {
        throw std::logic_error("<TABLE NOT FOUND>\n");
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::logic_error("<FAILED TO OPEN FILE>\n");
    }

   
    for (const auto& entry : tables[table]) {
        file << entry.first << " " << entry.second << "\n";
    }

    std::cout << "Data saved successfully to file '" << filename << "' from table '" << table << "'.\n";
}

void lazareva::list(HashTable& tables, std::istream& in, std::ostream& out)
{
    std::string table;
    in >> table;

    
    if (table.empty()) {
        throw std::logic_error("<TABLE NAME CANNOT BE EMPTY>\n");
    }

    
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

    
    if (table.empty()) {
        throw std::logic_error("<TABLE NAME CANNOT BE EMPTY>\n");
    }

    /
    if (tables.count(table) == 0) {
        throw std::logic_error("<TABLE NOT FOUND>\n");
    }

    
    tables[table].clear();
    std::cout << "Table '" << table << "' cleared successfully.\n";
}

void lazareva::resize(HashTable& tables, std::istream& in)
{
    std::string table;
    size_t newSize;
    in >> table >> newSize;

    
    if (table.empty()) {
        throw std::logic_error("<TABLE NAME CANNOT BE EMPTY>\n");
    }

    
    if (tables.count(table) == 0) {
        throw std::logic_error("<TABLE NOT FOUND>\n");
    }

    
    std::cout << "Resizing table '" << table << "' to new size " << newSize << ".\n";
}

void lazareva::count_entries(HashTable& tables, std::istream& in, std::ostream& out)
{
    std::string table;
    in >> table;

    
    if (table.empty()) {
        throw std::logic_error("<TABLE NAME CANNOT BE EMPTY>\n");
    }

    
    if (tables.count(table) == 0) {
        throw std::logic_error("<TABLE NOT FOUND>\n");
    }

    
    out << "Number of entries in table '" << table << "': " << tables[table].size() << "\n";
}

