#ifndef COMMANDS_HPP
#define COMMANDS_HPP

namespace sakovskaia
{
  void newCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output);
  void deleteCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output);
  void loadCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output);
  void addCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output);
  void saveCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output);
  void removeCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output);
  void frequencyCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output);
  void updateCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output);
  void combiningCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output);
  void diffCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output);
};

#endif
