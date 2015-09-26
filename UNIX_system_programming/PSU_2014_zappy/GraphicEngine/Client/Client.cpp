//
// Client.cpp for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/client_src
// 
// Made by Younes Iddahamou
// Login   <iddaha_y@epitech.net>
// 
// Started on  Mon Jun 29 14:21:50 2015 Younes Iddahamou
// Last update Sun Jul  5 20:17:20 2015 Younes Iddahamou
//

#include <arpa/inet.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include "header/Client.hh"
#include "header/ClientException.hh"

extern int g_exit_flag;

char		*get_next_line(int);

void		*run(void *client)
{
  Client*	cli;
  fd_set	readfd;

  cli = (Client*)client;
  while (g_exit_flag == 0)
    {
      FD_ZERO(&readfd);
      FD_SET(cli->getFD(), &readfd);
      if (select(cli->getFD() + 1, &readfd, NULL, NULL, NULL) == -1)
	return (NULL);
      cli->send(g_exit_flag);
      if (FD_ISSET(cli->getFD(), &readfd))
      	cli->receive(g_exit_flag);
    }
  return (NULL);
}

Client::Client()
  : port(0), fd(0)
{
  connected = false;
  th = 0;
  output.push_back("GRAPHIC\n");
}

void		Client::lock(pthread_mutex_t* m)
{
  pthread_mutex_lock(m);
}

void		Client::unlock(pthread_mutex_t* m)
{
  pthread_mutex_unlock(m);
}

pthread_t	Client::getThread() const
{
  return (th);
}

void		Client::setAddr(std::string const& addr)
{
  this->addr = addr;
}

bool		Client::isConnected() const
{
  return (connected);
}

int		Client::getFD() const
{
  return (client_sock);
}

void		Client::cnct()
{
  this->sin.sin_family = AF_INET;
  this->sin.sin_port = htons(this->port);
  if ((this->sin.sin_addr.s_addr = inet_addr(this->addr.c_str()))
      == (in_addr_t)(-1))
    throw ClientException("inet_addr failed");
  if (!(this->prot = getprotobyname("TCP")))
    throw ClientException("getprotobyname TCP failed");
  if ((this->client_sock = socket(AF_INET, SOCK_STREAM,
  				  this->prot->p_proto)) == -1)
    throw ClientException("socket failed");
  if (connect(this->client_sock, (struct sockaddr *)&(this->sin),
              sizeof(this->sin)) == -1)
    throw ClientException("connect failed");
  send(g_exit_flag);
  receive(g_exit_flag);
  connected = true;
  this->mutex = PTHREAD_MUTEX_INITIALIZER;
  th = pthread_create(&th, NULL, run, (void*)const_cast<Client*>(this));
  if (th != 0)
    throw ClientException("thread not created");
}

void		Client::setFD(fd_set *readfd, fd_set *writefd)
{
  FD_SET(client_sock, readfd);
  FD_SET(client_sock, writefd);
}

void		Client::receive(int& flag)
{
  char		*inpt;

  inpt = NULL;
  if ((inpt = get_next_line(client_sock)) == NULL)
    {
      flag = 1;
      connected = false;
    }
  else
    {
      this->lock(&mutex);
      input.push_back(std::string(inpt));
      this->unlock(&mutex);
      //free(inpt);
    }
}

void		Client::send(int& flag)
{
  const char	*inpt = this->output[0].c_str();

  flag = flag;
  if (output.size() != 0)
    {
      write(client_sock, inpt, this->output[0].size());
      this->lock(&mutex);
      this->removeFirstElem(output);
      this->unlock(&mutex);
    }
}

std::string		Client::getInput()
{
  this->lock(&mutex);
  std::string			tmp;

  if (input.size() != 0)
    {
      tmp = input[0];
      this->removeFirstElem(input);
      this->unlock(&mutex);
      return (tmp);
    }
  this->unlock(&mutex);
  return ("");
}

void			Client::addInput(const std::string& str)
{
  this->lock(&mutex);
  output.push_back(str);
  this->unlock(&mutex);
}

void					Client::removeFirstElem(std::vector<std::string>& vec)
{
  std::vector<std::string>::iterator	it;

  if (vec.size() == 0)
    return ;
  it = vec.begin();
  vec.erase(it);
}

void		Client::setPort(int port)
{
  this->port = port;
}

Client::~Client()
{
  close(client_sock);
}
