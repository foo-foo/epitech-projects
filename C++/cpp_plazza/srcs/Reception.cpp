//
// Reception.cpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/srcs
//
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
//
// Started on  Wed Apr 15 22:11:00 2015 Anatole Menichetti
// Last update Sun Apr 26 16:38:36 2015 Anatole Menichetti
//

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctime>
#include <exception>
#include "Reception.hpp"
#include "BadCommandError.hpp"

Reception::Reception(Parser const &parameters) :
  _parameters(parameters)
{
  _mPizzaSize["s"] = S;
  _mPizzaSize["m"] = M;
  _mPizzaSize["l"] = L;
  _mPizzaSize["xl"] = XL;
  _mPizzaSize["xxl"] = XXL;

  _mPizzaType["regina"] = Regina;
  _mPizzaType["margarita"] = Margarita;
  _mPizzaType["americane"] = Americaine;
  _mPizzaType["fantasia"] = Fantasia;
}

Reception::~Reception()
{}

/* ----------------- */
/* Private functions */
/* ----------------- */

//		Allocate the current command to the kitchen with best capabilities.
int		Reception::allocateCommand(std::queue<Command *> &commands, size_t &name)
{
  Kitchen	*bestKitchen;

  bestKitchen = NULL;
  for (std::list<Kitchen *>::iterator it = _kitchens.begin() ; it != _kitchens.end() ; ++it)
    {
      (*it)->receiveUpdate();
      if (!(*it)->isOpen())
	{
	  delete *it;
	  _kitchens.erase(it);
	}
      else
	if ((*it)->getState() == NOFULL &&
	    (bestKitchen == NULL ||(*it)->getResources().getNbr() > bestKitchen->getResources().getNbr()))
	  bestKitchen = *it;
	}
  if (bestKitchen)
    {
      bestKitchen->sendCommand(*commands.front());
      commands.pop();
    }
  else
    {
      bestKitchen = new Kitchen(_parameters, commands, name++, _mPizzaSize, _mPizzaType);
      _kitchens.push_back(bestKitchen);
      if (bestKitchen->start())
	{
	  delete _kitchens.back();
	  return (1);
	}
    }
  return (0);
}


/* ---------------- */
/* Public functions */
/* ---------------- */

//		Launch the reception: take and allocate new orders.
int		Reception::start()
{
  Order		*order;
  size_t	name = 0;

  while (1)
    {
      try {
	order = new Order(_mPizzaSize, _mPizzaType);
	std::queue<Command *>	&commands = order->getOrder();

	while (!commands.empty()/* || _kitchens.size()*/)
	  {
	    if (allocateCommand(commands, name))
	      {
		delete order;
		return (0);
	      }
	    if (!commands.empty())
	      commands.pop();
	  }
	delete order;
      }
      catch (BadCommandError &e) {
	std::cerr << e.what() << "." << std::endl;
	}
    }
  return (0);
}
