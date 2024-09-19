#include "Commands.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

#include "Utility.hpp"

struct isName
{
  bool operator()(const stepanchenko::CrossRefs & cross_refs, const std::string& name)
  {
    return cross_refs.getName() == name;
  }
};

void stepanchenko::create_tableCmd(std::vector< CrossRefs > cross_refs, std::istream& in)
{
  std::string tableName, file;
  in >> tableName >> file;
  using namespace std::placeholders;
  auto iter = std::find_if(cross_refs.begin(), cross_refs.end(), std::bind(isName(), _1, tableName));
  if (iter == cross_refs.end())
  {
    iter->createTable(tableName, file);
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND");
  }
}

void stepanchenko::add_to_tableCmd(std::vector< CrossRefs > cross_refs, std::istream& in)
{

}

void stepanchenko::get_intersectionCmd(std::vector< CrossRefs > cross_refs, std::istream& in)
{

}
