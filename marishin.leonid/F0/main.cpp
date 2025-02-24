#include "NotebookManager.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <map>
#include <limits>

void printHelp();
void executeAddNote(NotebookManager& manager, std::istream& is);
void executeRemoveNote(NotebookManager& manager, std::istream& is);
void executeCreateNotebook(NotebookManager& manager, std::istream& is);
void executeCreateTag(NotebookManager& manager, std::istream& is);
void executeDeleteTag(NotebookManager& manager, std::istream& is);
void executeAddTagToNote(NotebookManager& manager, std::istream& is);
void executeRemoveTagFromNote(NotebookManager& manager, std::istream& is);
void executeCreateNotebookFromTags(NotebookManager& manager, std::istream& is);
void executeMergeNotebooksByTags(NotebookManager& manager, std::istream& is);
void executeSortEntriesByTag(NotebookManager& manager, std::istream& is);

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Invalid command line arguments\n";
    return 1;
  }
  std::ifstream in(argv[1]);
  if (!in.is_open())
  {
    std::cerr << "Unable to open file\n";
    return 1;
  }

  NotebookManager manager;
  std::map<std::string, std::function<void(std::istream&, std::ostream&)>> cmds;
  using namespace std::placeholders;
  cmds["add"] = std::bind(executeAddNote, std::ref(manager), _1);
  cmds["remove"] = std::bind(executeRemoveNote, std::ref(manager), _1);
  cmds["create"] = std::bind(executeCreateNotebook, std::ref(manager), _1);
  cmds["tag-create"] = std::bind(executeCreateTag, std::ref(manager), _1);
  cmds["tag-delete"] = std::bind(executeDeleteTag, std::ref(manager), _1);
  cmds["tag-add"] = std::bind(executeAddTagToNote, std::ref(manager), _1);
  cmds["tag-remove"] = std::bind(executeRemoveTagFromNote, std::ref(manager), _1);
  cmds["tag-create-book"] = std::bind(executeCreateNotebookFromTags, std::ref(manager), _1);
  cmds["tag-merge-books"] = std::bind(executeMergeNotebooksByTags, std::ref(manager), _1);
  cmds["tag-sort-entries"] = std::bind(executeSortEntriesByTag, std::ref(manager), _1);

  std::string command;
  while (std::getline(in, command))
  {
    try
    {
      std::istringstream cmd_stream(command);
      std::string cmd;
      cmd_stream >> cmd;
      auto it = cmds.find(cmd);
      if (it != cmds.end())
      {
        it->second(cmd_stream, std::cout);
      }
      else
      {
        throw std::runtime_error("INVALID COMMAND");
      }
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return 0;
}
