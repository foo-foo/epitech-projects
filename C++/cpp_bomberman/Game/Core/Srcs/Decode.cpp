//
// Decode.cpp for Decode in /home/rosain_f/rendu/cpp_abstractvm
//
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
//
// Started on  Tue Feb 17 21:17:58 2015 Francois Rosain
// Last update Sat Jun 13 10:24:36 2015 Anatole Menichetti
//

#include "Decode.hpp"

Decode::Decode()
{
  _flameReac.insert(std::pair<e_object, pfctreac>(WALL, &BombEngine::nothingReac));
  _flameReac.insert(std::pair<e_object, pfctreac>(BOMB, &BombEngine::flameReacBomb));
  _flameReac.insert(std::pair<e_object, pfctreac>(BONUS, &BombEngine::flameReacBonus));
  _flameReac.insert(std::pair<e_object, pfctreac>(BOX, &BombEngine::flameReacBox));
  _flameReac.insert(std::pair<e_object, pfctreac>(FLAME, &BombEngine::flameReacFlame));

  _flameDiffus.insert(std::pair<e_object, pfctdiff>(WALL, &BombEngine::nothing));
  _flameDiffus.insert(std::pair<e_object, pfctdiff>(BOMB, &BombEngine::flameDiffusBomb));
  _flameDiffus.insert(std::pair<e_object, pfctdiff>(BONUS, &BombEngine::nothing));
  _flameDiffus.insert(std::pair<e_object, pfctdiff>(BOX, &BombEngine::nothing));
  _flameDiffus.insert(std::pair<e_object, pfctdiff>(FLAME, &BombEngine::flameDiffusFlame));
}

Decode::~Decode()
{}

/* --------- */
/* Functions */
/* --------- */

void	Decode::reaction(e_object const type, BombEngine *bombEngine, int const y, int const x, int &tmp, int const power) const
{
  std::map<e_object, pfctreac>::const_iterator it = _flameReac.find(type);
  (bombEngine->*(it->second))(y, x, tmp, power);
}

void	Decode::diffusion(e_object const type, BombEngine *bombEngine, int const y, int const x) const
{
  std::map<e_object, pfctdiff>::const_iterator it = _flameDiffus.find(type);
  (bombEngine->*(it->second))(y, x);
}
