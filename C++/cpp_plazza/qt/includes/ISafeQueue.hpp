//
// ISafeQueue.hpp for ISafeQueue in /home/rosain_f/projects/plazza/TP
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Mon Apr 13 13:43:19 2015 Francois Rosain
// Last update Tue Apr 14 14:00:01 2015 Anatole Menichetti
//

#ifndef _ISAFEQUEUE_
# define _ISAFEQUEUE_

template <typename T>
class ISafeQueue
{
public:
  virtual ~ISafeQueue() {};
  virtual void	push(T) = 0;
  virtual bool	tryPop(T*) = 0;
  virtual bool	isFinished() = 0;
  virtual void	setFinished() = 0;
};

#endif /* !_ISAFEQUEUE_ */
