#include "userInterface.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include <functional>
#include <map>
#include <limits>
#include "HuffmanCoding.hpp"

void petrov::UserInterface::readCommand(std::istream& in, std::ostream& out)
{
  std::map < std::string, std::function< void() > > cmdDictionary;
  cmdDictionary["readText"] = std::bind(&petrov::UserInterface::readText, this, std::ref(in), std::ref(out));
  cmdDictionary["writeText"] = std::bind(&petrov::UserInterface::writeText, this, std::ref(in));
  cmdDictionary["deleteText"] = std::bind(&petrov::UserInterface::deleteText, this, std::ref(in));
  cmdDictionary["decode"] = std::bind(&petrov::UserInterface::decode, this, std::ref(in));
  cmdDictionary["encode"] = std::bind(&petrov::UserInterface::encode, this, std::ref(in));
  cmdDictionary["autoCodes"] = std::bind(&petrov::UserInterface::autoCodes, this, std::ref(in));
  cmdDictionary["readCodes"] = std::bind(&petrov::UserInterface::readCodes, this, std::ref(in));
  cmdDictionary["writeCodes"] = std::bind(&petrov::UserInterface::writeCodes, this, std::ref(in));
  cmdDictionary["getSize"] = std::bind(&petrov::UserInterface::getSize, this, std::ref(in), std::ref(out));
  cmdDictionary["compareSizes"] = std::bind(&petrov::UserInterface::compareSizes, this, std::ref(in), std::ref(out));
  cmdDictionary["output"] = std::bind(&petrov::UserInterface::output, this, std::ref(in), std::ref(out));
  cmdDictionary["--help"] = std::bind(&petrov::UserInterface::help, this, std::ref(out));
  out << "> ";
  std::string cmd = "";
  while (in >> cmd)
  {
    try
    {
      cmdDictionary.at(cmd)();
    }
    catch (const std::out_of_range&)
    {
      out << "<INVALID COMMAND>\n";
    }
    catch (const std::logic_error& e)
    {
      out << e.what() << '\n';
    }
    in.clear();
    using numLim = std::numeric_limits< std::streamsize >;
    in.ignore(numLim::max(), '\n');
    out << "\n> ";
  }
}

