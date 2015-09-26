/*
** char_check.c for  in /home/auduri_a/rendu/PSU_2014_myirc
** 
** Made by audurier julien
** Login   <auduri_a@epitech.net>
** 
** Started on  Sat Apr 11 12:34:50 2015 audurier julien
** Last update Sun Apr 12 11:23:20 2015 Anatole Menichetti
*/

int	char_is_num(char c)
{
  if (c >= '0' && c <= '9')
    return (0);
  else
    return (-1);
}

int	char_is_alpha(char c)
{
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    return (0);
  else
    return (-1);
}

int	char_is_spe(char c)
{
  if (c == '-' || c == '[' || c == ']' || c =='\\' || c == '`'
      || c == '^' || c == '{' || c == '}')
    return (0);
  else
    return (-1);
}
