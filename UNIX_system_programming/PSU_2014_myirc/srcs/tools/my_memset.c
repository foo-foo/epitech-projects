/*
** my_memset.c for  in /home/auduri_a/rendu/PSU_2014_myirc
** 
** Made by audurier julien
** Login   <auduri_a@epitech.net>
** 
** Started on  Fri Apr 10 11:28:00 2015 audurier julien
** Last update Fri Apr 10 11:28:02 2015 audurier julien
*/

char	*my_memset(char *str, int len)
{
  int	i;

  i = 0;
  while (i < len)
      str[i++] = '\0';
  return (str);
}
