#include<iostream>
#include<string>
#include <algorithm>
#include<cstring>

using namespace feofanova;

void CreateER(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
void CreateRE(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
std::string FindER(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
std::string FindRE(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
void DeleteER(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
void DeleteRE(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
void Flip(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
void Flitter(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
void FullCompare(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
void PartCompare(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
void doUnion(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
void doCross(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
void doExtend(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
void doReduce(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
void FullPrint(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
void PartPrint(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);