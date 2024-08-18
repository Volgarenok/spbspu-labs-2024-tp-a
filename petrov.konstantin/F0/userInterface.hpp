#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include <map>
#include <string>
#include "utils.hpp"

namespace petrov
{
  class UserInterface
  {
    public:
    void readCommand(std::istream& in, std::ostream& out);

    private:
    std::map< std::string, std::string > texts_;
    std::map< std::string, setType > codes_;

    void readText(std::istream& in, std::ostream& out);
    void writeText(std::istream& in);
    void deleteText(std::istream& in);
    void decode(std::istream& in);
    void encode(std::istream& in);
    void autoCodes(std::istream& in);
    void readCodes(std::istream& in);
    void writeCodes(std::istream& in);
    void getSize(std::istream& in, std::ostream& out);
    void compareSizes(std::istream& in, std::ostream& out);
    void output(std::istream& in, std::ostream& out);
    void help(std::ostream& out);
    size_t getSizeOfFile(const std::string& file);
  };
}

#endif
