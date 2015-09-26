//
// Order.hpp for Order in /home/rosain_f/rendu/cpp_plazza/frn
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Tue Apr 21 13:10:31 2015 Francois Rosain
// Last update Thu Apr 23 11:35:21 2015 Anatole Menichetti
//

#ifndef _ORDER_
# define _ORDER_

# include "Command.hpp"

# include <map>
# include <queue>
# include <sstream>
# include <string>
# include "Reception.hpp"

class	Order
{
private:
  std::queue<Command*> _order;

public:
  Order(std::map<std::string, PizzaSize>&, std::map<std::string, PizzaType>&);
  ~Order();

  size_t	checkCommand(std::string, PizzaSize &, PizzaType &,
			     std::map<std::string, PizzaSize>&,
			     std::map<std::string, PizzaType>&);

  void		_createCommand(std::string, std::map<std::string, PizzaSize>&,
			       std::map<std::string, PizzaType>&);

  std::queue<Command*>&	getOrder();
};

#endif /* !_ORDER_ */
