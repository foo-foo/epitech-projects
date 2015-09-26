//
// IThread.hpp for IThread in /home/rosain_f/projects/plazza/TP/ex1
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Mon Apr 13 12:14:34 2015 Francois Rosain
// Last update Thu Apr 23 12:00:01 2015 Anatole Menichetti
//

#ifndef _ITHREAD_
# define _ITHREAD_

template <typename T, typename U>
class	IThread
{
public:
  virtual ~IThread() {};
  virtual void	start(T *start_fct, U args) = 0;
  virtual void	wait() = 0;

private:
  virtual void	startRoutine() = 0;
};

#endif /* !_ITHREAD_ */
