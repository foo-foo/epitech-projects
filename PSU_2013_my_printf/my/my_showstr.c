/*
** my_showstr.c for  in /home/menich_a/rendu/Piscine-C-Jour_06/ex_17
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Oct  8 08:49:34 2013 menich_a
** Last update Sun Nov 17 18:43:44 2013 menich_a
*/

void	second_part(char *str, int i)
{
  my_putchar(92);
  if (str[i] < 16)
    {
      my_putchar('0');
      if (str[i] < 10)
	{
	  my_putchar(str[i] + 48);
	}
      else
	{
	  my_putchar(str[i] + 87);
	}
    }
  else if (str[i] >= 16 && str[i] < 26)
    {
      my_putchar('1');
      my_putchar(str[i] + 32);
    }
  else
    {
      my_putchar('1');
      my_putchar(str[i] + 71);
    }
}

int	my_showstr(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] == 127)
	{
	  my_putchar(92);
	  my_putchar('7');
	  my_putchar('f');
	}
      else if (str[i] < ' ')
	{
	  second_part(str, i);
	}
      else
	{
	  my_putchar(str[i]);
	}
      i = i + 1;
    }
  return (0);
}
