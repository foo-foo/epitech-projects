//
// Bomb.cpp for  in /home/menich_a/rendu/cpp_bomberman/Game/Game/Srcs
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Thu Jun 11 18:51:13 2015 Anatole Menichetti
// Last update Sat Jun 13 09:24:38 2015 Anatole Menichetti
//

#include <iostream>
#include "Bomb.hpp"

Bomb::Bomb(int const y, int const x, APlayer* const player, gdl::Model& model)
  : AObject(BOMB), _player(player), _model(model),_timer(time(NULL)), _y(y), _x(x)
{
  if (_timer == -1)
    throw std::exception();
}

Bomb::~Bomb()
{}

/* --------- */
/* Get / Set */
/* --------- */

APlayer&	Bomb::getPlayer() const
{
  return (*_player);
}

/* --------- */
/* Functions */
/* --------- */

bool	Bomb::explose()
{
  if (difftime(time(NULL), _timer) >= TMP_BOMB)
    {
      _timer = time(NULL);
      _player->addBomb();
      return (true);
    }
  return (false);
}

bool	Bomb::initialize()
{
  scale(glm::vec3(.1, .1, .1));
  translate(glm::vec3(_x + 0.5f, 0.5f, _y + 0.5f));
  return (true);
}

void    Bomb::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _model.draw(shader, getTransformation(), clock.getElapsed());
}
