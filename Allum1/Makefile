##
## Makefile for allum1 in /home/menich_a/rendu/Allum1
## 
## Made by menich_a
## Login   <menich_a@epitech.net>
## 
## Started on  Fri Feb  7 00:26:49 2014 menich_a
## Last update Sun Feb 16 22:03:09 2014 menich_a
##

NAME	= allum1

SRCS	= srcs/main.c \
	  srcs/allum1.c \
	  srcs/my_tools.c \
	  srcs/user_turn.c \
	  srcs/computer_turn.c \
	  srcs/key_pressed.c \
	  srcs/my_termcaps.c \
	  my/my_putstr.c \
	  my/my_putchar.c \
	  my/my_strncmp.c \
	  my/my_strlen.c \
	  my/my_getnbr.c \
	  my/my_free_tab.c \
	  my/my_find_in_str.c \
	  my/my_find_in_tab.c \
	  my/my_find_in_env.c

OBJS	= main.o \
	  allum1.o \
	  my_tools.o \
	  user_turn.o \
	  computer_turn.o \
	  key_pressed.o \
	  my_termcaps.o \
	  my_putchar.o \
	  my_strncmp.o \
	  my_putstr.o \
	  my_strlen.o \
	  my_getnbr.o \
	  my_free_tab.o \
	  my_find_in_str.o \
	  my_find_in_tab.o \
	  my_find_in_env.o

RM	= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
		cc -o $(NAME) $(OBJS) -lncurses

$(OBJS):	$(SRCS)
		cc -c $(SRCS) -I./includes -lncurses

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
