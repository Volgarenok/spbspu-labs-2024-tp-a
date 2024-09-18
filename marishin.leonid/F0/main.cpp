#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <sstream>
#include <iterator>
#include <fstream>
#include <limits>

class Note
{
public:
  std::string key;
  std::string description;
  std::set<std::string> tags;

  Note() = default;
  Note(const std::string& k, const std::string& d) :
    key(k),
    description(d)
  {}

  Note(const Note& other):
    key(other.key),
    description(other.description),
    tags(other.tags)
  {}

  Note& operator=(const Note& other)
  {
    if (this != &other)
    {
      key = other.key;
      description = other.description;
      tags = other.tags;
    }
    return *this;
  }

  void addTag(const std::string& tag)
  {
    tags.insert(tag);
  }

  void removeTag(const std::string& tag)
  {
    tags.erase(tag);
  }
};

class Notebook
{
public:
  std::map<std::string, Note> notes;
  std::set<std::string> tags;

  void add(const std::string& key, const std::string& note)
  {
    if (notes.find(key) != notes.end())
    {
      throw std::runtime_error("INVALID COMMAND");
    }
    notes.emplace(std::make_pair(key, Note{ key, note }));
  }

  void remove(const std::string& key)
  {
    if (notes.erase(key) == 0)
    {
      throw std::runtime_error("INVALID COMMAND");
    }
  }

  void createTag(const std::string& tag)
  {
    if (!tags.insert(tag).second)
    {
      throw std::runtime_error("INVALID COMMAND");
    }
  }

  void deleteTag(const std::string& tag)
  {
    if (tags.erase(tag) == 0)
    {
      throw std::runtime_error("INVALID COMMAND");
    }
  }

  void addTagToNote(const std::string& key, const std::string& tag)
  {
    auto it = notes.find(key);
    if (it == notes.end() || tags.find(tag) == tags.end())
    {
      throw std::runtime_error("INVALID COMMAND");
    }
    it->second.addTag(tag);
  }

  void removeTagFromNote(const std::string& key, const std::string& tag)
  {
    auto it = notes.find(key);
    if (it == notes.end() || tags.find(tag) == tags.end())
    {
      throw std::runtime_error("INVALID COMMAND");
    }
    it->second.removeTag(tag);
  }

  std::vector<Note> getNotesByTag(const std::string&) const
  {
    std::vector<Note> result;
    return result;
  }
};

class NotebookManager
{
public:
  std::map<std::string, Notebook> notebooks;

  void createNotebook(const std::string& name)
  {
    if (!notebooks.emplace(name, Notebook{}).second)
    {
      throw std::runtime_error("INVALID COMMAND");
    }
  }

  void addNote(const std::string& book, const std::string& key, const std::string& note)
  {
    auto it = notebooks.find(book);
    if (it == notebooks.end())
    {
      throw std::runtime_error("INVALID COMMAND");
    }
    it->second.add(key, note);
  }

  void removeNote(const std::string& book, const std::string& key)
  {
    auto it = notebooks.find(book);
    if (it == notebooks.end())
    {
      throw std::runtime_error("INVALID COMMAND");
    }
    it->second.remove(key);
  }

  void createTag(const std::string& book, const std::string& tag)
  {
    auto it = notebooks.find(book);
    if (it == notebooks.end())
    {
      throw std::runtime_error("INVALID BOOK");
    }
    it->second.createTag(tag);
  }

  void deleteTag(const std::string& book, const std::string& tag)
  {
    auto it = notebooks.find(book);
    if (it == notebooks.end())
    {
      throw std::runtime_error("INVALID COMMAND");
    }
    it->second.deleteTag(tag);
  }

  void addTagToNote(const std::string& book, const std::string& key, const std::string& tag)
  {
    auto it = notebooks.find(book);
    if (it == notebooks.end())
    {
      throw std::runtime_error("INVALID COMMAND");
    }
    it->second.addTagToNote(key, tag);
  }

  void removeTagFromNote(const std::string& book, const std::string& key, const std::string& tag)
  {
    auto it = notebooks.find(book);
    if (it == notebooks.end())
    {
      throw std::runtime_error("INVALID COMMAND");
    }
    it->second.removeTagFromNote(key, tag);
  }

