/*
** my.h for libmy in /home/menich_a/rendu/Piscine-C-include
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Oct 10 16:46:02 2013 menich_a
** Last update Sun Nov 17 19:49:53 2013 menich_a
*/

#ifndef MY_H_
# define MY_H_

#include <stdarg.h>

void		my_putchar(char);

int		my_isneg(int);

int		my_put_nbr(int);

int		my_swap(int *, int *);

int		my_putstr(char *);

int		my_strlen(char *);

int		my_getnbr(char *);

void		my_sort_int_tab(int *, int);

int		my_power_rec(int, int);

int		my_square_root(int);

int		my_is_prime(int);

int		my_find_prime_sup(int);

char		 *my_strcpy(char *, char *);

char		 *my_strncpy(char *, char *, int);

char		 *my_revstr(char *);

char		 *my_strstr(char *, char *);

int		my_strcmp(char *, char *);

int		my_strncmp(char * , char *, int);

char		 *my_strupcase(char *);

char		 *my_strlowcase(char *);

char		 *my_strcapitalize(char *);

int		my_str_isalpha(char *);

int		my_str_isnum(char *);

int		my_str_islower(char *);

int		my_str_isupper(char *);

int		my_str_isprintable(char *);

int		my_showstr(char *);

int		my_showmem(char *, int);

char		 *my_strcat(char *, char *);

char		 *my_strncat(char *, char *, int);

int		my_strlcat(char *, char *, int);

int		my_printf(char *, ...);

char		 *from_base_ten(int, char *);

unsigned int	my_nbrlen(unsigned int);

int             my_showstr_oct(char *);

void            my_put_nbr_base(unsigned int, char *);

void            my_put_unsigned_nbr(unsigned int);

int             printf_unprintable_string(va_list, unsigned int);

int             printf_unsigned_binary(va_list, unsigned int);

int             printf_low_unsigned_hex(va_list, unsigned int);

int             printf_unsigned_hex(va_list, unsigned int);

int             printf_unsigned_int(va_list, unsigned int);

int             printf_unsigned_oct(va_list, unsigned int);

int             printf_pointer(va_list, unsigned int);

int             printf_string(va_list, unsigned int);

int             printf_char(va_list, unsigned int);

int             printf_int(va_list, unsigned int);

#endif /* !MY_H_*/
