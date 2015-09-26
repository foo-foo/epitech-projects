//
// Thread.hpp for Thread in /home/rosain_f/projects/plazza/TP/ex1
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Mon Apr 13 12:16:25 2015 Francois Rosain
// Last update Fri Apr 24 17:24:14 2015 Anatole Menichetti
//

#ifndef _THREAD_
# define _THREAD_

# include <pthread.h>
# include "IThread.hpp"

void *start_routine(void *);

enum thread_status
  {
    NYS,
    RUNNING,
    DEAD
  };

template <typename T, typename U>
class	Thread : public IThread<T, U>
{
  thread_status	_status;
  pthread_t	_thread;
  T		*_startRoutine;
  U		_arg;

public:
  Thread();
  virtual ~Thread();

  virtual void	start(T *start_fct, U args);
  virtual void	wait();

private:
  virtual void	startRoutine();
  static void	*start_routine(void *);
};

template <typename T, typename U>
Thread<T, U>::Thread()
  : _status(NYS), _thread(0)
{}

template <typename T, typename U>
Thread<T, U>::~Thread()
{}

/* ---------------- */
/* Public functions */
/* ---------------- */

template <typename T, typename U>
void    Thread<T, U>::start(T *startRoutine, U arg)
{
  _status = RUNNING;
  _startRoutine = startRoutine;
  _arg = arg;
  pthread_create(&_thread, NULL, Thread<T, U>::start_routine, this);
}

template <typename T, typename U>
void    Thread<T, U>::wait()
{
  pthread_join(_thread, NULL);
  _status = DEAD;
}

/* ----------------- */
/* Private functions */
/* ----------------- */

template <typename T, typename U>
void	Thread<T, U>::startRoutine()
{
  (*_startRoutine)(_arg);
}

// Trampoline
template <typename T, typename U>
void		*Thread<T, U>::start_routine(void *arg)
{
  Thread<T, U>	*thread = reinterpret_cast<Thread <T, U> *>(arg);

  thread->startRoutine();
  return NULL;
}

#endif /* !_THREAD_ */
