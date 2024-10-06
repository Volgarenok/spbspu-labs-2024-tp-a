#include "Utility.hpp"

void stepanchenko::checkName(std::vector< CrossRefs >& cross_refs, const std::string& name)
{
  auto iter = std::find_if(cross_refs.begin(), cross_refs.end(), [&](CrossRefs& cr) {
    return cr.getName() == name;
  });

  if (iter == cross_refs.end())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void stepanchenko::printL(const std::pair < size_t, std::string >& line, std::ostream& out)
{
  out << line.first << ' ' << line.second << '\n';
}

void stepanchenko::writeToFile(const std::string & name,
  const std::vector< std::pair< size_t, std::string > >& lines, std::ofstream& file)
{
  file << "--------Beginning of the table--------\n";
  file << name << '\n';

  for (const auto& line : lines)
  {
    file << line.first << ' ' << line.second << "\n";
  }

  file << "------------End of table------------\n";
}

bool stepanchenko::isInIntersection(std::pair < std::string,
  std::list< size_t > > entry, CrossRefs& cr)
{
  return cr.search(entry.first) == cr.end();
}

std::vector<stepanchenko::CrossRefs> stepanchenko::createCrossRefsFromFile(std::istream& fin)
{
  std::vector<CrossRefs> cross_refs;

  while (!fin.eof())
  {
    std::string line;

    while (std::getline(fin, line))
    {
      CrossRefs cr;
      if (line == "--------Beginning of the table--------")
      {
        fin >> cr;
      }
      else
      {
        throw std::logic_error("<INVALID COMMAND>");
      }

      cross_refs.push_back(cr);
    }
  }

  return cross_refs;
}

void stepanchenko::helpCmd(std::ostream& out)
{
  out << "--CREATE <table name> <file name>\n";
  out << "\tCreates cross-references table named <table name> based ";
  out << "on \n\ttext data from the <filename> file.\n";
  out << "--ADDTOTABLE <table name> <file name>\n";
  out << "\tAdds cross-references to the existing <table name> table based ";
  out << "\n\ton data from the <file name> file.\n";
  out << "--GETINTERSECTION <new table name> <table1 name> <table2 name>  \n";
  out << "\tCreate a new table named <new table name>, which will store ";
  out << "\n\tcross-references for words present in both <table1 name> and <table2 name>.\n";
  out << "--PRINTLINES <word> <table name>\n";
  out << "\tPrints all lines from <table name> in which the word <word> occurs.\n";
  out << "--PRINT <table name>\n";
  out << "\tPrints the text in numbered lines according to the cross-references ";
  out << "\n\tfrom the <table name> table.\n";
  out << "--DELETELINES <word> <table name> <file name> \n";
  out << "\tDeletes all lines with the word <word> from the file <filename> ";
  out << "according \n\tto the cross-references from the table <table name>.\n";
  out << "--MOVEDOWN <word> <table name> <result_file name>\n";
  out << "\tMove all lines containing the word <word> to the beginning of the ";
  out << "document \n\t<result_filename> in their order, according to the cross-references ";
  out << "from the \n\ttable <table name>.\n";
  out << "--GETSELECTION <word1> <word2> <table name> <result_file name> \n";
  out << "\tSelects only those lines in which both words <word1> and <word2> occur, ";
  out << "\n\tand write the result to the <result_filename> file. \n";
  out << "--VIEW\n";
  out << "\tPrints all tables available\n";
  out << "--SAVE <file name>\n";
  out << "\tSaves all tables in file <file name>\n";
}
