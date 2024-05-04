#include <iostream>
#include <limits>
#include <functional>
#include <map>

namespace skuratov
{
	void cmd1(std::istream& in, std::ostream& out)
	{
		out << "Hi, this is CMD1" << '\n';
	}
	void cmd2(std::istream& in, std::ostream& out)
	{
		out << "Hi, this is CMD2" << '\n';
	}
}

int main()
{
	std::string cmd;
	while (std::cin >> cmd)
	{
		if (cmd == "CMD1")
		{
			skuratov::cmd1(std::cin, std::cout);
		}
		else if (cmd == "CMD2")
		{
			skuratov::cmd2(std::cin, std::cout);
		}
		else
		{
			std::cerr << "INVALID COMMAND\n";
		}
	}
}
