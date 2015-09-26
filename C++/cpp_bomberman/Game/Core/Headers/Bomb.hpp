#ifndef BOMB_HPP_
# define BOMB_HPP_

# include <ctime>
# include "AObject.hpp"
# include "Model.hh"
# include "APlayer.hpp"

# define TMP_BOMB 2

class	Bomb : public AObject
{
private:
  APlayer*	_player;
  gdl::Model&	_model;
  time_t	_timer;
  int	_y;
  int	_x;

public:
  Bomb(int const y, int const x, APlayer* const player, gdl::Model &model);
  ~Bomb();

  APlayer&	getPlayer() const;

  bool	explose();
  bool	initialize();
  void	draw(gdl::AShader &shader, gdl::Clock const &clock);
};

#endif //!BOMB_HPP_
