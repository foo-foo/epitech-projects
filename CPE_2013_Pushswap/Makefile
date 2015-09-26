##
## Makefile for push_swap in /home/menich_a/rendu/CPE_2013_push_swap
## 
## Made by menich_a
## Login   <menich_a@epitech.net>
## 
## Started on  Mon Dec  9 15:20:02 2013 menich_a
## Last update Mon Jan  6 17:34:53 2014 menich_a
##

NAME	= push_swap

SRCS	= sources/push_swap.c \
	  sources/l_a_operations.c \
	  sources/l_b_operations.c \
	  sources/double_operations.c

OBJS	= push_swap.o \
	  l_a_operations.o \
	  l_b_operations.o \
	  double_operations.o

CLIB	= -lmy -llist -L./lib -I./include

RM	= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
		cc -o $(NAME) $(OBJS) $(CLIB)

$(OBJS):	$(SRCS)
		cd lib/my && $(MAKE)
		cd lib/my && $(MAKE)
		cc -c $(SRCS) $(CLIB)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

