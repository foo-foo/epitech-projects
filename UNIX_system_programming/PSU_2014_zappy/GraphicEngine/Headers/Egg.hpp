//
// Egg.hpp for Egg in /home/rosain_f/rendu/PSU_2014_zappy
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Fri Jul  3 17:14:00 2015 Francois Rosain
// Last update Fri Jul  3 17:37:57 2015 Francois Rosain
//

#ifndef _EGG_
# define _EGG_

# include "Model.hh"

# include "AObject.hpp"

class	Egg : public AObject
{
private:
  gdl::Model*	_model;
  size_t	_x;
  size_t	_y;
  int		_id;

public:
  Egg(gdl::Model* model, size_t x, size_t y, int id)
    : AObject(EGG), _model(model), _x(x), _y(y), _id(id) {}

  virtual ~Egg() {};

  int		getId() const;
  virtual void	draw(gdl::AShader&, gdl::Clock const &);
};

#endif /* !_EGG_ */
