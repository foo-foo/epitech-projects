//
// Flame.cpp for  in /home/menich_a/rendu/cpp_bomberman/Game/Game/Srcs
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Thu Jun 11 18:58:13 2015 Anatole Menichetti
// Last update Sat Jun 13 10:31:29 2015 Anatole Menichetti
//

#include <iostream>
#include "Flame.hpp"

Flame::Flame(int const y, int const x, gdl::Model &model, bool const flagBox)
  : AObject(FLAME), _model(model),_timer(time(NULL)), _y(y), _x(x), _flagBox(flagBox)
{
  if (_timer == -1)
    throw std::exception();
}

Flame::~Flame()
{}

bool	Flame::isEnd()
{
  if (difftime(time(NULL), _timer) >= TMP_FLAME)
    {
      _timer = time(NULL);
      return (true);
    }
  return (false);
}

bool	Flame::isBonus() const
{
  return (_flagBox);
}

bool	Flame::initialize()
{
  scale(glm::vec3(0.005f, 0.005f, 0.005f));
  translate(glm::vec3(_x + 0.5f, 0.5f, _y + 0.5f));
  return (true);
}

void    Flame::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _model.draw(shader, getTransformation(), clock.getElapsed());
}
