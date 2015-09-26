//
// BonusSpeed.cpp for BonusSpeed in /home/rosain_f/rendu/cpp_bomberman/work_in_progress/v6
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Tue May 26 12:51:30 2015 Francois Rosain
// Last update Thu Jun 11 18:51:52 2015 Anatole Menichetti
//

#include "BonusSpeed.hpp"

/* --------- */
/* Functions */
/* --------- */

bool	BonusSpeed::initialize()
{
  scale(glm::vec3(.25, .25, .25));
  translate(glm::vec3(_x + 0.5f, 0.5f, _y + 0.5f));
  return (true);
}

void	BonusSpeed::activate(APlayer* player) const
{
  player->addSpeed();
  std::cout << "Bonus speed +5 !" << std::endl;
  std::cout << "Speed is now : " << player->getSpeed() << std::endl << std::endl;
}
