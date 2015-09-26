#ifndef FLAME_HPP_
# define FLAME_HPP_

# include <ctime>
# include "AObject.hpp"
# include "Model.hh"

# define TMP_FLAME 0.25

class	Flame : public AObject
{
private:

  gdl::Model	&_model;
  time_t	_timer;
  int		_y;
  int		_x;
  bool		_flagBox;

public:
  Flame(int const y, int const x, gdl::Model &model, bool const flagBox);
  ~Flame();

  bool	isEnd();
  bool	isBonus() const;
  bool	initialize();
  void	draw(gdl::AShader &shader, gdl::Clock const &clock);
};

#endif //!BOMB_HPP_
