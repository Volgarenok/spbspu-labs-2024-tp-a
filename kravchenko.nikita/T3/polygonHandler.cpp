#include "polygonHandler.hpp"
#include "polygonCommands.hpp"

const char* kravchenko::InvalidCommand::what() const noexcept
{
  return "<INVALID COMMAND>";
}
