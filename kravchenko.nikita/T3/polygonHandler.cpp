#include "polygonHandler.hpp"
#include <iterator>
#include <limits>
#include "polygonCommands.hpp"

void kravchenko::PolygonHandler::inputPolygons(std::istream& in)
{
  using inputIt = std::istream_iterator< Polygon >;
  while (!in.eof())
  {
    std::copy(inputIt{ in }, inputIt{}, std::back_inserter(data_));
    in.clear();
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}

void kravchenko::PolygonHandler::handleCommands(std::istream& cmdIn, std::ostream& cmdOut)
{
  auto& commandsMap = PolygonHandler::getCommandsMap();
  std::string commandName;
  cmdIn >> commandName;
  while (!cmdIn.eof())
  {
    try
    {
      auto commandFunctor = commandsMap.at(commandName);
      commandFunctor(data_, cmdIn, cmdOut);
    }
    catch (const std::out_of_range&)
    {
      cmdOut << "<INVALID COMMAND>" << '\n';
    }
    catch (const InvalidCommand& e)
    {
      cmdOut << e.what() << '\n';
    }
    catch (...)
    {
      throw;
    }
    cmdIn.clear();
    cmdIn.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    cmdIn >> commandName;
  }
}

const std::map< std::string, std::function< void(std::vector< kravchenko::Polygon >&, std::istream&, std::ostream&) > >&
kravchenko::PolygonHandler::getCommandsMap()
{
  using namespace std::placeholders;
  static std::map< std::string,
                   std::function< void(std::vector< kravchenko::Polygon >&, std::istream&, std::ostream&) > >
    commands{
      { "AREA", Area{} }
    };
  return commands;
}

const char* kravchenko::InvalidCommand::what() const noexcept
{
  return "<INVALID COMMAND>";
}
