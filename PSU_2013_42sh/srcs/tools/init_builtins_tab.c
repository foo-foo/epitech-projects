/*
** init_builtins_tab.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2/srcs
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri May 16 19:43:41 2014 menich_a
** Last update Sat May 31 14:11:47 2014 menich_a
*/

#include "mysh.h"
#include "alias.h"

void		init_builtins_tab(t_builtin builtins[13])
{
  builtins[0] = (t_builtin){"history", &display_history};
  builtins[1] = (t_builtin){"unsetenv", &my_unsetenv};
  builtins[2] = (t_builtin){"alias", &get_data_alias};
  builtins[3] = (t_builtin){"unalias", &unalias};
  builtins[4] = (t_builtin){"setenv", &my_setenv};
  builtins[5] = (t_builtin){"cd", &my_change_dir};
  builtins[6] = (t_builtin){"exit", &my_exit};
  builtins[7] = (t_builtin){"help", &my_help};
  builtins[8] = (t_builtin){"jobs", &my_jobs};
  builtins[9] = (t_builtin){"fg", &my_fg};
  builtins[10] = (t_builtin){"echo", &my_echo};
  builtins[11] = (t_builtin){"env", &my_env};
  builtins[12] = (t_builtin){"printenv", &my_env};
}
