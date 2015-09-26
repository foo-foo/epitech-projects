//
// Mutex.cpp for Mutex in /home/rosain_f/projects/plazza/TP/ex1
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Mon Apr 13 11:36:51 2015 Francois Rosain
// Last update Thu Apr 23 10:28:13 2015 Anatole Menichetti
//

#include "../includes/Mutex.hpp"

Mutex::Mutex()
{
  pthread_mutex_init(&_mutex, NULL);
}

Mutex::~Mutex()
{
  pthread_mutex_destroy(&_mutex);
}

/* ---------------- */
/* Public functions */
/* ---------------- */

void	Mutex::lock()
{
  pthread_mutex_lock(&_mutex);
}

void	Mutex::unlock()
{
  pthread_mutex_unlock(&_mutex);
}

bool	Mutex::trylock()
{
  if (!pthread_mutex_trylock(&_mutex))
    return (true);
  return (false);
}
