#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "commands.hpp"
#include "entities.hpp"

int main()
{
  using namespace ibragimov;
  std::shared_ptr< Entity > currentEntity = nullptr;

  std::vector< std::shared_ptr< Encodings > > encodings{};
  std::vector< std::shared_ptr< DecodedText > > decodedTexts{};
  std::vector< std::shared_ptr< EncodedText > > encodedTexts{};

  std::map< std::string, std::function< void(std::istream&) > > inputSubcommands;
  {
    using namespace std::placeholders;
    inputSubcommands["DECODED"] = std::bind(inputEntity< DecodedText >, _1, std::ref(currentEntity));
    inputSubcommands["ENCODED"] = std::bind(inputEntity< EncodedText >, _1, std::ref(currentEntity));
    inputSubcommands["ENCODINGS"] = std::bind(inputEntity< Encodings >, _1, std::ref(currentEntity));
  }
  std::map< std::string, std::function< void(std::ostream&) > > outputSubcommands;
  {
    using namespace std::placeholders;
    outputSubcommands["DECODED"] = std::bind(outputEntity< DecodedText >, _1, std::ref(currentEntity));
    outputSubcommands["ENCODED"] = std::bind(outputEntity< EncodedText >, _1, std::ref(currentEntity));
    outputSubcommands["ENCODINGS"] = std::bind(outputEntity< Encodings >, _1, std::ref(currentEntity));
  }
  std::map< std::string, std::function< void() > > saveSubcommands;
  {
    using namespace std::placeholders;
    saveSubcommands["DECODED"] = std::bind(saveEntity< DecodedText >, std::ref(decodedTexts), std::ref(currentEntity));
    saveSubcommands["ENCODED"] = std::bind(saveEntity< EncodedText >, std::ref(encodedTexts), std::ref(currentEntity));
    saveSubcommands["ENCODINGS"] = std::bind(saveEntity< Encodings >, std::ref(encodings), std::ref(currentEntity));
  }
  std::map< std::string, std::function< void(const size_t) > > deleteSubcommands;
  {
    using namespace std::placeholders;
    deleteSubcommands["DECODED"] = std::bind(deleteEntity< DecodedText >, std::ref(decodedTexts), _1);
    deleteSubcommands["ENCODED"] = std::bind(deleteEntity< EncodedText >, std::ref(encodedTexts), _1);
    deleteSubcommands["ENCODINGS"] = std::bind(deleteEntity< Encodings >, std::ref(encodings), _1);
  }
  std::map< std::string, std::function< void(const size_t) > > loadSubcommands;
  {
    using namespace std::placeholders;
    loadSubcommands["DECODED"] = std::bind(loadEntity< DecodedText >, std::ref(decodedTexts), _1, std::ref(currentEntity));
    loadSubcommands["ENCODED"] = std::bind(loadEntity< EncodedText >, std::ref(encodedTexts), _1, std::ref(currentEntity));
    loadSubcommands["ENCODINGS"] = std::bind(loadEntity< Encodings >, std::ref(encodings), _1, std::ref(currentEntity));
  }
  std::map< std::string, std::function< void(std::istream&) > > memoryCommands;
  {
    using namespace std::placeholders;
    memoryCommands["INPUT"] = std::bind(input, inputSubcommands, _1);
  }
  std::map< std::string, std::function< void(const size_t, const size_t) > > huffmanCommands;
  {
    using namespace std::placeholders;
    huffmanCommands["HUFFMAN"] = std::bind(huffman, std::ref(decodedTexts), _1, std::ref(currentEntity));
    huffmanCommands["ENCODE"] = std::bind(encode, std::ref(decodedTexts), _1, std::ref(encodings), _2, std::ref(currentEntity));
    huffmanCommands["DECODE"] = std::bind(decode, std::ref(encodedTexts), _1, std::ref(encodings), _2, std::ref(currentEntity));
  }

  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      memoryCommands.at(command)(std::cin);
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
