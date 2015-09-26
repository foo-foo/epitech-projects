/*
** my_strncat.c for  in /home/menich_a/rendu/Piscine-C-Jour_07/ex_01
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Oct  8 15:53:06 2013 menich_a
** Last update Tue Oct  8 16:28:58 2013 menich_a
*/

int	my_count(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      i = i + 1;
    }
  return (i);
}

char	*my_strncat(char *dest, char *src, int nb)
{
  int	i;
  int	j;

  i = my_count(dest);
  j = 0;
  if (nb > my_count(src) || nb < 0)
    {
      nb = my_count(src);
    }
  while (j < nb)
    {
      dest[i] = src[j];
      i = i + 1;
      j = j + 1;
    }
  dest[i] = '\0';
  return (dest);
}
