#include "dataStruct.hpp"
#include "delimeterI.hpp"
#include "parseFunctions.hpp"

std::istream& dataStruct::operator>>(std::istream& in, DataStruct& value)
{
	std::istream::sentry guard(in);
	if (!in)
	{
		return in;
	}
	using cDel = delimeterI::DelimeterI;
	DataStruct temp{ 0, {0, 0}, "" };
	std::string key;
	in >> cDel{ '(' } >> cDel{ ':' };
	for (short i = 0; i < 3; ++i)
	{
		std::getline(in, key, ' ');
		if (key == "key1")
		{
			parseSignedLL(in, temp.key1);
		}
		else if (key == "key2")
		{
			parseComplex(in, temp.key2);
		}
		else if (key == "key3")
		{
			in >> cDel{ '"' };
			std::getline(in, temp.key3, '"');
		}
		in >> cDel{ ':' };
	}
	in >> cDel{ ')' };
	if (in)
	{
		value = temp;
	}
	return in;
}