  void createNotebookFromTags(const std::string& book1, const std::string& tag1, const std::string& book2,
    const std::string& tag2, const std::string& newBook)
  {
    auto it1 = notebooks.find(book1);
    auto it2 = notebooks.find(book2);
    if (it1 == notebooks.end() || it2 == notebooks.end())
    {
      throw std::runtime_error("INVALID COMMAND");
    }
    createNotebook(newBook);
    for (const auto& note : it1->second.getNotesByTag(tag1))
    {
      notebooks[newBook].add(note.key, note.description);
    }
    for (const auto& note : it2->second.getNotesByTag(tag2))
    {
      notebooks[newBook].add(note.key, note.description);
    }
  }

  void mergeNotebooksByTags(const std::string& book1, const std::string& book2, const std::string& newBook)
  {
    auto it1 = notebooks.find(book1);
    auto it2 = notebooks.find(book2);
    if (it1 == notebooks.end() || it2 == notebooks.end())
    {
      throw std::runtime_error("INVALID COMMAND");
    }
    createNotebook(newBook);
  }

  void sortEntriesByTag(const std::string& book, const std::string& tag)
  {
    auto it = notebooks.find(book);
    if (it == notebooks.end())
    {
      throw std::runtime_error("INVALID COMMAND");
    }
    auto notes = it->second.getNotesByTag(tag);
    std::vector<Note> sorted_notes(notes.begin(), notes.end());
    std::sort(sorted_notes.begin(), sorted_notes.end(), [](const Note& a, const Note& b)
    {
      return a.key < b.key;
    });
    it->second.notes.clear();
    for (const auto& note : sorted_notes)
    {
      it->second.notes[note.key] = note;
    }
  }
};

void printHelp()
{
  std::cout << "--help: Show available commands and their usage.\n";
  std::cout << "add <book> <key> <note>: Add a note with the given key and description to the book.\n";
  std::cout << "remove <book> <key>: Remove the note with the given key from the book.\n";
  std::cout << "create <book>: Create a new notebook with the given name.\n";
  std::cout << "tag-create <book> <tag>: Create a new tag in the book.\n";
  std::cout << "tag-delete <book> <tag>: Delete the tag from the book.\n";
  std::cout << "tag-add <book> <key> <tag>: Add a tag to the note with the given key in the book.\n";
  std::cout << "tag-remove <book> <key> <tag>: Remove a tag from the note with the given key in the book.\n";
  std::cout << "tag-create-book <book1> <tag1> <book2> <tag2> <new_book>: Create a new notebook based on notes tagged in the given books.\n";
  std::cout << "tag-merge-books <book1> <book2> <new_book>: Merge notes from the given books into a new book based on common tags.\n";
  std::cout << "tag-sort-entries <source_book> <tag>: Sort entries in the book by the given tag.\n";
}

void executeAddNote(NotebookManager& manager, std::istream& is)
{
  std::string book, key, note;
  is >> book >> key;
  std::getline(is, note);
  manager.addNote(book, key, note);
}

void executeRemoveNote(NotebookManager& manager, std::istream& is)
{
  std::string book, key;
  is >> book >> key;
  manager.removeNote(book, key);
}

void executeCreateNotebook(NotebookManager& manager, std::istream& is)
{
  std::string book;
  is >> book;
  manager.createNotebook(book);
}

void executeCreateTag(NotebookManager& manager, std::istream& is)
{
  std::string book, tag;
  is >> book >> tag;
  manager.createTag(book, tag);
}

void executeDeleteTag(NotebookManager& manager, std::istream& is)
{
  std::string book, tag;
  is >> book >> tag;
  manager.deleteTag(book, tag);
}

void executeAddTagToNote(NotebookManager& manager, std::istream& is)
{
  std::string book, key, tag;
  is >> book >> key >> tag;
  manager.addTagToNote(book, key, tag);
}

void executeRemoveTagFromNote(NotebookManager& manager, std::istream& is)
{
  std::string book, key, tag;
  is >> book >> key >> tag;
  manager.removeTagFromNote(book, key, tag);
}

void executeCreateNotebookFromTags(NotebookManager& manager, std::istream& is)
{
  std::string book1, tag1, book2, tag2, newBook;
  is >> book1 >> tag1 >> book2 >> tag2 >> newBook;
  manager.createNotebookFromTags(book1, tag1, book2, tag2, newBook);
}

void executeMergeNotebooksByTags(NotebookManager& manager, std::istream& is)
{
  std::string book1, book2, newBook;
  is >> book1 >> book2 >> newBook;
  manager.mergeNotebooksByTags(book1, book2, newBook);
}

void executeSortEntriesByTag(NotebookManager& manager, std::istream& is)
{
  std::string book, tag;
  is >> book >> tag;
  manager.sortEntriesByTag(book, tag);
}

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
