/*
** my_strncpy.c for  in /home/menich_a/rendu/Piscine-C-Jour_06
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Oct  7 09:12:09 2013 menich_a
** Last update Wed Oct  9 14:14:15 2013 menich_a
*/

int	my_strlen3(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      i = i + 1;
    }
  return (i);
}

char	*my_strncpy(char *dest, char *src, int n)
{
  int	i;

  i = 0;
  if (n > my_strlen3(src))
    {
      n = my_strlen3(src);
    }
  while (i < n && src[i] != '\0')
    {
      dest[i] = src[i];
      i = i + 1;
    }
  return (dest);
}
