#ifndef RESOURCES_HPP_
# define RESOURCES_HPP_

#include <cstdlib>
#include "Command.hpp"
#include "Mutex.hpp"


typedef	struct	s_resource
{
  size_t	doe;
  size_t	tomato;
  size_t	gruyere;
  size_t	ham;
  size_t	mushrooms;
  size_t	steak;
  size_t	eggplant;
  size_t	chieflove;
  size_t	goatcheese;
}		t_resource;


class	Resources
{
private:
  Mutex		_mutex;
  size_t	_doe;
  size_t	_tomato;
  size_t	_gruyere;
  size_t	_ham;
  size_t	_mushrooms;
  size_t	_steak;
  size_t	_eggplant;
  size_t	_chieflove;
  size_t	_goatcheese;

public:
  Resources();
  ~Resources();

  void	regeneResources();
  bool	takeResources(PizzaType const type);
  void	debugDisplay() const;
  t_resource &getResources() const;
  void setResources(t_resource const &);
  int	getNbr() const;

private:
  bool	checkResource(PizzaType const type) const;
};

#endif //!RESOURCES_HPP_
