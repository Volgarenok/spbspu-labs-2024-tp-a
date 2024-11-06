#include "commands.hpp"
#include <string>
#include <stdexcept>
#include <interface.hpp>
#include <delimiter.hpp>

chernikova::Commands chernikova::initializeCommands()
{
  Commands commandsSet;

  commandsSet.insert({ "AREA", getArea });
  commandsSet.insert({ "MAX", getMax });
  commandsSet.insert({ "MIN", getMin });
  commandsSet.insert({ "COUNT", getCount });
  commandsSet.insert({ "ECHO", echoDuplicate });
  commandsSet.insert({ "INTERSECTIONS", getIntersections });
  commandsSet.insert({ "RIGHTSHAPES", getRightShapes });

  return commandsSet;
}

void chernikova::doCommand(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  StreamGuard streamGuard(in);
  in.unsetf(std::ios_base::skipws);

  static Commands functions = initializeCommands();

  std::string command;
  in >> command;

  if (!in)
  {
    throw std::invalid_argument("Команда не была считана.");
  }

  try
  {
    functions.at(command)(polygons, out, in);
  }
  catch (const std::out_of_range& error)
  {
    handleError(in, out);
  }
  catch (const std::invalid_argument& error)
  {
    printError(out);
  }
  catch (const std::length_error& error)
  {
    printEmptyError(out);
  }
  catch (const std::domain_error& error)
  {
    printError(out);
    in.clear();
  }
}

void chernikova::getArea(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  std::string subcommand;
  in >> ExactSymbolI{ ' ' } >> subcommand >> ExactSymbolI{ '\n' };

  if (!in)
  {
    throw std::out_of_range("Ошибка чтения подкоманды AREA.");
  }

  if (subcommand == "EVEN")
  {
    getAreaEven(polygons, out);
  }
  else if (subcommand == "ODD")
  {
    getAreaOdd(polygons, out);
  }
  else if (subcommand == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument(
        "Нельзя подсчитать среднее арифметическое площадей для пустого множества.");
    }

    getAreaMean(polygons, out);
  }
  else
  {
    size_t count = 0;

    try
    {
      size_t numberOfSymbols;
      count = std::stoull(subcommand, &numberOfSymbols);
    }
    catch (const std::invalid_argument& error)
    {
      throw std::invalid_argument("Была введена несуществующая подкоманда.");
    }
    catch (const std::out_of_range& error)
    {
      throw std::invalid_argument("Введенное значение было некорректно.");
    }

    if (count < 3)
    {
      throw std::invalid_argument("Количество вершин полигона не может быть меньше трех.");
    }
    getAreaVertexes(polygons, count, out);
  }
}

void chernikova::getMax(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  std::string subcommand;
  in >> ExactSymbolI{ ' ' } >> subcommand >> ExactSymbolI{ '\n' };

  if (!in)
  {
    throw std::out_of_range("Ошибка чтения подкоманды GETMAX.");
  }

  if (polygons.empty())
  {
    throw std::invalid_argument("Нельзя найти максимальное значение для пустого множества.");
  }

  if (subcommand == "AREA")
  {
    getMaxArea(polygons, out);
  }
  else if (subcommand == "VERTEXES")
  {
    getMaxVertexes(polygons, out);
  }
  else
  {
    throw std::invalid_argument("Была введена несуществующая подкоманда.");
  }
}

void chernikova::getMin(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  std::string subcommand;
  in >> ExactSymbolI{ ' ' } >> subcommand >> ExactSymbolI{ '\n' };

  if (!in)
  {
    throw std::out_of_range("Ошибка чтения подкоманды GETMIN.");
  }

  if (polygons.empty())
  {
    throw std::invalid_argument("Нельзя найти минимальное значение для пустого множества.");
  }

  if (subcommand == "AREA")
  {
    getMinArea(polygons, out);
  }
  else if (subcommand == "VERTEXES")
  {
    getMinVertexes(polygons, out);
  }
  else
  {
    throw std::invalid_argument("Была введена несуществующая подкоманда.");
  }
}

void chernikova::getCount(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  std::string subcommand;
  in >> ExactSymbolI{ ' ' } >> subcommand >> ExactSymbolI{ '\n' };

  if (!in)
  {
    throw std::out_of_range("Ошибка чтения подкоманды GETCOUNT.");
  }

  if (subcommand == "EVEN")
  {
    getCountEven(polygons, out);
  }
  else if (subcommand == "ODD")
  {
    getCountOdd(polygons, out);
  }
  else
  {
    size_t count = 0;

    try
    {
      size_t numberOfSymbols;
      count = std::stoull(subcommand, &numberOfSymbols);
    }
    catch (const std::invalid_argument& error)
    {
      throw std::invalid_argument("Была введена несуществующая подкоманда.");
    }
    catch (const std::out_of_range& error)
    {
      throw std::invalid_argument("Введенное значение было некорректно.");
    }

    if (count < 3)
    {
      throw std::invalid_argument("Количество вершин полигона не может быть меньше трех.");
    }

    getCountVertexes(polygons, count, out);
  }
}

void chernikova::echoDuplicate(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  Polygon polygon;
  in >> ExactSymbolI{ ' ' };

  if (!in)
  {
    throw std::out_of_range("Ошибка чтения команды ECHO.");
  }

  in >> polygon;

  if (!in)
  {
    throw std::domain_error("Неправильный формат ввода полигона.");
  }

  echo(polygons, polygon, out);
}

void chernikova::getIntersections(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  Polygon polygon;
  in >> ExactSymbolI{ ' ' };

  if (!in)
  {
    throw std::out_of_range("Ошибка чтения команды INTERSECTIONS.");
  }

  in >> polygon;

  if (!in)
  {
    throw std::domain_error("Неправильный формат ввода полигона.");
  }

  if (polygons.empty())
  {
    throw std::invalid_argument("Нельзя найти прямые углы для несуществующего полигона.");
  }

  intersections(polygons, polygon, out);
}

void chernikova::getRightShapes(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  in >> ExactSymbolI{ '\n' };

  if (!in)
  {
    throw std::out_of_range("Ошибка чтения команды RIGHTSHAPES.");
  }

  if (polygons.empty())
  {
    throw std::invalid_argument("Нельзя найти прямые углы для несуществующего полигона.");
  }

  rightShapes(polygons, out);
}
