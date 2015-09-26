//
// Character.hpp for Character in /home/rosain_f/rendu/PSU_2014_zappy/client_graphic_src
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Fri Jul  3 12:12:56 2015 Francois Rosain
// Last update Sat Jul  4 19:50:07 2015 Francois Rosain
//

#ifndef _CHARACTER_
# define _CHARACTER_

# include "AObject.hpp"
# include "Model.hh"

# define ORIENTATE(x)	(x * 90 - 90)
# define TURN_BEFORE_ERASE	200

# define SCALE_LVL_1	0.35
# define SCALE_LVL_2	0.50

class	Character  : public AObject
{
private:
  gdl::Model*	_model;
  float		_x;
  float		_y;
  size_t	_id;
  int		_lvl;
  int		_orientation; 
  size_t	_turn;
  bool		_die;

public:
  Character(gdl::Model*, size_t, float, float, int, int);
  ~Character();

  size_t	getId() const;
  float		getX() const;
  float		getY() const;
  size_t	getOrientation() const;
  bool		getDie() const;
  size_t	getTurn() const;

  void		setX(size_t);
  void		setY(size_t);
  void		setOrientation(size_t);
  void		addTurn();

  void		die();

  virtual void	draw(gdl::AShader&, gdl::Clock const &);
};

#endif /* !_CHARACTER_ */
