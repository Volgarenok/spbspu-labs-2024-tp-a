#include "commands.hpp"
#include <iostream>

namespace rav = ravinskij;

void rav::printHelp()
{
}

void rav::addText(std::istream& in, fileTable& files)
{
}

void rav::saveText(std::istream& in, fileTable& files)
{
}

void rav::deleteText(std::istream& in, fileTable& files)
{
}

void rav::printText(std::istream& in, std::ostream& out, const fileTable& files)
{
}

void rav::createEncoding(std::istream& in, encodesTable& encodings, traverserTable& traverses, const fileTable& files)
{
}

void rav::deleteEncoding(std::istream& in, encodesTable& encodings, traverserTable& traverses)
{
}

void rav::encode(std::istream& in, const encodesTable& encodings, fileTable& files)
{
}

void rav::decode(std::istream& in, const traverserTable& traverses, fileTable& files)
{
}

void rav::addEncoding(std::istream& in, encodesTable& encodings)
{
}

void rav::saveEncoding(std::istream& in, encodesTable& encodings)
{
}

void rav::compareEncodings(std::istream& in, const encodesTable& encodings)
{
}
