//
// ScopedLock.hpp for ScopedLock in /home/rosain_f/projects/plazza/TP/ex1
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Mon Apr 13 11:55:11 2015 Francois Rosain
// Last update Mon Apr 13 12:00:10 2015 Francois Rosain
//

#ifndef _SCOPEDLOCK_
# define _SCOPEDLOCK_

# include "Mutex.hpp"

class	ScopedLock
{
private:
  Mutex*	_mutex;

  ScopedLock(Mutex const &);
  ScopedLock	operator=(Mutex const &);

public:
  ScopedLock(Mutex* mutex);
  ~ScopedLock();
};

#endif /* !_SCOPEDLOCK_ */