void petrov::UserInterface::readText(std::istream& in, std::ostream& out)
{
  std::string file, name;
  in >> file >> name;
  if (texts_.find(name) != texts_.cend())
  {
    out << "> This name is taken. Read anyway y/n: ";
    char ans;
    in >> ans;
    if (ans != 'y')
    {
      return;
    }
  }
  texts_[name] = file;
}
void petrov::UserInterface::writeText(std::istream& in)
{
  std::string name, file;
  in >> name >> file;
  try
  {
    std::ifstream inFile(texts_.at(name), std::ios::in);
    inFile >> std::noskipws;
    std::ofstream outFile(file, std::ios::out);
    using isIt = std::istream_iterator< char >;
    using osIt = std::ostream_iterator< char >;
    std::copy(isIt(inFile), isIt(), osIt(outFile));
    inFile.close();
    outFile.close();
  }
  catch (const std::out_of_range&)
  {
    throw std::logic_error("<INVALID NAME>");
  }
}
void petrov::UserInterface::deleteText(std::istream& in)
{
  std::string name;
  in >> name;

  auto deletable = texts_.find(name);
  if (deletable == texts_.end())
  {
    throw std::logic_error("<INVALID NAME>");
  }
  texts_.erase(deletable);
}
void petrov::UserInterface::decode(std::istream& in)
{
  std::string codeName, binName, textName;
  in >> codeName >> binName >> textName;

  if (codes_.find(codeName) == codes_.cend())
  {
    throw std::logic_error("<INVALID CODES NAME>");
  }
  if (texts_.find(binName) == texts_.cend())
  {
    throw std::logic_error("<INVALID READ NAME>");
  }

  std::ifstream inFile(texts_[binName], std::ios::binary);
  inFile >> std::noskipws;
  std::ofstream outFile(textName, std::ios::out);
  petrov::decode(codes_[codeName], outFile, inFile);
}
void petrov::UserInterface::encode(std::istream& in)
{
  std::string codeName, textName, binName;
  in >> codeName >> textName >> binName;

  if (codes_.find(codeName) == codes_.cend())
  {
    throw std::logic_error("<INVALID CODES NAME>");
  }
  if (texts_.find(textName) == texts_.cend())
  {
    throw std::logic_error("<INVALID READ NAME>");
  }
  std::ifstream inFile(texts_[textName], std::ios::in);
  inFile >> std::noskipws;
  using isIt = std::istream_iterator< char >;
  setType tmpSet(compareNodes);
  auto addToDest = std::bind(&addToSet, std::ref(tmpSet), std::placeholders::_1);
  std::for_each(isIt(inFile), isIt(), addToDest);
  if (!isSubset(codes_[codeName], tmpSet))
  {
    throw std::logic_error("<NOT ENOUGH CODES>");
  }
  inFile.clear();
  inFile.seekg(0, std::ios::beg);

  std::ofstream outFile(binName, std::ios::binary);
  petrov::encode(codes_[codeName], outFile, inFile);
  inFile.close();
  outFile.close();
}
void petrov::UserInterface::autoCodes(std::istream& in)
{
  std::string file, name;
  in >> file >> name;
  if (texts_.find(file) == texts_.cend())
  {
    throw std::logic_error("<INVALID READ NAME>");
  }
  setType codes(compareNodes);
  std::ifstream inFile(texts_[file], std::ios::in);
  codes_[name] = petrov::autoCodes(codes, inFile);
  inFile.close();
}
void petrov::UserInterface::readCodes(std::istream& in)
{
  std::string file, name;
  in >> file >> name;
  std::ifstream inFile(file, std::ios::in);
  if (!inFile)
  {
    throw std::logic_error("<INVALID READ NAME>");
  }
  inFile >> std::noskipws;
  Node tmpNode;
  setType tmpSet(compareNodes);
  while (!inFile.eof())
  {
    inFile >> tmpNode;
    tmpSet.insert(tmpNode);
    if (inFile.fail())
    {
      inFile.clear();
      using numLim = std::numeric_limits< std::streamsize >;
      inFile.ignore(numLim::max(), '\n');
    }
  }
  inFile.close();
  codes_[name] = tmpSet;
}
void petrov::UserInterface::writeCodes(std::istream& in)
{
  std::string name, file;
  in >> name >> file;
  if (codes_.find(name) == codes_.cend())
  {
    throw std::logic_error("<INVALID READ NAME>");
  }
  std::ofstream outFile(file, std::ios::out);
  using outIt = std::ostream_iterator< Node >;
  std::copy(codes_[name].cbegin(), codes_[name].cend(), outIt(outFile, "\n"));
  outFile.close();
}
void petrov::UserInterface::getSize(std::istream& in, std::ostream& out)
{
  std::string file;
  in >> file;
  out << getSizeOfFile(file) << '\n';
}
void petrov::UserInterface::compareSizes(std::istream& in, std::ostream& out)
{
  std::string name1, name2;
  in >> name1 >> name2;
  out << ((getSizeOfFile(name1) * 100) / getSizeOfFile(name2)) << "%\n";
}
void petrov::UserInterface::output(std::istream& in, std::ostream& out)
{
  std::string name;
  in >> name;
  try
  {
    std::ifstream inFile(texts_.at(name), std::ios::in);
    inFile >> std::noskipws;
    using outIt = std::ostream_iterator< char >;
    using inIt = std::istream_iterator< char >;
    std::copy(inIt(inFile), inIt(), outIt(out));
    inFile.close();
    return;
  }
  catch (const std::out_of_range&)
  {
  }
  try
  {
    using outIt = std::ostream_iterator< Node >;
    setType set = codes_.at(name);
    std::copy(set.cbegin(), set.cend(), outIt(out, "\n"));
  }
  catch (const std::out_of_range&)
  {
    out << "<INVALID NAME>";
  }
}
void petrov::UserInterface::help(std::ostream& out)
{
  out << "1. readText <file> <name>\n"
    << "Считать файл <file> под имя <name>\n"
    << "Если уже существует <name> то вывести сообщение \"This name is taken."
    << "Read anyway y/n: \"\n"
    << "В случае 'y' перезаписать <name>\n"
    << "В случае 'n' ничего не делать\n"
    << "Если хотя бы один из аргументов не передан то вывести <INVALID ARGUMENT>\n"
    << "2. writeText <name> <file>\n"
    << "Записать содержимое <name> в файл <file>\n"
    << "Если файла <file> не существует создать его\n"
    << "Если файла <name> не существует то вывести <INVALID NAME>\n"
    << "Если хотя бы один из аргументов не передан то вывести <INVALID ARGUMENT>\n"
    << "3. deleteText <name>\n"
    << "Удалить файл <name>\n"
    << "Если файла <name> не существует то вывести <INVALID NAME>\n"
    << "Если аргумент не передан то вывести <INVALID ARGUMENT>\n"
    << "4. decode <codesName> <binName> <txtName>\n"
    << "Используя созданное дерево кодов <codesName>, расшифровать данные"
    << "из <binName> и  записать в <txtName>\n"
    << "Если кодов в <codesName> не хватает чтобы раскодировать <binName>"
    << "то вывести <NOT ENOUGH CODES>\n"
    << "Если <txtName> не существует создать его\n"
    << "Если <binName> не существует то вывести <INVALID READ NAME>\n"
    << "Если <codesName> не существует то вывести <INVALID CODES NAME>\n"
    << "Если хотя бы один из аргументов не передан то вывести <INVALID ARGUMENT>\n"
    << "5. encode <codesName> <txtName> <binName>\n"
    << "Используя созданное дерево кодов <codesName>,"
    << "зашифровать данные из <txtName> и  записать в <binName>\n"
    << "Если кодов в <codesName> не хватает чтобы закодировать"
    << "<txtName> то вывести <NOT ENOUGH CODES>\n"
    << "Если <binName> не существует создать его\n"
    << "Если <txtName> не существует то вывести <INVALID READ NAME>\n"
    << "Если <codesName> не существует то вывести <INVALID CODES NAME>\n"
    << "Если хотя бы один из аргументов не передан то вывести <INVALID ARGUMENT>\n"
    << "6. autoCodes <txtName> <codesName>\n"
    << "Создать дерево кодов для всех символов в <txtName>,"
    << "используя алгоритм Хаффмана, и записать в <codesName>\n"
    << "Если <codesName> не существует создать его\n"
    << "Если хотя бы один из аргументов не передан то вывести <INVALID ARGUMENT>\n"
    << "7. readCodes <codesFile> <codesName>\n"
    << "Считать коды из файла <codesFile> в дерево кодов <codesName>\n"
    << "Если <codesName> не существует создать его\n"
    << "Если хотя бы один из аргументов не передан то вывести <INVALID ARGUMENT>\n"
    << "8. writeCodes <codesName> <codesFile>\n"
    << "Записать коды из <codesName> в файл <codesFile>\n"
    << "Если <codesFile> не существует создать его\n"
    << "Если хотя бы один из аргументов не передан то вывести <INVALID ARGUMENT>\n"
    << "9. getSize <name>\n"
    << "Вывести в стандартный поток вывода размер данных <name>\n"
    << "10. compareSizes <name1> <name2>\n"
    << "Вывести в стандартный поток вывода процентное"
    << "соотношение размера данных <name1> к <name2>\n"
    << "11. output <name>\n"
    << "Вывести в стандартный поток вывода содержимое <name>\n"
    << "Если введенной команды не существует, вывести <INVALID COMMAND>\n";
}
size_t petrov::UserInterface::getSizeOfFile(const std::string& file)
{
  try
  {
    std::ifstream inFile(texts_.at(file), std::ios::ate | std::ios::binary);
    size_t size = inFile.tellg();
    inFile.close();
    return size;
  }
  catch (const std::out_of_range&)
  {
    throw std::logic_error("<INVALID NAME>");
  }
  return -1;
}
