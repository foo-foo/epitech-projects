//
// Command.cpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/srcs
//
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
//
// Started on  Wed Apr 15 21:36:40 2015 Anatole Menichetti
// Last update Sun Apr 26 16:07:42 2015 Anatole Menichetti
//
#include <iostream>
#include "Command.hpp"

Command::Command(PizzaSize const &size, PizzaType const &type) :
  _kitchen(0), _cook(0), _size(size), _type(type)
{
}

Command::Command(t_cmd &cmd) :
  _kitchen(cmd.kitchen), _cook(cmd.cook), _size(cmd.size), _type(cmd.type)
{
}

Command::~Command()
{
}

/* ---------------- */
/* Public functions */
/* ---------------- */

PizzaSize	Command::getSize() const
{
  return (_size);
}

PizzaType	Command::getType() const
{
  return (_type);
}

t_cmd		Command::getCmd() const
{
  t_cmd		ret;

  ret.kitchen = _kitchen;
  ret.cook =  _cook;
  ret.size = _size;
  ret.type = _type;
  return (ret);
}

void		Command::setKitchen(size_t const kitchen)
{
  _kitchen = kitchen;
}
void		Command::setCook(size_t const cook)
{
  _cook = cook;
}

size_t		Command::getKitchen() const
{
  return (_kitchen);
}
size_t		Command::getCook() const
{
  return (_cook);
}
