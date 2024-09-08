#include "ownCmds.hpp"
#include <set>
#include <clocale>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

void skuratov::help(std::ostream& out)
{
  setlocale(LC_ALL, "Russian");
  out << "  load <text1> <text1.txt> - загрузка незашифрованного текста из файла" << '\n';
  out << "  huff <codes1> <text1> - создание кодировки дл€ не зашифрованного текста" << '\n';
  out << "  comp <encoded1> <text1> <codes1> - сжатие текста" << '\n';
  out << "  save <encoded1> <output1.bin> - сохранение данных" << '\n';
  out << "  encload <text2> <output1.bin> - загрузка зашифрованного текста из файла" << '\n';
  out << "  decomp <decoded1> <text1> <codes1> -  раскодирование сжатого текста" << '\n';
  out << "  eff <text1> <codes1> - вывод эффективности сжати€ текста" << '\n';
  out << "  sort <text1> - сортировка данных" << '\n';
  out << "  rm <text1> - удаление повтор€ющихс€ слов из текста" << '\n';
  out << "  count <text1> - подсчет количества слов в тексте" << '\n';
}

void skuratov::load(std::istream& in, std::ostream& out, Context& context)
{
  std::string textVar, infile;
  in >> textVar >> infile;

  std::ifstream file(infile);
  if (!file)
  {
    out << "<INVALID LOAD>" << '\n';
    return;
  }
  std::string text((std::istreambuf_iterator< char >(file)), std::istreambuf_iterator< char >());
  context.context[textVar] = text;
  out << "Loaded text for variable '" << textVar << "':\n" << text << "\n";
}

void skuratov::huff(std::istream& in, std::ostream& out, Context& context, CodeContext& codeContext)
{
  std::string codesVar, textVar;
  in >> codesVar >> textVar;

  if (context.context.find(textVar) == context.context.end())
  {
    out << "<INVALID HUFF>" << '\n';
    return;
  }

  std::string text = context.context[textVar];
  std::map< char, std::string > huffmanCodes;

  try
  {
    createHuffmanCodes(text, huffmanCodes);
    codeContext.codeContext[codesVar] = huffmanCodes;

    out << "Huffman codes for variable '" << codesVar << "':\n";
    for (const auto& pair : huffmanCodes)
    {
      out << pair.first << ": " << pair.second << "\n";
    }
  }
  catch (const std::exception&)
  {
    out << "<INVALID HUFF>" << '\n';
  }
}

void skuratov::compress(std::istream& in, std::ostream& out, Context& context, CodeContext& codeContext)
{
  std::string encodedVar, textVar, codesVar;
  in >> encodedVar >> textVar >> codesVar;

  if (context.context.find(textVar) == context.context.end() || codeContext.codeContext.find(codesVar) == codeContext.codeContext.end())
  {
    out << "<INVALID COMPRESSION>" << '\n';
    return;
  }

  std::string text = context.context[textVar];
  std::map< char, std::string > huffmanCodes = codeContext.codeContext[codesVar];
  std::string encodedText;

  if (compressText(text, huffmanCodes, encodedText))
  {
    context.context[encodedVar] = encodedText;
    out << "Text compressed into '" << encodedVar << "':\n" << encodedText << "\n";
  }
  else
  {
    out << "<INVALID COMPRESSION>" << '\n';
  }
}

void skuratov::save(std::istream& in, std::ostream& out, const Context& context)
{
  std::string encodedVar, outputFile;
  in >> encodedVar >> outputFile;

  auto it = context.context.find(encodedVar);
  if (it == context.context.end())
  {
    out << "<INVALID SAVE>" << '\n';
    return;
  }

  std::ofstream outfile(outputFile, std::ios::binary);
  if (!outfile)
  {
    out << "<INVALID SAVE>" << '\n';
    return;
  }

  outfile << it->second;
  out << "Data saved to " << outputFile << '\n';
}

void skuratov::loadEncoded(std::istream& in, std::ostream& out, Context& context)
{
  std::string codesVar, filename;
  in >> codesVar >> filename;

  std::ifstream infile(filename, std::ios::binary);
  if (!infile)
  {
    out << "<INVALID LOAD ENCODED>" << '\n';
    return;
  }

  std::string encodedData;
  infile >> encodedData;

  if (encodedData.empty())
  {
    out << "<NO DATA LOADED>" << '\n';
    return;
  }

  context.context[codesVar] = encodedData;

  out << "Loaded encoded data for variable '" << codesVar << "':\n";
  out << encodedData << "\n";
}

