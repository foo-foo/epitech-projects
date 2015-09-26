//
// Mutex.hpp for Mutex in /home/rosain_f/projects/plazza/TP/ex1
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Mon Apr 13 11:35:33 2015 Francois Rosain
// Last update Tue Apr 14 10:48:54 2015 Anatole Menichetti
//

#ifndef _MUTEX_
# define _MUTEX_

# include <pthread.h>
# include "IMutex.hpp"

class	Mutex : public IMutex
{
private:
  pthread_mutex_t	_mutex;

public:
  Mutex();
  virtual ~Mutex();

  virtual void	lock();
  virtual void	unlock();
  virtual bool	trylock();
};

#endif /* _MUTEX_ */
