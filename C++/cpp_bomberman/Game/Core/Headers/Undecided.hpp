//
// Undecided.hpp for  in /home/menich_a/rendu/cpp_bomberman/work_in_progress/v6
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Wed May 27 16:23:42 2015 Anatole Menichetti
// Last update Sat Jun 13 10:41:07 2015 Anatole Menichetti
//

#ifndef _UNDECIDED_HPP_
# define _UNDECIDED_HPP_

# include "Bot.hpp"

class	Undecided : public Bot
{
  size_t	_lastPos;

public:
  Undecided(Character* const character, size_t const id);
  virtual ~Undecided() {};

private:
  virtual void	getBestWay(std::vector<std::vector <AObject*> > const &, size_t const, size_t const, int [2]);
  virtual char	getNextAction(Field &);

  void	updateLastPos(char const action, size_t const x, size_t const y);
  char	getRandomWay(std::vector<std::vector <AObject*> > const &map, size_t const x, size_t const y) const;
};

#endif /* !_UNDECIDED_HPP_ */
