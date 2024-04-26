#include <iostream>
#include <map>
#include <functional>

namespace feofanova
{
    void lessarea(const int&, std::istream&, std::ostream& out)
    {
        out << "lessarea dispatched\n";
    }
    void perms(const int&, std::istream&, std::ostream& out)
    {
        out << "perms dispatched\n";
    }
}

int main()
{
    std::string cmd;
    int context = 0;
    std::map< std::string, std::function< void(const int&, std::istream&, std::ostream&) > > const_cmds;
    const_cmds["lessarea"] = poly::lessarea;
    const_cmds["perms"] = poly::perms;

    while (std::cin >> cmd)
    {
        try
        {
            const_cmds.at(cmd)(context, std::cin, std::cout);
        }
        catch (const std::out_of_range&)
        {
        }
        try
        {
            cmds.at(cmd)(context, std::cin, std::cout);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}
