//
// ClientException.hh for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/client_src/header
// 
// Made by Younes Iddahamou
// Login   <iddaha_y@epitech.net>
// 
// Started on  Mon Jun 29 16:04:48 2015 Younes Iddahamou
// Last update Mon Jun 29 16:27:10 2015 Younes Iddahamou
//

#ifndef __CLIENT_EXCEPTION__
# define __CLIENT_EXCEPTION__

# include <stdexcept>
# include <string>

class ClientException : public std::runtime_error
{
public:
  ClientException(const std::string&) throw();
  virtual ~ClientException() throw();
};

#endif
