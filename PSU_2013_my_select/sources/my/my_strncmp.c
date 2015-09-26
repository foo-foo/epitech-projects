/*
** my_strncmp.c for libmy.a in /home/menich_a/rendu/PSU_2013_minishell1/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Jan  3 11:49:55 2014 menich_a
** Last update Tue Jan 14 14:20:44 2014 menich_a
*/

int	my_strncmp(char *s1, char *s2, int n)
{
  int	i;

  i = 0;
  while (s1[i] == s2[i] && s1[i] != '\0' && i < n)
    {
      i = i + 1;
    }
  return (s1[i] - s2[i]);
}
