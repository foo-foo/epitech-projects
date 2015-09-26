//
// Cook.hpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/includes
//
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
//
// Started on  Wed Apr 15 17:58:14 2015 Anatole Menichetti
// Last update Sun Apr 26 16:21:09 2015 Anatole Menichetti
//

#ifndef COOK_HPP_
# define COOK_HPP_

# include <map>
# include "Thread.hpp"
# include "SafeQueue.hpp"
# include "Command.hpp"
# include "Resources.hpp"

enum	KitchenStat
{
  FULL,
  NOFULL,
  CLOSE
};

enum	CookState
  {
    BUSY = 0,
    FREE = 1
  };
class	Cook
{
  SafeQueue<Command *>	&_commands;
  SafeQueue<Command *>	&_cmdFinished;
  double const		_multiplier;
  Resources		&_resources;
  Thread<Cook,char>	_thread;
  CookState		_state;
  char			_c; //debug
  KitchenStat		&_kitchenstate;
  std::map<std::string, PizzaSize>	_mPizzaSize;
  std::map<std::string, PizzaType>	_mPizzaType;

public:
  Cook(SafeQueue<Command *> &, SafeQueue<Command *> &,
       double const, Resources &, char const, KitchenStat &,
       std::map<std::string, PizzaSize> &,
       std::map<std::string, PizzaType> &);
  ~Cook();

  void		operator()(const char);
  Command	*makePizza();
  bool		isFree() const;
};

#endif /* !COOK_HPP_ */
