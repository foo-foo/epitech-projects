//
// Character.cpp for Character in /home/rosain_f/rendu/PSU_2014_zappy/client_graphic_src
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Fri Jul  3 12:15:41 2015 Francois Rosain
// Last update Sun Jul  5 12:18:44 2015 Francois Rosain
//

#include "Character.hpp"

#include <iostream>

Character::Character(gdl::Model* model, size_t id,  float x, float y, int lvl, int o)
  : AObject(CHARACTER), _model(model), _x(x), _y(y), _id(id), _lvl(lvl), _orientation(o), _turn(0), _die(false)
{
  initialize();
  translate(glm::vec3(x + 0.5f,1,y + 0.5f));
  scale(glm::vec3(SCALE_LVL_1, SCALE_LVL_1, SCALE_LVL_1));
  rotate(glm::vec3(0,1,0), ORIENTATE(o));
}

Character::~Character()
{}

/* --------- */
/* Get / Set */
/* --------- */

size_t	Character::getId() const
{
  return (_id);
}

float	Character::getX() const
{
  return (_x);
}

float	Character::getY() const
{
  return (_y);
}

size_t	Character::getOrientation() const
{
  return (_orientation);
}

void	Character::setX(size_t x)
{
  _x = x;
}

void	Character::setY(size_t y)
{
  _y = y;
}

void	Character::setOrientation(size_t o)
{
  _orientation = o;
}

bool	Character::getDie() const
{
  return (_die);
}

size_t	Character::getTurn() const
{
  return (_turn);
}

/* --------- */
/* Functions */
/* --------- */

void		Character::draw(gdl::AShader& shader, gdl::Clock const & clock)
{
  _model->draw(shader, getTransformation(), clock.getElapsed());
}

void		Character::addTurn()
{
  _turn++;
}

void		Character::die()
{
  _die = true;
}
