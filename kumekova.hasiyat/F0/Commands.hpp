#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "FrequencyDictionary.hpp"
#include <sstream>
#include <string>
#include <unordered_map>

namespace kumekova
{
void showHelp();
void printAllDictionaries(
    const std::unordered_map<std::string, FrequencyDictionary> &dictionaries,
    const std::string &currentDictionary);
void processCommand(
    std::unordered_map<std::string, FrequencyDictionary> &dictionaries,
    std::string &currentDictionary);
}

#endif
