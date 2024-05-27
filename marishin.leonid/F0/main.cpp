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

  Note(const std::string& k, const std::string& d):
    key(k),
    description(d)
  {}

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
    notes[key] = Note{key, note};
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
    for (auto& [key, note] : notes)
    {
      note.removeTag(tag);
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

  std::vector<Note> getNotesByTag(const std::string& tag) const
  {
    std::vector<Note> result;
    for (const auto& [key, note] : notes)
    {
      if (note.tags.find(tag) != note.tags.end())
      {
        result.push_back(note);
      }
    }
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

  void createNotebookFromTags(const std::string& book1, const std::string& tag1, const std::string& book2, const std::string& tag2, const std::string& newBook)
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
    for (const auto& [key, note1] : it1->second.notes)
    {
      for (const auto& [key, note2] : it2->second.notes)
      {
        std::vector<std::string> common_tags;
        std::set_intersection(note1.tags.begin(), note1.tags.end(), note2.tags.begin(), note2.tags.end(), std::back_inserter(common_tags));
        if (!common_tags.empty())
        {
          notebooks[newBook].add(note1.key, note1.description);
        }
      }
    }
  }

  void sortEntriesByTag(const std::string& book, const std::string& tag)
  {
    auto it = notebooks.find(book);
    if (it == notebooks.end())
    {
      throw std::runtime_error("INVALID COMMAND");
    }
    auto notes = it->second.getNotesByTag(tag);
    auto other_notes = it->second.notes;
    for (const auto& note : notes)
    {
      other_notes.erase(note.key);
    }
    std::vector<Note> sorted_notes(notes.begin(), notes.end());
    sorted_notes.insert(sorted_notes.end(), other_notes.begin(), other_notes.end());
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

void executeAddNote(NotebookManager& manager, std::istream& is, std::ostream& os)
{
  std::string book, key, note;
  is >> book >> key;
  std::getline(is, note);
  manager.addNote(book, key, note);
}

void executeRemoveNote(NotebookManager& manager, std::istream& is, std::ostream& os)
{
  std::string book, key;
  is >> book >> key;
  manager.removeNote(book, key);
}

void executeCreateNotebook(NotebookManager& manager, std::istream& is, std::ostream& os)
{
  std::string book;
  is >> book;
  manager.createNotebook(book);
}

void executeCreateTag(NotebookManager& manager, std::istream& is, std::ostream& os)
{
  std::string book, tag;
  is >> book >> tag;
  manager.createTag(book, tag);
}

void executeDeleteTag(NotebookManager& manager, std::istream& is, std::ostream& os)
{
  std::string book, tag;
  is >> book >> tag;
  manager.deleteTag(book, tag);
}

void executeAddTagToNote(NotebookManager& manager, std::istream& is, std::ostream& os)
{
  std::string book, key, tag;
  is >> book >> key >> tag;
  manager.addTagToNote(book, key, tag);
}

void executeRemoveTagFromNote(NotebookManager& manager, std::istream& is, std::ostream& os)
{
  std::string book, key, tag;
  is >> book >> key >> tag;
  manager.removeTagFromNote(book, key, tag);
}

void executeCreateNotebookFromTags(NotebookManager& manager, std::istream& is, std::ostream& os)
{
  std::string book1, tag1, book2, tag2, newBook;
  is >> book1 >> tag1 >> book2 >> tag2 >> newBook;
  manager.createNotebookFromTags(book1, tag1, book2, tag2, newBook);
}

void executeMergeNotebooksByTags(NotebookManager& manager, std::istream& is, std::ostream& os)
{
  std::string book1, book2, newBook;
  is >> book1 >> book2 >> newBook;
  manager.mergeNotebooksByTags(book1, book2, newBook);
}

void executeSortEntriesByTag(NotebookManager& manager, std::istream& is, std::ostream& os)
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

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;

  using namespace std::placeholders;
  cmds["add"] = std::bind(executeAddNote, std::ref(manager), _1, _2);
  cmds["remove"] = std::bind(executeRemoveNote, std::ref(manager), _1, _2);
  cmds["create"] = std::bind(executeCreateNotebook, std::ref(manager), _1, _2);
  cmds["tag-create"] = std::bind(executeCreateTag, std::ref(manager), _1, _2);
  cmds["tag-delete"] = std::bind(executeDeleteTag, std::ref(manager), _1, _2);
  cmds["tag-add"] = std::bind(executeAddTagToNote, std::ref(manager), _1, _2);
  cmds["tag-remove"] = std::bind(executeRemoveTagFromNote, std::ref(manager), _1, _2);
  cmds["tag-create-book"] = std::bind(executeCreateNotebookFromTags, std::ref(manager), _1, _2);
  cmds["tag-merge-books"] = std::bind(executeMergeNotebooksByTags, std::ref(manager), _1, _2);
  cmds["tag-sort-entries"] = std::bind(executeSortEntriesByTag, std::ref(manager), _1, _2);

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
}
