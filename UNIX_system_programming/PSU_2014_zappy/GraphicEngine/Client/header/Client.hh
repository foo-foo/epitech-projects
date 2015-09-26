//
// Client.hh for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/client_src/header
// 
// Made by Younes Iddahamou
// Login   <iddaha_y@epitech.net>
// 
// Started on  Mon Jun 29 14:17:44 2015 Younes Iddahamou
// Last update Sun Jul  5 19:27:56 2015 Younes Iddahamou
//

#ifndef __CLIENT_HH__
# define __CLIENT_HH__

# include <iostream>
# include <netdb.h>
# include <pthread.h>
# include <string>
# include <vector>
# include <map>

class Client
{
public:
  Client();
  ~Client();

public:
  void	setPort(int);
public:
  int	getFD() const;
public:
  void	cnct();
  void	setFD(fd_set *, fd_set *);
  void	receive(int&);
  void	send(int&);
  void	removeFirstElem(std::vector<std::string>&);
  std::string	getInput();
  void	addInput(std::string const&);
  bool	isConnected() const;
  void	lock(pthread_mutex_t*);
  void	unlock(pthread_mutex_t*);
  pthread_t	getThread() const;
  void		setAddr(const std::string&);

private:
  int				port;
  int				fd;
  struct sockaddr_in		sin;
  struct protoent		*prot;
  int				client_sock;
  std::string			addr;
  std::vector<std::string>	input;
  std::vector<std::string>	output;
  pthread_t			th;
  pthread_mutex_t		mutex;
  pthread_mutex_t		mutex2;
  bool				connected;
};

#endif
