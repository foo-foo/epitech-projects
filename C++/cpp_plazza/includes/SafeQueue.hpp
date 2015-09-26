//
// SafeQueue.hpp for SafeQueue in /home/rosain_f/projects/plazza/TP
//
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
//
// Started on  Mon Apr 13 14:48:46 2015 Francois Rosain
// Last update Sun Apr 26 23:06:25 2015 Sebastien Lauret
//

#ifndef _SAFEQUEUE_
# define _SAFEQUEUE_

# include <string>
# include <iostream>
# include <queue>
# include "ScopedLock.hpp"
# include "ISafeQueue.hpp"

template <typename T>
class	SafeQueue : public ISafeQueue<T>
{
public:
  SafeQueue();
  virtual ~SafeQueue();
  virtual void  push(T);
  virtual bool  tryPop(T*);
  virtual bool  isFinished() const;
  virtual void  setFinished();
  size_t	size() const;

private:
  std::queue<T>		_queue;
  bool			_state;
  Mutex			_mutex;
};

/* ----------------- */
/* Public functions */
/* ----------------- */

template <typename T>
SafeQueue<T>::SafeQueue()
  : _state(false), _mutex()
{}

template <typename T>
SafeQueue<T>::~SafeQueue()
{}

template <typename T>
void    SafeQueue<T>::push(T value)
{
  _mutex.lock();
  _queue.push(value);
  _mutex.unlock();
}

template <typename T>
bool    SafeQueue<T>::tryPop(T *value)
{
  ScopedLock	sl(&_mutex);

  if (_queue.empty())
    return (false);
  *value = _queue.front();
  _queue.pop();
  return (true);
}

template <typename T>
bool    SafeQueue<T>::isFinished() const
{
  if (_state && _queue.empty())
    return (true);
  return (false);
}

template <typename T>
void    SafeQueue<T>::setFinished()
{
  _mutex.lock();
  _state = true;
  _mutex.unlock();
}
template <typename T>
size_t    SafeQueue<T>::size() const
{
  return (_queue.size());
}

#endif /* !_SAFEQUEUE_ */
