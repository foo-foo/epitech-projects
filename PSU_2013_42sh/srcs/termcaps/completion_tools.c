/*
** completion_tools.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2/srcs/termcaps
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri May  9 17:52:39 2014 menich_a
** Last update Fri May 30 17:47:50 2014 menich_a
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "get_next_line.h"
#include "my_termios.h"
#include "my.h"

int		complete_line(t_line *line, char **tab)
{
  int		i;
  int		j;
  char		*tmp;

  j = 0;
  i = line->i;
  while (i >= 0 && line->line[i] != ' ' && line->line[i] != '/')
    i = i - 1;
  i = i + 1;
  while (line->line[i] == tab[0][j] && line->line[i] && tab[0][j])
    {
      i = i + 1;
      j = j + 1;
    }
  tmp = my_str_catdup(line->line, tab[0] + j);
  if (tmp == NULL)
    return (-1);
  free(line->line);
  line->line = tmp;
  line->i = my_strlen(line->line);
  line->size = my_strlen(line->line) + 1;
  my_putstr(tab[0] + j);
  my_free_tab(tab);
  return (0);
}

int		half_complete_line(t_line *line, char **tab)
{
  char		*str;
  int		i;
  int		j;

  i = 0;
  while (tab[0][i])
    {
      j = 1;
      while (tab[j] && tab[j][i] == tab[0][i])
        j = j + 1;
      if (tab[j])
        break;
      i = i + 1;
    }
  if ((str = my_strndup(tab[0], i)) == NULL)
    return (-1);
  my_free_tab(tab);
  tab = malloc(sizeof(*tab) * 2);
  if (!tab)
    return (msg_error("mysh: error: malloc failed.\n"));
  tab[0] = str;
  tab[1] = NULL;
  return (complete_line(line, tab));
}

char		**add_one_choice(char **tab, char *choice, int check)
{
  int		i;
  struct stat	*stat;

  i = 0;
  if (check == 1)
    {
      if ((stat = malloc(sizeof(*stat))) == NULL)
	return (msg_error_return("mysh: error: realloc failed.\n", 0));
      lstat(choice, stat);
      if ((stat->st_mode & S_IFDIR) != 0)
        choice = my_str_catdup(choice, "/");
      free(stat);
    }
  while (tab && tab[i] && my_strcmp(choice, tab[i]))
    i = i + 1;
  if (tab && tab[i])
    return (tab);
  if ((tab = realloc(tab, sizeof(*tab) * (i + 2))) == NULL)
    return (msg_error_return("mysh: error: realloc failed.\n", 0));
  if ((tab[i] = my_strdup(choice)) == NULL)
    return (NULL);
  tab[i + 1] = NULL;
  return (tab);
}



void		display_choice_tab(char **tab, t_line *line)
{
  int		i;

  i = 0;
  my_putchar('\n');
  while (tab[i])
    {
      my_putstr(tab[i]);
      my_putchar('\t');
      i = i + 1;
    }
  my_putchar('\n');
  display_prompt(NULL, 0, 0);
  my_putstr(line->line);
  i = line->size;
  while (--i > line->i)
    launch_termcap(MOVE_LEFT);
  my_free_tab(tab);
}

int		check_before_display(char **tab)
{
  int		ret;
  char		buff[BUFF_SIZE + 1];

  my_putstr("\nDisplay all ");
  my_put_nbr(my_tablen(tab));
  my_putstr(" possibilities? (y or n)");
  while ((ret = read(0, buff, BUFF_SIZE)) > 0)
    if (buff[0] == 'y' || buff[0] == 'n')
      break;
  if (ret <= 0 || buff[0] == 'n')
    {
      my_putchar('\n');
      display_prompt(NULL, 0, 0);
      my_free_tab(tab);
      return (1);
    }
  return (0);
}
