##
## Makefile for my_ls in /home/menich_a/rendu/PSU_2013_my_ls
## 
## Made by menich_a
## Login   <menich_a@epitech.net>
## 
## Started on  Mon Nov 25 12:14:40 2013 menich_a
## Last update Sun Dec  1 21:50:51 2013 menich_a
##

NAME	= my_ls

SRCS	= main.c \
	  my_ls.c \
	  my_options.c \
	  clean_list_syntax.c \
	  my_tools.c

OBJS	= main.o \
	  my_ls.o \
	  my_options.o \
	  clean_list_syntax.o \
	  my_tools.o

LIB	= -lmy -llist -L./lib -I./include

RM	= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
	cc -o $(NAME) $(OBJS) $(LIB)

$(OBJS):	$(SRCS)
	cc -c $(SRCS) $(LIB)

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all
