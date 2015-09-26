//
// Order.cpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/srcs
//
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
//
// Started on  Wed Apr 15 21:55:52 2015 Anatole Menichetti
// Last update Sun Apr 26 16:36:37 2015 Anatole Menichetti
//

#include <algorithm>
#include "Order.hpp"
#include "RuntimeError.hpp"
#include "BadCommandError.hpp"

void	lowerCase(char &c)
{
  if (c >= 'A' && c <= 'Z')
    c += 32;
}

Order::Order(std::map<std::string, PizzaSize>& mPizzaSize,
	     std::map<std::string, PizzaType>& mPizzaType)
{
  std::string	        line;
  std::string		command;
  size_t		pos = 0;
  size_t		len = 0;

  std::getline(std::cin, line);
  if (line.empty())
    throw (RuntimeError("read", "EOF have been reached"));
  while (pos < line.size())
    {
      if ((len = line.find_first_of(";\0", pos)) == std::string::npos)
	len = line.size() - pos;
      command = line.substr(pos, len);
      std::for_each(command.begin(), command.end(), lowerCase);
      _createCommand(command, mPizzaSize, mPizzaType);
      pos += (len + 1);
    }
}

Order::~Order()
{}

/* ------------------ */
/* Privates Functions */
/* ------------------ */

size_t		Order::checkCommand(std::string const &command,
				    PizzaSize &pizza_size,
				    PizzaType &pizza_type,
				    std::map<std::string, PizzaSize>& mPizzaSize,
				    std::map<std::string, PizzaType>& mPizzaType) const
{
  std::string	info;
  size_t	pos_start = 0;
  size_t	pos_end = 0;
  size_t	cpt = 0;

  while (cpt < 2)
    {
      if ((pos_start = command.find_first_not_of(" \t", pos_start)) == std::string::npos)
	throw (BadCommandError("bad command", "empty command"));
      if ((pos_end = command.find_first_of(" \t", pos_start)) == std::string::npos
	  || (info = command.substr(pos_start, pos_end - pos_start)).empty())
	throw (BadCommandError("bad command", "syntax error in command line"));
      if ((cpt == 0 && (pizza_type = mPizzaType[info]) == 0))
	throw (BadCommandError("bad command", "unknown pizza type " + info));
      if ((cpt == 1 && (pizza_size = mPizzaSize[info]) == 0))
	throw (BadCommandError("bad command", "unknown pizza size " + info));
      pos_start += (pos_end - pos_start + 1);
      cpt++;
    }
  if ((pos_start = command.find_first_of("x", pos_start)) == std::string::npos)
    throw (BadCommandError("bad command", "please specify number of pizzas"));
  return (pos_start);
}

void	Order::_createCommand(std::string const &command,
			      std::map<std::string, PizzaSize>& mPizzaSize,
			      std::map<std::string, PizzaType>& mPizzaType)
{
  PizzaSize		pizza_size;
  PizzaType		pizza_type;
  size_t		nb_commands;
  size_t		pos_start = checkCommand(command, pizza_size, pizza_type, mPizzaSize, mPizzaType);
  size_t		pos_end = command.find_first_not_of("0123456789", ++pos_start);
  std::istringstream	iss(command.substr(pos_start, pos_end - pos_start));

  iss >> nb_commands;
  while (nb_commands--)
    _order.push(new Command(pizza_size, pizza_type));
}

/* ---------------- */
/* Public functions */
/* ---------------- */

std::queue<Command*>&	Order::getOrder()
{
  return (_order);
}
