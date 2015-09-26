//
// Reception.hpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/includes
//
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
//
// Started on  Wed Apr 15 17:32:32 2015 Anatole Menichetti
// Last update Sun Apr 26 16:18:05 2015 Anatole Menichetti
//

#ifndef RECEPTION_HPP_
# define RECEPTION_HPP_

# include <list>
# include <map>

# include "Command.hpp"
# include "Kitchen.hpp"
# include "Order.hpp"
# include "Parser.hpp"

class	Reception
{
  std::list<Kitchen *>		_kitchens; // A safe queue (used by 2 threads) of kitchens holded by reception.
  Parser const			&_parameters; // Plazza parameters
  std::map<std::string, PizzaSize>	_mPizzaSize;
  std::map<std::string, PizzaType>	_mPizzaType;

public:
  Reception(Parser const &); // Init the 2 reception threads with plazza parameters.
  ~Reception();

  int	start(); // Launch the reception: take and allocate new orders.
  void	operator()(char); // Handle the resources replace time.

private:
  int	allocateCommand(std::queue<Command *> &, size_t&); // Allocate the current command to the kitchen with best capabilities.
};

#endif /* !RECEPTION_HPP_ */
