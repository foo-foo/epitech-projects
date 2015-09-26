/*
** my_strlcat.c for  in /home/menich_a/rendu/Piscine-C-Jour_07/ex_01
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Oct  8 18:02:30 2013 menich_a
** Last update Wed Oct  9 13:48:11 2013 menich_a
*/

int	my_count2(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      i = i + 1;
    }
  return (i);
}

int	my_strlcat(char *dest, char *src, int size)
{
  int	i;
  int	j;

  i = my_count2(src);
  j = my_count2(dest);
  if (i == 0)
    {
      if (size < j)
	return (size);
      if (size >= j)
	return (j);
    }
  else
    {
      if (size < j)
	return (i + size);
      else
	return (i + j);
    }
  return (0);
}
