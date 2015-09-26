//
// Warrior.hpp for  in /home/menich_a/rendu/cpp_bomberman/work_in_progress/v6
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Wed May 27 16:23:42 2015 Anatole Menichetti
// Last update Sat Jun 13 10:41:26 2015 Anatole Menichetti
//

#ifndef _WARRIOR_HPP_
# define _WARRIOR_HPP_

# include "Bot.hpp"

class	Warrior : public Bot
{
  std::vector<Character*> &_ennemies;

public:
  Warrior(Character* const character, size_t const id, std::vector<Character*> &);
  virtual ~Warrior() {};

protected:
  virtual int	getNbrHit(std::vector<std::vector <AObject*> > const &, size_t const, size_t const) const;

private:
  int	absoluteValue(int const) const;
  void	getEnnemiesDirections(int [4], bool const) const;
  bool	nextActionIsDangerous(std::vector<std::vector <AObject*> > const &, char const, size_t, size_t) const;
  int	getBestWayRec(std::vector<std::vector <AObject*> > const &, size_t const, size_t const, int const,
		      std::vector<std::pair<size_t, size_t> > &) const;
  void	getOneBestWay(std::vector<std::vector <AObject*> > const &,
		      int const, int const, size_t const, size_t const, char const, int [2],
		      std::vector<std::pair<size_t, size_t> > &) const;
  virtual void	getBestWay(std::vector<std::vector <AObject*> > const &, size_t const, size_t const, int [2]);
  virtual char	getNextAction(Field &);
};

#endif /* !_WARRIOR_HPP_ */
