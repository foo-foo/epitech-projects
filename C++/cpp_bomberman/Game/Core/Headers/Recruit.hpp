//
// Recruit.hpp for  in /home/menich_a/rendu/cpp_bomberman/work_in_progress/v6
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Wed May 27 16:23:42 2015 Anatole Menichetti
// Last update Sat Jun 13 10:39:50 2015 Anatole Menichetti
//

#ifndef _RECRUIT_HPP_
# define _RECRUIT_HPP_

# include "Bot.hpp"

class	Recruit : public Bot
{

public:
  Recruit(Character* const character, size_t const id);
  virtual ~Recruit() {};

private:
  int	getBestWayRec(std::vector<std::vector <AObject*> > const &, size_t const, size_t const, int const, std::vector<std::pair<size_t, size_t> > &) const;
  void	getOneBestWay(std::vector<std::vector <AObject*> > const &,
		      int const, int const, size_t const, size_t const, char const, int [2],
		      std::vector<std::pair<size_t, size_t> > &) const;
  virtual void	getBestWay(std::vector<std::vector <AObject*> > const &, size_t const, size_t const, int [2]);
  virtual char	getNextAction(Field &);
};

#endif /* !_RECRUIT_HPP_ */
