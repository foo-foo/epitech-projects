//
// ClientException.cpp for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/client_src
// 
// Made by Younes Iddahamou
// Login   <iddaha_y@epitech.net>
// 
// Started on  Mon Jun 29 16:10:26 2015 Younes Iddahamou
// Last update Mon Jun 29 16:20:51 2015 Younes Iddahamou
//

#include "header/ClientException.hh"

ClientException::ClientException(const std::string& str) throw()
  : std::runtime_error(str)
{
}

ClientException::~ClientException() throw()
{
}
