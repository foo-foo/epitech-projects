//
// Cook.cpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/srcs
//
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
//
// Started on  Wed Apr 15 21:38:59 2015 Anatole Menichetti
// Last update Sat Apr 25 14:53:38 2015 Sebastien Lauret
//

#include "../includes/Cook.hpp"

Cook::Cook(SafeQueue<Command *> &commands, SafeQueue<Command *> &cmdFinished,
	   double const multiplier, Resources &resources, char c, KitchenStat &kitchenstate,
	   std::map<std::string, PizzaSize> &mPizzaSize,
	   std::map<std::string, PizzaType> &mPizzaType)
  : _commands(commands),
    _cmdFinished(cmdFinished),
    _multiplier(multiplier),
    _resources(resources),
    _state(FREE), _c(c),
    _kitchenstate(kitchenstate),
    _mPizzaSize(mPizzaSize),
    _mPizzaType(mPizzaType)
{
  this->_thread.start(this, 0);
}

Cook::~Cook()
{
}

void		Cook::operator()(char)
{
  Command	*cmd;

  while (_kitchenstate != CLOSE)
    {
      if ((cmd = makePizza())!= NULL)
	{
	  cmd->setCook(_c);
	  _cmdFinished.push(cmd);
	}
    }
}

Command*	Cook::makePizza()
{
  Command	*cmd;
  PizzaType	type;

  if (!this->_commands.tryPop(&cmd))
    return (NULL);
  _state = BUSY;
  while (this->_resources.takeResources(cmd->getType()));
  type = cmd->getType();
  if (type == Margarita || type == Fantasia)
    usleep(1000000 * type / 2 * _multiplier);
  else
    usleep(1000000 * 2 * _multiplier);
  _state = FREE;
  return (cmd);
}

bool	Cook::isFree()
{
  return (_state == FREE);
}
