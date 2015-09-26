//
// ScopedLock.cpp for ScopedLock in /home/rosain_f/projects/plazza/TP/ex1
//
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
//
// Started on  Mon Apr 13 11:57:44 2015 Francois Rosain
// Last update Fri Apr 24 11:54:09 2015 Sebastien Lauret
//

#include "../includes/ScopedLock.hpp"

ScopedLock::ScopedLock(Mutex* mutex)
  : _mutex(mutex)
{
  _mutex->lock();
}

ScopedLock::~ScopedLock()
{
  _mutex->unlock();
}
