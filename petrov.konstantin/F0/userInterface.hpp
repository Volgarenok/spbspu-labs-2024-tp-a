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

    std::ostream& readText(std::istream& in, std::ostream& out);
    std::ostream& writeText(std::istream& in, std::ostream& out);
    std::ostream& deleteText(std::istream& in, std::ostream& out);
    std::ostream& decode(std::istream& in, std::ostream& out);
    std::ostream& encode(std::istream& in, std::ostream& out);
    setType& autoCodes(std::istream& in, std::ostream& out);
  };
}

#endif
