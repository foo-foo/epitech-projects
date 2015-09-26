//
// Command.hpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/includes
//
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
//
// Started on  Wed Apr 15 17:51:52 2015 Anatole Menichetti
// Last update Sun Apr 26 16:06:08 2015 Anatole Menichetti
//

#ifndef COMMAND_HPP_
# define COMMAND_HPP_

# include <unistd.h>

enum	PizzaSize
  {
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
  };

enum	PizzaType
  {
    Regina = 1,
    Margarita = 2,
    Americaine = 4,
    Fantasia = 8
  };

typedef struct	s_cmd
{
  size_t	kitchen;
  size_t	cook;
  PizzaSize	size;
  PizzaType	type;
}		t_cmd;

class	Command
{
  size_t		_kitchen;
  size_t		_cook;
  PizzaSize const	_size;
  PizzaType const	_type;

public:
  Command(PizzaSize const &, PizzaType const &);
  Command(t_cmd &cmd);
  ~Command();

  void		setKitchen(size_t const);
  void		setCook(size_t const);

  size_t	getKitchen() const;
  size_t	getCook() const;
  PizzaSize	getSize() const;
  PizzaType	getType() const;
  t_cmd		getCmd() const;
};

#endif /* !COMMAND_HPP_ */
