//
// Parser.cpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/srcs
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Wed Apr 15 22:08:59 2015 Anatole Menichetti
// Last update Thu Apr 23 10:57:25 2015 Anatole Menichetti
//

#include <sstream>
#include <algorithm>
#include "../includes/Parser.hpp"
#include "../includes/ArgError.hpp"

Parser::Parser(int ac, char **av)
{
  if (ac != PARAMS_NBR)
    throw(ArgError("usage", std::string(av[0]) + " [COOKING TIME] [COOKS NUMBER] [REPLACE TIME]" ));

  _multiplier = getDouble(std::string(av[1]));
  _cooksNbr = getInteger(std::string(av[2]));
  _replaceTime = getInteger(std::string(av[3]));
}

Parser::~Parser()
{}

/* ----------------- */
/* Private functions */
/* ----------------- */

double	Parser::getDouble(std::string const &data) const
{
  if (data.find_first_not_of("0123456789.") != std::string::npos ||
      std::count(data.begin(), data.end(), '.') > 1)
    throw(ArgError("syntax", "invalid parameter: " + data));

  double		d;
  std::istringstream	is(data);

  is >> d;
  return (d);
}

size_t	Parser::getInteger(std::string const &data) const
{
  if (data.find_first_not_of("0123456789") != std::string::npos)
    throw(ArgError("syntax", "invalid parameter: " + data));

  size_t		i;
  std::istringstream	is(data);

  is >> i;
  return (i);
}

/* ---------------- */
/* Public functions */
/* ---------------- */

double	Parser::getMultiplier() const
{
  return (_multiplier);
}

size_t	Parser::getCooksNbr() const
{
  return (_cooksNbr);
}

size_t	Parser::getReplaceTime() const
{
  return (_replaceTime);
}
