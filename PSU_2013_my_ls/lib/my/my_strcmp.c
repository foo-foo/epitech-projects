/*
** my_strcmp.c for  in /home/menich_a/rendu/Piscine-C-Jour_06/ex_05
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Oct  7 16:43:06 2013 menich_a
** Last update Mon Oct  7 17:19:47 2013 menich_a
*/

int	my_strcmp(char *s1, char *s2)
{
  int	i;
  int	res;

  i = 0;
  while (s1[i] == s2[i] && s1[i] != '\0')
    {
      i = i + 1;
    }
  res = s1[i] - s2[i];
  return (res);
}
