#include "ownCmds.hpp"

void skuratov::help(std::ostream& out)
{
  out << "  load <text1> <text1.txt> - загрузка незашифрованного текста из файла\n";
  out << "  huff <codes1> <text1> - создание кодировки дл€ не зашифрованного текста\n";
  out << "  compress <encoded1> <text1> <codes1> - сжатие текста\n";
  out << "  save <encoded1> <output1.bin> - сохранение данных\n";
  out << "  load_encoded <text3> <codes1> <output1.bin> - загрузка зашифрованного текста из файла\n";
  out << "  decompress <decoded1> <text3> <codes1> -  раскодирование сжатого файла\n";
  out << "  eff text1 codes1 - вывод эффективности сжати€ текста\n";
  out << "  sort_data <encoded1> - сортировка данных\n";
  out << "  remove_duplicates <text1> - удаление повтор€ющихс€ слов из текста\n";
  out << "  count_words <text1> - подсчет количества слов в тексте\n";
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
  }
  catch (...)
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
    out << "Text compressed into " << encodedVar << "\n";
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
  out << "Data saved to " << outputFile << "\n";
}

void skuratov::loadEncoded(std::istream& in, std::ostream& out, CodeContext& codeContext)
{
  std::string codesVar, filename;
  in >> codesVar >> filename;

  std::ifstream infile(filename);
  if (!infile)
  {
    out << "<INVALID LOAD ENCODED>" << '\n';
    return;
  }

  std::map< char, std::string > huffmanCodes;
  char ch = {};
  std::string code;
  while (infile >> ch >> code)
  {
    huffmanCodes[ch] = code;
  }

  codeContext.codeContext[codesVar] = huffmanCodes;
}

void skuratov::decompress(std::istream& in, std::ostream& out, Context& context, CodeContext& codeContext)
{
  std::string decodedVar, encodedVar, codesVar;
  in >> decodedVar >> encodedVar >> codesVar;

  if (context.context.find(encodedVar) == context.context.end() || codeContext.codeContext.find(codesVar) == codeContext.codeContext.end())
  {
    out << "<INVALID DECOMPRESSION>" << '\n';
    return;
  }

  std::string encodedText = context.context[encodedVar];
  std::map< char, std::string > huffmanCodes = codeContext.codeContext[codesVar];
  std::string decodedText;

  if (decompressText(encodedText, huffmanCodes, decodedText))
  {
    context.context[decodedVar] = decodedText;
    out << "Text decompressed into " << decodedVar << "\n";
  }
  else
  {
    out << "<INVALID DECOMPRESSION>\n";
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
  size_t originalBits = text.size() * 8;
  size_t compressedBits = 0;

  for (char ch : text)
  {
    compressedBits += huffmanCodes[ch].size();
  }

  out << "Original size: " << originalBits << " bits\n";
  out << "Compressed size: " << compressedBits << " bits\n";
  out << "Compression efficiency: " << static_cast< double >(compressedBits) / originalBits * 100 << "%\n";
}

void skuratov::sortData(std::istream& in, std::ostream& out, Context& context)
{}

void skuratov::removeDuplicates(std::istream& in, std::ostream& out, Context& context)
{}

void skuratov::countWords(std::istream& in, std::ostream& out, Context& context)
{}

