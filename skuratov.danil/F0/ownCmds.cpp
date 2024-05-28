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

void skuratov::load(std::istream& in, std::ostream& out)
{}

void skuratov::huff(std::istream& in, std::ostream& out)
{}

void skuratov::compress(std::istream& in, std::ostream& out)
{}

void skuratov::save(std::istream& in, std::ostream& out)
{}

void skuratov::loadEncoded(std::istream& in, std::ostream& out)
{}

void skuratov::decompress(std::istream& in, std::ostream& out)
{}

void skuratov::eff(std::istream& in, std::ostream& out)
{}

void skuratov::sortData(std::istream& in, std::ostream& out)
{}

void skuratov::removeDuplicates(std::istream& in, std::ostream& out)
{}

void skuratov::countWords(std::istream& in, std::ostream& out)
{}
