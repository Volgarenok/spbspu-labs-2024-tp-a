#include "comlinearg.hpp"
#include "commands.hpp"

void piyavkin::help(std::ostream& out)
{
  out << "Room system\n1. adddictionary <dictionary name> - create an object named <dictionary name>\n";
  out << "2. changedictionary <dictionary name> <key> <value> - change the dictionary\n";
  out << "3. makedictionary <dictionary name> <file.txt> - build a dictionary from a text file\n";
  out << "4. topfreq <dictionary name> <n> - display top n frequently occurring values\n";
  out << "5. intersectdictionaries <new dictionary name> <dictionary name1> <dictionary name2> - find the"
      << "intersection of dictionaries.\n";
  out << "6. uniondictionaries <new dictionary name> <dictionary name1> <dictionary name2> - find unions of dictionaries\n";
  out << "7. uniquedictionaries <new dictionary name> <dictionary name1> <dictionary name2> - find and"
      << "save in <new dictionary name> all the keys that are in <dictionary name1>, but not in <dictionary name2>, and"
      << "their values\n";
  out << "8. adddictionarytodictionary <dictionary name1> <dictionary name2> - add to <dictionary name1>"
      << " all missing keys and their values\n";
  out << "9. subdictionarytodictionary <dictionary name1> <dictionary name2> - subtract from"
      << " <dictionary name1> <dictionary name2>\n";
  out << "10. printdictionary <dictionary name> <file.txt> - write the dictionary to a text file\n";
}

void piyavkin::check(std::istream& in, std::ostream& out, dic_t& dicts)
{
  input(in, dicts);
  if (!in.bad())
  {
    out << "GOOD FILE\n";
  }
  else
  {
    out << "BAD FILE\n";
  }
}
