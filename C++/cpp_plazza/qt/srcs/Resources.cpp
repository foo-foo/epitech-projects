//
// Resources->cpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/srcs
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech->net>
// 
// Started on  Thu Apr 23 13:41:35 2015 Anatole Menichetti
// Last update Thu Apr 23 17:50:28 2015 Anatole Menichetti
//

#include <string>
#include <iostream>
#include "../includes/ScopedLock.hpp"
#include "../includes/Resources.hpp"

Resources::Resources()
  : _mutex(),
    _doe(5),
    _tomato(5),
    _gruyere(5),
    _ham(5),
    _mushrooms(5),
    _steak(5),
    _eggplant(5),
    _chieflove(5),
    _goatcheese(5)
{
}

Resources::~Resources()
{
}

/* ---------------- */
/* Public functions */
/* ---------------- */

void		Resources::regeneResources()
{
  ScopedLock	sl(&_mutex);

  this->_doe += 1;
  this->_tomato += 1;
  this->_gruyere += 1;
  this->_ham += 1;
  this->_mushrooms += 1;
  this->_steak += 1;
  this->_eggplant += 1;
  this->_chieflove += 1;
  this->_goatcheese += 1;
}

bool	Resources::takeResources(PizzaType type)
{
  if (this->checkResource(type))
    {
      ScopedLock	sl(&_mutex);

      this->_doe += -1;
      this->_tomato += -1;
      this->_gruyere += (type == Margarita || type == Regina
			 || type == Americaine) ? -1 : 0;
      this->_ham += (type == Regina) ? -1 : 0;
      this->_mushrooms += (type == Regina) ? -1 : 0;
      this->_steak += (type == Americaine) ? -1 : 0;
      this->_eggplant += (type == Fantasia) ? -1 : 0;
      this->_chieflove += (type == Fantasia) ? -1 : 0;
      this->_goatcheese += (type == Fantasia) ? -1 : 0;
      return (true);
    }
  return (false);
}

void	Resources::debugDisplay() const
{
  std::cout << "ressource    : " << std::endl
	    << " - doe        : " << this->_doe << std::endl
	    << " - tomato     : " << this->_tomato << std::endl
	    << " - gruyere    : " << this->_gruyere << std::endl
	    << " - ham        : " << this->_ham << std::endl
	    << " - mushrooms  : " << this->_mushrooms << std::endl
	    << " - steak      : " << this->_steak << std::endl
	    << " - eggplant   : " << this->_eggplant << std::endl
	    << " - chieflove  : " << this->_chieflove << std::endl
	    << " - goatcheese : " << this->_goatcheese << std::endl;
}

t_resource	&Resources::getResources() const
{
  t_resource	&val = *(new t_resource);
  val.doe = _doe;
  val.tomato = _tomato;
  val.gruyere = _gruyere;
  val.ham = _ham;
  val.mushrooms = _mushrooms;
  val.steak = _steak;
  val.eggplant = _eggplant;
  val.chieflove = _chieflove;
  val.goatcheese = _goatcheese;
  return (val);
}

void	Resources::setResources(t_resource &res)
{
  _doe = res.doe;
  _tomato = res.tomato;
  _gruyere = res.gruyere;
  _ham = res.ham;
  _mushrooms = res.mushrooms;
  _steak = res.steak;
  _eggplant = res.eggplant;
  _chieflove = res.chieflove;
  _goatcheese = res.goatcheese;
}

int	Resources::getNbr()
{
  return (_tomato);
}

/* ----------------- */
/* Private functions */
/* ----------------- */

bool	Resources::checkResource(PizzaType type)
{
  return ((this->_doe && this->_tomato)
	  && ((type == Margarita && this->_gruyere)
	      || (type == Regina && this->_gruyere && this->_ham && this->_mushrooms)
	      || (type == Americaine && this->_gruyere && this->_steak)
	      || (type == Fantasia && this->_eggplant && this->_goatcheese && this->_chieflove)));
}
