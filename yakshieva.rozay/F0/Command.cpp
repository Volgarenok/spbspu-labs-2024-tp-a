#include "Command.hpp"
#include "WorkType.hpp"
#include <fstream>
#include <stdexcept>
#include <algorithm>

namespace yakshieva
{
    size_t getCountOfWords(const std::string& str)
    {
        return std::count(str.begin(), str.end(), ' ') + 1;
    }
}

void yakshieva::newTree(std::string commands, tree_t& dicts)
{
    if (getCountOfWords(commands) != 1)
    {
        throw std::logic_error("<INVALID_ARGUMENTS>");
    }
    std::string newDictName = getWord(commands, false);
    if (dicts.count(newDictName))
    {
        throw std::logic_error("<DICTIONARY_ALREADY_EXISTS>");
    }
    dicts[newDictName] = {};
    std::get< 1 >(dicts[newDictName]) = "";
    std::get< 2 >(dicts[newDictName]) = 0;
}

void yakshieva::create(std::string commands, tree_t& dicts)
{
    if (getCountOfWords(commands) != 2)
    {
        throw std::logic_error("<INVALID_ARGUMENTS>");
    }
    std::string oldDictName = getWord(commands, false);
    std::string fileName = getWord(commands, true);
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        throw std::logic_error("<ERROR_OPEN_FILE>");
    }
    word_t& dict = std::get< 0 >(dicts[oldDictName]);
    if ((!dict.empty()) && (std::get< 1 >(dicts[oldDictName]).empty()))
    {
        throw std::logic_error("<RECORDING_IS_NOT_POSSIBLE>");
    }
    std::string line;
    num_set_t newList;
    size_t numLine = std::get< 2 >(dicts[oldDictName]);
    while (!file.eof())
    {
        numLine++;
        std::getline(file, line);
        std::get< 1 >(dicts[oldDictName]) += line + '\n';
        std::get< 2 >(dicts[oldDictName]) += 1;
        while (!line.empty())
        {
            std::string word;
            while ((word == "") && (!line.empty()))
            {
                word = getWord(line, false);
            }
            if (word != "")
            {
                word_t::iterator it = dict.find(word);
                if (it != dict.end())
                {
                    dict[word].insert(numLine);
                }
                else
                {
                    num_set_t numSet;
                    numSet.insert(numLine);
                    std::pair< const std::string, num_set_t > pair{ word, numSet };
                    dict.insert(pair);
                }
            }
        }
    }
}

void yakshieva::print(std::string commands, tree_t& dicts, std::ostream& out)
{
    std::string dictName = getWord(commands, false);
    if (!dicts.count(dictName))
    {
        throw std::logic_error("<INVALID_NAME>");
    }
    std::tuple< word_t, std::string, size_t >& dict = dicts.at(dictName);
    if (std::get< 0 >(dict).empty())
    {
        throw std::logic_error("<DICTIONARY_EMPTY>");
    }
    outDict(std::get< 0 >(dict), out);
}

void yakshieva::displayText(std::string commands, tree_t& dicts, std::ostream& out)
{
    if (getCountOfWords(commands) != 1)
    {
        throw std::logic_error("<INVALID_ARGUMENTS>");
    }
    std::string dictName = getWord(commands, false);
    if (!dicts.count(dictName))
    {
        throw std::logic_error("<INVALID_NAME>");
    }
    if (std::get< 1 >(dicts.at(dictName)).empty())
    {
        throw std::logic_error("<NO_TEXT>");
    }
    outText(std::get< 1 >(dicts.at(dictName)), std::get< 2 >(dicts.at(dictName)), out);
}

void yakshieva::showLine(std::string commands, tree_t& dicts, std::ostream& out)
{
    if (getCountOfWords(commands) != 2)
    {
        throw std::logic_error("<INVALID_ARGUMENTS>");
    }

    size_t lineNumber = getNumber(commands);
    if (lineNumber == 0)
    {
        throw std::logic_error("<INVALID_LINE>");
    }

    std::string dictName = getWord(commands, false);
    if (!dicts.count(dictName))
    {
        throw std::logic_error("<INVALID_NAME>");
    }

    word_t& dict = std::get<0>(dicts[dictName]);
    if (dict.empty())
    {
        throw std::logic_error("<DICTIONARY_EMPTY>");
    }

    std::string& text = std::get<1>(dicts[dictName]);
    size_t step;
    size_t beginPos = 0;
    for (size_t i = 1; i < lineNumber; i++)
    {
        step = 0;
        while (text[beginPos + step] != '\n')
        {
            step++;
        }
        beginPos += step + 1;
    }
    step = 0;
    while (text[beginPos + step] != '\n')
    {
        step++;
    }
    std::string line = text.substr(beginPos, step);
    out << line << std::endl;
}

void yakshieva::search(std::string commands, tree_t& dicts, std::ostream& out)
{
    if (getCountOfWords(commands) != 2)
    {
        throw std::logic_error("<INVALID_ARGUMENTS>");
    }
    std::string newDictName = getWord(commands, false);
    if (!dicts.count(newDictName))
    {
        throw std::logic_error("<INVALID_NAME>");
    }
    std::string word = getWord(commands, false);
    word_t& dict = std::get< 0 >(dicts[newDictName]);
    word_t::iterator it = dict.find(word);
    if (it == dict.end())
    {
        throw std::logic_error("<INVALID_WORD>");
    }
    else
    {
        outLink(*it, out);
    }
}

