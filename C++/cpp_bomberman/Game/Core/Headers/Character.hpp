//
// Character.hpp for Character in /home/rosain_f/rendu/cpp_bomberman/work_in_progress/v4
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Fri May 15 11:43:46 2015 Francois Rosain
// Last update Tue Sep 15 08:53:26 2015 Anatole Menichetti
//

#ifndef _CHARACTER_HPP_
# define _CHARACTER_HPP_

# include <iostream>
# include <vector>

# include "AObject.hpp"
# include "Model.hh"

class	Character : public AObject
{
private:
  gdl::Model	_model;
  std::string	_modelFile;
  float		_modelScale;
  float		_x;
  float		_y;
  bool		_mooving;
  size_t const	_id;
  bool		_isDancing;
  void		_animationHandler();

public:
  Character();
  Character(size_t);
  ~Character();

  virtual bool	initialize(int const, int const);
  virtual void	draw(gdl::AShader &, gdl::Clock const &);

  float	getX() const;
  float	getY() const;

  void	moveDown(float const);
  void	moveUp(float const);
  void	moveLeft(float const);
  void	moveRight(float const);
  void	pauseModel();
  void	putBomb();
  bool	isDancing();
  void	danse();
  void	pickBonus();

  bool	isMonster() const;
  void  teleport(std::vector<std::vector <AObject*> > const &);
};

#endif /* !_CHARACTER_HPP_ */
