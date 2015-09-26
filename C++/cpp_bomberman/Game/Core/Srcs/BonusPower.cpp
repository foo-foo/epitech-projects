//
// BonusSpeed.cpp for BonusSpeed in /home/rosain_f/rendu/cpp_bomberman/work_in_progress/v6
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Tue May 26 12:51:30 2015 Francois Rosain
// Last update Thu Jun 11 18:50:51 2015 Anatole Menichetti
//

#include "BonusPower.hpp"

/* --------- */
/* Functions */
/* --------- */

bool	BonusPower::initialize()
{
  scale(glm::vec3(0.0025f,0.0025f,0.0025f));
  translate(glm::vec3(_x + 0.5f, 0.5f, _y + 0.5f));
  return (true);
}

void	BonusPower::activate(APlayer* player) const
{
  player->addPower();
  std::cout << "Bonus power +1 !" << std::endl;
  std::cout << "Power is now : " << player->getPower() << std::endl << std::endl;
}
