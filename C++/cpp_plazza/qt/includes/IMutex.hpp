//
// IMutex.hpp for IMutex in /home/rosain_f/projects/plazza/TP/ex1
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Mon Apr 13 11:34:18 2015 Francois Rosain
// Last update Tue Apr 14 10:49:09 2015 Anatole Menichetti
//

#ifndef _IMUTEX_
# define _IMUTEX_

class	IMutex
{
public:
  virtual ~IMutex(void) {};
  virtual void	lock(void) = 0;
  virtual void	unlock(void) = 0;
  virtual bool	trylock(void) = 0;
};

#endif /* _IMUTEX_ */