void skuratov::decompress(std::istream& in, std::ostream& out, Context& context, CodeContext& codeContext)
{
  std::string decodedVar, encodedVar, codesVar;
  in >> decodedVar >> encodedVar >> codesVar;

  if (context.context.find(encodedVar) == context.context.end())
  {
    out << "<INVALID ENCODED VARIABLE>" << '\n';
    return;
  }
  if (codeContext.codeContext.find(codesVar) == codeContext.codeContext.end())
  {
    out << "<INVALID CODES VARIABLE>" << '\n';
    return;
  }

  std::string encodedText = context.context[encodedVar];
  std::map< char, std::string > huffmanCodes = codeContext.codeContext[codesVar];
  std::string decodedText;

  out << "Encoded Text: " << encodedText << "\n";

  if (decompressText(encodedText, huffmanCodes, decodedText))
  {
    context.context[decodedVar] = decodedText;
    out << "Text decompressed into '" << decodedVar << "':\n" << decodedText << "\n";
  }
  else
  {
    out << "<INVALID DECOMPRESSION>" << '\n';
  }
}

void skuratov::eff(std::istream& in, std::ostream& out, const Context& context, const CodeContext& codeContext)
{
  std::string textVar, codesVar;
  in >> textVar >> codesVar;

  if (context.context.find(textVar) == context.context.end() || codeContext.codeContext.find(codesVar) == codeContext.codeContext.end())
  {
    out << "<INVALID EFF>" << '\n';
    return;
  }

  std::string text = context.context.at(textVar);
  std::map< char, std::string > huffmanCodes = codeContext.codeContext.at(codesVar);

  double efficiency = calculateEfficiency(text, huffmanCodes);
  double origSize = text.size() * 8;

  out << "Original size: " << origSize << " bits" << '\n';
  out << "Compressed size: " << efficiency << " bits" << '\n';
  out << "Compression difference: " << origSize - efficiency << " bits" << '\n';
}

void skuratov::sortData(std::istream& in, std::ostream& out, Context& context)
{
  std::string textVar;
  in >> textVar;

  if (context.context.find(textVar) == context.context.end())
  {
    out << "<INVALID SORT DATA>" << '\n';
    return;
  }

  std::string text = context.context[textVar];
  std::vector< std::string > words;
  size_t start = 0, end;

  while ((end = text.find_first_of(" ,;.", start)) != std::string::npos)
  {
    if (end > start)
    {
      words.push_back(text.substr(start, end - start));
    }
    start = end + 1;
  }

  if (start < text.length())
  {
    words.push_back(text.substr(start));
  }

  if (words.empty())
  {
    out << "<INVALID SORT DATA>" << '\n';
    return;
  }

  std::sort(words.begin(), words.end(), compareByLength);

  std::string sortedText;
  for (const auto& word : words)
  {
    sortedText += word + " ";
  }

  if (!sortedText.empty())
  {
    sortedText.pop_back();
  }
  context.context[textVar] = sortedText;
  out << "Data sorted in " << textVar << "\n";
  out << "Result: " << sortedText << '\n';
}

void skuratov::removeDuplicates(std::istream& in, std::ostream& out, Context& context)
{
  std::string textVar;
  in >> textVar;

  if (context.context.find(textVar) == context.context.end())
  {
    out << "<INVALID DUPLICATES REMOVAL>" << '\n';
    return;
  }

  std::string text = context.context[textVar];
  std::unordered_set< std::string > uniqueWords;
  std::vector< std::string > orderedWords;
  std::string word;

  size_t pos = {};
  while ((pos = text.find(' ')) != std::string::npos)
  {
    word = text.substr(0, pos);
    if (uniqueWords.insert(word).second) 
    {
      orderedWords.push_back(word);
    }
    text.erase(0, pos + 1);
  }

  if (!text.empty())
  {
    if (uniqueWords.insert(text).second)
    {
      orderedWords.push_back(text);
    }
  }

  if (orderedWords.empty())
  {
    out << "<INVALID DUPLICATES REMOVAL>" << '\n';
    return;
  }

  std::string result;
  for (const auto& uniqueWord : orderedWords)
  {
    result += uniqueWord + " ";
  }

  if (!result.empty())
  {
    result.pop_back();
  }
  context.context[textVar] = result;
  out << "Duplicates removed in " << textVar << ":\n" << result << "\n";
}

void skuratov::countWords(std::istream& in, std::ostream& out, const Context& context)
{
  std::string textVar;
  in >> textVar;

  if (context.context.find(textVar) == context.context.end())
  {
    out << "<INVALID WORD COUNT>" << '\n';
    return;
  }

  std::string text = context.context.at(textVar);
  size_t wordCount = {};
  size_t start = 0, end;

  while ((end = text.find_first_of(" ,;.", start)) != std::string::npos)
  {
    if (end > start)
    {
      ++wordCount;
    }
    start = end + 1;
  }

  if (start < text.length())
  {
    ++wordCount;
  }
  out << "Word count in " << textVar << ": " << wordCount << "\n";
}
