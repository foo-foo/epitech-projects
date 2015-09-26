##
## Makefile for libmy.a in /home/menich_a/rendu/Piscine-C-lib/my
## 
## Made by menich_a
## Login   <menich_a@epitech.net>
## 
## Started on  Mon Oct 21 08:04:46 2013 menich_a
## Last update Thu Nov 28 14:18:30 2013 menich_a
##

NAME	= libmy.a

SRCS	= my_find_prime_sup.c \
	  my_getnbr.c \
	  my_isneg.c \
	  my_is_prime.c \
	  my_power_rec.c \
	  my_putchar.c \
	  my_put_nbr.c \
	  my_putstr.c \
	  my_revstr.c \
	  my_showmem.c \
	  my_showstr.c \
	  my_sort_int_tab.c \
	  my_square_root.c \
	  my_strcapitalize.c \
	  my_strcat.c \
	  my_strcmp.c \
	  my_strcpy.c \
	  my_str_isalpha.c \
	  my_str_islower.c \
	  my_str_isnum.c \
	  my_str_isprintable.c \
	  my_str_isupper.c \
	  my_strlcat.c \
	  my_strlen.c \
	  my_strlowcase.c \
	  my_strncat.c \
	  my_strncmp.c \
	  my_strncpy.c \
	  my_strstr.c \
	  my_strupcase.c \
	  my_swap.c \
	  my_printf.c \
	  unsigned_printf_functions.c \
	  basic_printf_functions.c \
	  my_printf_tools.c \

OBJS	= my_find_prime_sup.o \
	  my_getnbr.o \
	  my_isneg.o \
	  my_is_prime.o \
	  my_power_rec.o \
	  my_putchar.o \
	  my_put_nbr.o \
	  my_putstr.o \
	  my_revstr.o \
	  my_showmem.o \
	  my_showstr.o \
	  my_sort_int_tab.o \
	  my_square_root.o \
	  my_strcapitalize.o \
	  my_strcat.o \
	  my_strcmp.o \
	  my_strcpy.o \
	  my_str_isalpha.o \
	  my_str_islower.o \
	  my_str_isnum.o \
	  my_str_isprintable.o \
	  my_str_isupper.o \
	  my_strlcat.o \
	  my_strlen.o \
	  my_strlowcase.o \
	  my_strncat.o \
	  my_strncmp.o \
	  my_strncpy.o \
	  my_strstr.o \
	  my_strupcase.o \
	  my_swap.o \
	  my_printf.o \
	  unsigned_printf_functions.o \
	  basic_printf_functions.o \
	  my_printf_tools.o \

all:		$(NAME)

$(NAME):	$(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)
	cp $(NAME) ..

$(OBJS):	$(SRCS)
	cc -c $(SRCS) -I../../include

clean:
	rm -f $(OBJS)

fclean:		clean
	rm -f $(NAME)

re:		fclean all
