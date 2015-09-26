//
// BonusSpeed.hpp for BonusSpeed in /home/rosain_f/rendu/cpp_bomberman/work_in_progress/v6
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Tue May 26 12:51:46 2015 Francois Rosain
// Last update Sat Jun 13 09:52:37 2015 Anatole Menichetti
//

#ifndef _BONUS_BOMB_HPP_
# define _BONUS_BOMB_HPP_

/* Objects */

# include "AObject.hpp"
# include "ABonus.hpp"
# include "Model.hh"

class	BonusBomb : public ABonus
{
public:
  BonusBomb(int const y, int const x, gdl::Model& model) : ABonus(y, x, model) {};
  virtual ~BonusBomb() {};

  virtual bool	initialize();
  virtual void	activate(APlayer*) const;
};

#endif /* !_BONUS_BOMB_HPP_ */
