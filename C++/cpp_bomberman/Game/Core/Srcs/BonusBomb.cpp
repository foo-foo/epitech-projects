//
// BonusBomb.cpp for  in /home/menich_a/rendu/cpp_bomberman/Game/Game/Srcs
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Thu Jun 11 18:50:20 2015 Anatole Menichetti
// Last update Thu Jun 11 18:51:03 2015 Anatole Menichetti
//

#include "BonusBomb.hpp"

/* --------- */
/* Functions */
/* --------- */

bool	BonusBomb::initialize()
{
  scale(glm::vec3(.05, .05, .05));
  translate(glm::vec3(_x + 0.5f, 0.5f, _y + 0.5f));
  return (true);
}

void	BonusBomb::activate(APlayer* player) const
{
  player->addBomb();
  std::cout << "Bonus bomb +1 !" << std::endl;
  std::cout << "Bomb is now : " << player->getBomb() << std::endl << std::endl;
}
