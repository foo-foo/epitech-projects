/*
** my_strncmp.c for  in /home/menich_a/rendu/Piscine-C-Jour_06/ex_06
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Oct  7 17:28:13 2013 menich_a
** Last update Mon Oct  7 17:40:19 2013 menich_a
*/

int	my_strncmp(char *s1, char *s2, int n)
{
  int	i;

  i = 0;
  if (n <= 0)
    {
      return (0);
    }
  while (s1[i] == s2[i] && i < n - 1 && s1[i] != '\0')
    {
      i = i + 1;
    }
  return (s1[i] - s2[i]);
}
