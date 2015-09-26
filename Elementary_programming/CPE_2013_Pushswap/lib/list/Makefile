##
## Makefile for liblist.a in /home/menich_a/utilities/liblist
## 
## Made by menich_a
## Login   <menich_a@epitech.net>
## 
## Started on  Wed Oct 23 07:44:19 2013 menich_a
## Last update Mon Jan  6 23:13:30 2014 menich_a
##

NAME	= liblist.a

SRCS	= my_create_list.c \
	  my_put_in_list.c \
	  my_put_end_list.c \
	  my_show_list.c \
	  my_list_size.c \
	  my_is_sorted.c \
	  my_rm_from_list.c \
	  my_rm_list.c

OBJS	= my_create_list.o \
	  my_put_in_list.o \
	  my_put_end_list.o \
	  my_show_list.o \
	  my_list_size.o \
	  my_is_sorted.o \
	  my_rm_from_list.o \
	  my_rm_list.o

RM	= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
		ar rc	$(NAME) $(OBJS)
		ranlib	$(NAME)
		cp	$(NAME) ..

$(OBJS):	$(SRCS)
		cc -c $(SRCS) -I../../include

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
