#ifndef _ABONUS_HPP_
# define _ABONUS_HPP_

# include <iostream>

/* Objects */

# include "Model.hh"
# include "APlayer.hpp"
# include "AObject.hpp"

# define NB_BONUS	3
# define LUCK_BONUS	30

class	ABonus : public AObject
{
protected:
  gdl::Model&	_model;
  int		_y;
  int		_x;

public:
  ABonus(int y, int x, gdl::Model& model) : AObject(BONUS), _model(model), _y(y), _x(x) {};
  virtual ~ABonus() {};

  virtual void	draw(gdl::AShader&, gdl::Clock const &);
  virtual void	activate(APlayer*) const = 0;
};

#endif /* !_ABONUS_HPP_ */
