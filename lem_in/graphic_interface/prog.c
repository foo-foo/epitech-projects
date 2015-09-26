/*
** prog.c for prog.c in /home/benoit_l/rendu/my_select
** 
** Made by Benoit Leo
** Login   <benoit_l@epitech.net>
** 
** Started on  Wed Jan 15 09:09:01 2014 Benoit Leo
** Last update Sun May  4 18:20:29 2014 menich_a
*/

#include <unistd.h>
#include <stdlib.h>

void	my_putchar(char x)
{
  write(1, &x, 1);
}

int	my_strlen(char *str)
{
  int	x;

  x = 0;
  while (str[x] != '\0')
    x = x + 1;
  return (x);
}

void	my_putstr(char *str)
{
  write(1, str, my_strlen(str));
}

int	my_getnbr(char *str)
{
  int	i;
  int	j;
  int	res;

  i = 0;
  res = 0;
  while (str[i] < '0' || str[i] > '9')
    i = i + 1;
  j = i - 1;
  while (str[i] >= '0' && str[i] <= '9')
    {
      res = (res * 10) + (str[i] - 48);
      i = i + 1;
    }
  if (res <= -2147483648 || res >= 2147483647)
    return (0);
  if (str[j] == '-')
    return (-res);
  return (res);
}

char	*my_strcat(char *dest, char *src)
{
  int	i;
  int	j;
  char	*tmp;

  j = 0;
  i = 0;
  tmp = malloc(sizeof(char) * (my_strlen(dest) + my_strlen(src) + 5));
  if (tmp == NULL)
    return (NULL);
  while (dest[i] != '\0')
    {
      tmp[i] = dest[i];
      i++;
    }
  if (src != NULL)
    while (src[j] != '\0')
      tmp[i++] = src[j++];
  tmp[i] = '\0';
  return (tmp);
}
