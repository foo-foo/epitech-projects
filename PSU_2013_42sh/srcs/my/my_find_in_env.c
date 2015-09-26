/*
** my_find_in_env.c for my_select in /home/menich_a/rendu/PSU_2013_my_select/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Jan 14 12:25:41 2014 menich_a
** Last update Sat Feb 15 11:40:58 2014 menich_a
*/

#include <stdlib.h>
#include "my.h"

/*
**	Return value of env variable `to_find'
*/
char	*my_find_in_env(char **env, char *to_find)
{
  int	i;

  i = 0;
  if (env == NULL || env[0] == NULL)
    return (NULL);
  while (env[i] != NULL)
    {
      if (my_strncmp(env[i], to_find, my_strlen(to_find) - 1) == 0 &&
	  env[i][my_strlen(to_find)] == '=')
	return (env[i] + my_strlen(to_find) + 1);
      i = i + 1;
    }
  return (NULL);
}
