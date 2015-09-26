//
// Monster.hpp for  in /home/menich_a/rendu/cpp_bomberman/work_in_progress/v6
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Wed May 27 16:23:42 2015 Anatole Menichetti
// Last update Fri Jun 12 23:52:14 2015 Anatole Menichetti
//

#ifndef _MONSTER_HPP_
# define _MONSTER_HPP_

# include "Bot.hpp"

class	Monster : public Bot
{
  size_t	_lastPos;

public:
  Monster(Character* character, size_t const id);
  virtual ~Monster() {};

private:
  virtual void	getBestWay(std::vector<std::vector <AObject*> > const &, size_t const, size_t const, int [2]);
  virtual char	getNextAction(Field &);

  void	updateLastPos(char const action, size_t const x, size_t const y);
  char	getRandomWay(std::vector<std::vector <AObject*> > const &map, size_t const x, size_t const y) const;
};

#endif /* !_MONSTER_HPP_ */
