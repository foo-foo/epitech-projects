//
// ABonus.cpp for  in /home/menich_a/rendu/cpp_bomberman/Game/Game/Srcs
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Thu Jun 11 18:47:48 2015 Anatole Menichetti
// Last update Thu Jun 11 18:47:49 2015 Anatole Menichetti
//

#include "ABonus.hpp"

/* --------- */
/* Functions */
/* --------- */

void    ABonus::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _model.draw(shader, getTransformation(), clock.getElapsed());
}