void yakshieva::addLine(std::string commands, tree_t& dicts)
{
    if (getCountOfWords(commands) < 2)
    {
        throw std::logic_error("<INVALID_ARGUMENTS>");
    }
    std::string oldDictName = getWord(commands, false);
    if (!dicts.count(oldDictName))
    {
        throw std::logic_error("<INVALID_NAME>");
    }
    word_t& dict = std::get< 0 >(dicts[oldDictName]);
    if ((!std::get< 0 >(dicts[oldDictName]).empty()) && (std::get< 1 >(dicts[oldDictName]).empty()))
    {
        throw std::logic_error("<RECORDING_IS_NOT_POSSIBLE>");
    }
    std::get< 1 >(dicts[oldDictName]) += commands + '\n';
    std::get< 2 >(dicts[oldDictName]) += 1;
    size_t numLine = std::get< 2 >(dicts[oldDictName]);
    while (!commands.empty())
    {
        std::string word = getWord(commands, false);
        if (word != "")
        {
            word_t::iterator it = dict.find(word);
            if (it != dict.end())
            {
                dict[word].insert(numLine);
            }
            else
            {
                num_set_t numSet;
                numSet.insert(numLine);
                std::pair< const std::string, num_set_t > pair{ word, numSet };
                dict.insert(pair);
            }
        }
    }
}

void yakshieva::addWord(std::string commands, tree_t& dicts)
{
    if (getCountOfWords(commands) != 3)
    {
        throw std::logic_error("<INVALID_ARGUMENTS>");
    }

    std::string dictName = getWord(commands, false);
    if (!dicts.count(dictName))
    {
        throw std::logic_error("<INVALID_NAME>");
    }

    std::string word = getWord(commands, false);
    size_t lineNumber = getNumber(commands);
    if (lineNumber == 0)
    {
        throw std::logic_error("<LINE_NUMBER_EQUAL_ZERO>");
    }

    word_t& dict = std::get<0>(dicts[dictName]);
    dict[word].insert(lineNumber);
}

void yakshieva::erase(std::string commands, tree_t& dicts)
{
    if (getCountOfWords(commands) != 2)
    {
        throw std::logic_error("<INVALID_ARGUMENTS>");
    }
    std::string dictName = getWord(commands, false);
    if (!dicts.count(dictName))
    {
        throw std::logic_error("<INVALID_NAME>");
    }
    size_t lineNum = getNumber(commands);
    word_t& dict = std::get< 0 >(dicts[dictName]);
    if (!lineNum)
    {
        std::logic_error("<LINE_NUMBER_EQUAL_ZERO>");
    }
    std::string& text = std::get< 1 >(dicts[dictName]);
    std::string line;
    size_t step;
    size_t beginPos = 0;
    for (size_t i = 1; i < lineNum; i++)
    {
        step = 0;
        while (text[beginPos + step] != '\n')
        {
            step++;
        }
        beginPos += step + 1;
    }
    step = 0;
    while (text[beginPos + step] != '\n')
    {
        step++;
    }
    line = text.substr(beginPos, step);
    text.erase(beginPos, step + 1);
    size_t max = std::get< 2 >(dicts[dictName]);
    std::get< 2 >(dicts[dictName]) -= 1;
    std::string word;
    while (!line.empty())
    {
        word = getWord(line, false);
        dict[word].erase(lineNum);
        if (dict.at(word).empty())
        {
            dict.erase(word);
        }
    }
    word_t::iterator it = std::get< 0 >(dicts[dictName]).begin();
    word_t::iterator end = std::get< 0 >(dicts[dictName]).end();
    for (it; it != end; it++)
    {
        for (size_t l = 1; l <= max; l++)
        {
            num_set_t::iterator itNum = it->second.find(l);
            if ((itNum != it->second.end()) && (*itNum > lineNum))
            {
                it->second.erase(l);
                it->second.insert(l - 1);
            }
        }
    }
}

void yakshieva::remove(std::string commands, tree_t& dicts)
{
    if (getCountOfWords(commands) != 1)
    {
        throw std::logic_error("<INVALID_ARGUMENTS>");
    }
    std::string oldDictName = getWord(commands, false);
    if (!dicts.count(oldDictName))
    {
        throw std::logic_error("<INVALID_NAME>");
    }
    dicts.erase(oldDictName);
}

void yakshieva::clear(std::string commands, tree_t& dicts)
{
    if (getCountOfWords(commands) != 1)
    {
        throw std::logic_error("<INVALID_ARGUMENTS>");
    }
    std::string dictName = getWord(commands, false);
    if (!dicts.count(dictName))
    {
        throw std::logic_error("<INVALID_NAME>");
    }
    std::get< 0 >(dicts[dictName]).clear();
    std::get< 1 >(dicts[dictName]) = "";
    std::get< 2 >(dicts[dictName]) = 0;
}
