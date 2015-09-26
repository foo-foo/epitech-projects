/*
** echo2.c for  in /home/bencha_a/echo
** 
** Made by bencharif
** Login   <bencha_a@epitech.net>
** 
** Started on  Thu May 22 21:40:51 2014 bencharif
** Last update Sat May 31 13:54:24 2014 menich_a
*/

#include "mysh.h"
#include "my.h"

void	my_special_putstr(char *str)
{
  int	i;
  int	j;
  char	tab[] = "abefnrtv";
  char	tab2[] = "\a\b\e\f\n\r\t\v";

  i = 0;
  while (str[i])
    {
      j = 0;
      if (str[i] == '\\')
	{
	  while (tab[j] && str[i + 1] != tab[j])
	    j++;
	  if (tab[j])
	    {
	      my_putchar(tab2[j]);
	      i++;
	    }
	  else
	    my_putchar(str[i]);
	}
      else
	my_putchar(str[i]);
      i++;
   }
}

void	get_echo_options(char **cmd, t_state *state)
{
  int	i;
  int	j;

  i = 1;
  state->n_state = 0;
  state->e_state = 0;
  while (cmd[i] && cmd[i][0] == '-')
    {
      j = 1;
      while (cmd[i][j])
	{
	  if (cmd[i][j] == 'e')
	    state->e_state = 1;
	  if (cmd[i][j] == 'E')
	    state->e_state = 0;
	  if (cmd[i][j] == 'n')
	    state->n_state = 1;
	  j = j + 1;
	}
      i++;
    }
}

char	**my_echo(char **cmd, char **env)
{
  int		i;
  t_state	state;

  i = 1;
  get_echo_options(cmd, &state);
  while (cmd[i] && cmd[i][0] == '-' &&
	 (cmd[i][1] == 'e' || cmd[i][1] == 'E' || cmd[i][1] == 'n'))
    i++;
  while (cmd[i])
    {
      if (state.e_state == 1)
	my_special_putstr(cmd[i]);
      else
	my_putstr(cmd[i]);
      if (cmd[i + 1])
	my_putchar(' ');
      i++;
    }
  if (state.n_state == 0)
    my_putchar('\n');
  return (env);
}
