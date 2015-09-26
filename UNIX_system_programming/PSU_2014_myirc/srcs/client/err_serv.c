/*
** err_serv.c for  in /home/auduri_a/rendu/PSU_2014_myirc/srcs/server
** 
** Made by audurier julien
** Login   <auduri_a@epitech.net>
** 
** Started on  Wed Apr  8 17:26:32 2015 audurier julien
** Last update Sat Apr 11 08:57:26 2015 Anatole Menichetti
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../includes/myirc.h"
#include "../../includes/server.h"

char	*err_serv(char *err_code, char *pseudo, char *name, char *err_mess)
{
  char	*ret;

  if ((ret = malloc(sizeof(char) *
		    (strlen(err_code) + strlen(pseudo) +
		     strlen(name) + strlen(err_mess) + 2))) == NULL)
    return (NULL);
  sprintf(ret, "%s%s %s%s", err_code, pseudo, name, err_mess);
  return (ret);
}
