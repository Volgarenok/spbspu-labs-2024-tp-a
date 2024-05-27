#include "ownCmds.hpp"

void skuratov::help(std::ostream& out)
{
  setlocale(LC_ALL, "Russian");
  out << "load <text1> <text1.txt> - загрузка незашифрованного текста из файла\n";
  out << "huff <codes1> <text1> - создание кодировки дл€ не зашифрованного текста\n";
  out << "compress <encoded1> <text1> <codes1> - сжатие текста\n";
  out << "save <encoded1> <output1.bin> - сохранение данных\n";
  out << "load_encoded <text3> <codes1> <output1.bin> - загрузка зашифрованного текста из файла\n";
  out << "decompress <decoded1> <text3> <codes1> -  раскодирование сжатого файла\n";
  out << "eff text1 codes1 - вывод эффективности сжати€ текста\n";
  out << "sort_data <encoded1> - сортировка данных\n";
  out << "remove_duplicates <text1> - удаление повтор€ющихс€ слов из текста\n";
  out << "count_words <text1> - подсчет количества слов в тексте\n";
}

void skuratov::load()
{}

void skuratov::huff()
{}

void skuratov::compress()
{}

void skuratov::save()
{}

void skuratov::loadEncoded()
{}

void skuratov::decompress()
{}

void skuratov::eff()
{}

void skuratov::sortData()
{}

void skuratov::removeDuplicates()
{}

void skuratov::countWords()
{}
