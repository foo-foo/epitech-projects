//
// APlayer.hpp for Player in /home/rosain_f/projects/BomberMan/animation
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Tue May  5 14:19:49 2015 Francois Rosain
// Last update Sat Jun 13 13:03:27 2015 Anatole Menichetti
//

#ifndef _APLAYER_HPP_
# define _APLAYER_HPP_

# include <iostream>

/* Objects */

# include "Clock.hh"
# include "Field.hpp"
# include "Character.hpp"

/* APlayer */

# include "Bomb.hpp"
# include "ABonus.hpp"

# define DEFAULT_BOMBS	2
# define MAX_BOMBS	10

# define DEFAULT_POWER	3
# define MAX_POWER	10

# define DEFAULT_SPEED	1
# define MAX_SPEED	6

# define SPEED(x) (80 + 5 * x)

typedef void    (Character::*movePtr)(float const);

class	APlayer
{
protected:
  Character*	_character;
  float		_speed;
  int		_bombs;
  int		_power;
  size_t const	_id;
  movePtr	_launchMove[4];

public:
  APlayer(Character* const character, size_t const id);

  virtual ~APlayer() {};

  virtual void			update(gdl::Clock const &, Field&) = 0;

  virtual float			getSpeed() const;
  virtual int			getPower() const;
  virtual int			getBomb() const;

  virtual void			addPower();
  virtual void			addSpeed();
  virtual void			addBomb();

  virtual size_t		getId() const;

  virtual bool			isHuman() const;
};

#endif /* !_APLAYER_HPP_ */
