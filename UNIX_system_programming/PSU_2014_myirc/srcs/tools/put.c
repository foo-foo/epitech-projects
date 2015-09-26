/*
** put.c for my_irc in /home/menich_a/rendu/PSU_2014_myirc/srcs/client
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Apr  8 10:05:20 2015 Anatole Menichetti
** Last update Wed Apr  8 11:38:48 2015 Anatole Menichetti
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>

void	putstr(char *str)
{
  if (str)
    if (write(1, str, strlen(str)) == -1 &&
	write(2, str, strlen(str)) == -1)
	perror("write error");
}

int	fputstr(int fd, char *str)
{
  if (str)
    return (write(fd, str, strlen(str)));
  return (0);
}
