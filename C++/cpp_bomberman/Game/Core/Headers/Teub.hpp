//
// Teub.hpp for  in /home/menich_a/rendu/cpp_bomberman/work_in_progress/v6
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Wed May 27 16:23:42 2015 Anatole Menichetti
// Last update Sat Jun 13 10:40:41 2015 Anatole Menichetti
//

#ifndef _TEUB_HPP_
# define _TEUB_HPP_

# include "Undecided.hpp"

class	Teub : public Undecided
{
public:

  Teub(Character* const character, size_t const id);
  virtual ~Teub() {};

protected:
  virtual int	getNbrHit(std::vector<std::vector <AObject*> > const &, size_t const, size_t const) const;
};

#endif /* !_TEUB_HPP_ */
