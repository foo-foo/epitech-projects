##
## Makefile for my_select in /home/menich_a/rendu/PSU_2013_my_select/include
## 
## Made by menich_a
## Login   <menich_a@epitech.net>
## 
## Started on  Fri Jan 10 13:23:17 2014 menich_a
## Last update Sun Jan 19 20:15:15 2014 menich_a
##

NAME	= my_select

SRCS	= sources/main.c \
	  sources/my_init.c \
	  sources/my_select.c \
	  sources/display_list.c \
	  sources/dynamic_research_mode.c \
	  sources/termcaps/my_termcaps.c \
	  sources/termcaps/my_cursor_termcaps.c \
	  sources/my_tools.c \
	  sources/my/my_msg_error_return.c \
	  sources/my/my_putchar.c \
	  sources/my/my_putstr.c \
	  sources/my/my_strlen.c \
	  sources/my/my_strcmp.c \
	  sources/my/my_strncmp.c \
	  sources/my/my_strdup.c \
	  sources/my/my_strncat.c \
	  sources/list/my_create_list.c \
	  sources/list/my_list_size.c \
	  sources/list/my_put_end_list.c \
	  sources/list/my_rm_from_list.c \
	  sources/list/my_rm_list.c

OBJS	= main.o \
	  my_init.o \
	  my_select.o \
	  display_list.o \
	  dynamic_research_mode.o \
	  my_termcaps.o \
	  my_cursor_termcaps.o \
	  my_tools.o \
	  my_msg_error_return.o \
	  my_putchar.o \
	  my_putstr.o \
	  my_strlen.o \
	  my_strcmp.o \
	  my_strncmp.o \
	  my_strdup.o \
	  my_strncat.o \
	  my_create_list.o \
	  my_list_size.o \
	  my_put_end_list.o \
	  my_rm_from_list.o \
	  my_rm_list.o

CLIB	= -lncurses -I./include

RM	= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
		cc -o $(NAME) $(OBJS) $(CLIB)

$(OBJS):	$(SRCS)
		cc -c $(SRCS) $(CLIB)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
