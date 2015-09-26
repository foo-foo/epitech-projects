/*
** my_strcmp.c for libmy.a  in /home/menich_a/rendu/CPE_2013_Pushswap/lib/my
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Jan  6 22:28:32 2014 menich_a
** Last update Mon Jan  6 22:37:50 2014 menich_a
*/

int	my_strcmp(char *s1, char *s2)
{
  int	i;

  while (s1[i] == s2[i] && s1[i] != '\0')
    {
      i = i + 1;
    }
  return (s1[i] - s2[i]);
}
