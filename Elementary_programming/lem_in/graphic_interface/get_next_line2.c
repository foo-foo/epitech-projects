/*
** get_next_line2.c for get_next_line2.c in /home/benoit_l/rendu/lem-in/v3.0/interface_graphique
** 
** Made by Benoit Leo
** Login   <benoit_l@epitech.net>
** 
** Started on  Sun May  4 16:30:05 2014 Benoit Leo
** Last update Sun May  4 19:46:47 2014 menich_a
*/

#include <unistd.h>
#include "get_next_line.h"

int	msg_error(char *msg)
{
  if (msg)
    write(2, msg, my_strlen(msg));
  return (-1);
}

int	end_of_line(char *str)
{
  int	i;

  i = 0;
if (!str)
    return (-1);
  while (str[i] != '\0')
    {
      if (str[i] == '\n')
        return (i);
      i = i + 1;
    }
  return (-1);
}
