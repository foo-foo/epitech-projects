//
// Egg.cpp for Egg in /home/rosain_f/rendu/PSU_2014_zappy
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Fri Jul  3 17:22:56 2015 Francois Rosain
// Last update Fri Jul  3 17:38:16 2015 Francois Rosain
//

#include "Egg.hpp"

void	Egg::draw(gdl::AShader& shader, gdl::Clock const & clock)
{
  _model->draw(shader, getTransformation(), clock.getElapsed());
}

int	Egg::getId() const
{
  return (_id);
}
