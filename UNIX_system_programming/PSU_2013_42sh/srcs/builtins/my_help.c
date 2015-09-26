/*
** my_help.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu May 15 19:50:57 2014 menich_a
** Last update Wed May 21 16:41:13 2014 menich_a
*/

#include "mysh.h"
#include "my.h"

char	**my_help(char **cmd, char **env)
{
  (void)cmd;
  my_putstr(HELP_LIST);
  return (env);
}
