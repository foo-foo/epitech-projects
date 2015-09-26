//
// NamedPipe.cpp for cpp_plazza in /home/menich_a/rendu/cpp_plazza/srcs
//
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
//
// Started on  Thu Apr 23 13:35:44 2015 Anatole Menichetti
// Last update Sun Apr 26 16:32:19 2015 Anatole Menichetti
//

#include <cerrno>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "NamedPipe.hpp"
#include "RuntimeError.hpp"

NamedPipe::NamedPipe(std::string const &str)
  : _path(str), _fd(0)
{
  if (mkfifo(this->_path.c_str(), 0644) == -1)
    throw (RuntimeError("mkfifo", strerror(errno)));
}

NamedPipe::~NamedPipe()
{
  if (this->_fd != 0)
    close(this->_fd);
  remove(this->_path.c_str());
}

/* ---------------- */
/* Public functions */
/* ---------------- */

int	NamedPipe::openPipeRd()
{
  int	mode;

  if ((this->_fd = open(this->_path.c_str(), O_RDONLY)) > 0)
    {
      mode = fcntl(this->_fd, F_GETFL, 0);
      mode |= O_NONBLOCK;
      fcntl(this->_fd, F_SETFL, mode);
    }
  return (this->_fd);
}

int	NamedPipe::openPipeWr()
{
  int	mode;

  if ((this->_fd = open(this->_path.c_str(), O_WRONLY)) > 0)
    {
      mode = fcntl(this->_fd, F_GETFL, 0);
      mode |= O_NONBLOCK;
      fcntl(this->_fd, F_SETFL, mode);
    }
  return (this->_fd);
}
