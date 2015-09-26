##
## Makefile for liblist in /home/menich_a/rendu/PSU_2013_my_ls/include_and_lib/list
## 
## Made by menich_a
## Login   <menich_a@epitech.net>
## 
## Started on  Thu Nov 28 14:11:52 2013 menich_a
## Last update Sun Dec  1 21:13:14 2013 menich_a
##

NAME	= liblist.a

SRCS	= my_put_in_list.c \
	  my_show_long_list.c \
	  my_list_size.c \
	  my_sort_list.c \
	  my_create_list.c \
	  ../../my_tools.c

OBJS	= my_put_in_list.o \
	  my_show_long_list.o \
	  my_list_size.o \
	  my_sort_list.o \
	  my_create_list.o \
	  my_tools.o

RM	= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)
	cp $(NAME) ..

$(OBJS):	$(SRCS)
	cc -c $(SRCS) -I../../include -lmy -L..

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all
