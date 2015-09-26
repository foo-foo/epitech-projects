//
// main.cpp for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/client_src
// 
// Made by Younes Iddahamou
// Login   <iddaha_y@epitech.net>
// 
// Started on  Mon Jun 29 14:12:38 2015 Younes Iddahamou
// Last update Sun Jul  5 20:14:12 2015 Younes Iddahamou
//

#include <signal.h>
#include <string>
#include <iostream>
#include <sstream>
#include <poll.h>
#include "header/ClientException.hh"
#include "header/Client.hh"
#include "Map.hpp"
#include "GraphicEngine.hpp"

int		g_exit_flag;

int			parsePort(char **av)
{
  int			i(0);
  std::string		arg("");
  std::stringstream	ss;

  arg = av[2];
  ss << arg;
  ss >> i;
  return (i);
}

std::string		parseAddr(char **av)
{
  std::string		addr;

  addr = av[1];
  return (addr);
}

void		gettingStarted(Client& client)
{
  std::string	input;
  GraphicEngine	ge;

  while (g_exit_flag == 0 && !ge.getOver())
    {
      input = client.getInput();
      ge.exec(input);
      if (ge.isInit())
	{
	  if (!ge.update() || !ge.getMap()->isSizeOk())
	    {
	      g_exit_flag = 1;
	      return ;
	    }
	  if (ge.getGoDraw())
	    ge.draw();
        }
    }
}

int		main(int ac, char **av)
{
  Client	client;
  int		port(4242);
  std::string	addr("127.0.0.1");

  if (ac < 3)
    {
      std::cerr << "USAGE: exec addr port" << std::endl;
      return (1);
    }
  port = parsePort(av);
  addr = parseAddr(av);
  g_exit_flag = 0;
  client.setPort(port);
  client.setAddr(addr);
  try
    {
      client.cnct();
      gettingStarted(client);
    }
  catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
      return (1);
    }
  return (0);
}
