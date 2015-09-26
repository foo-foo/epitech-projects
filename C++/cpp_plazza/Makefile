##
## Makefile for cpp_plazza in /home/menich_a/rendu/cpp_plazza
## 
## Made by Anatole Menichetti
## Login   <menich_a@epitech.net>
## 
## Started on  Wed Apr 15 17:29:42 2015 Anatole Menichetti
## Last update Thu Apr 23 17:39:05 2015 Anatole Menichetti
##

NAME		= plazza

SRCS		= srcs/main.cpp				\
		  srcs/Parser.cpp			\
		  srcs/Reception.cpp			\
		  srcs/Order.cpp			\
		  srcs/Command.cpp			\
		  srcs/Resources.cpp			\
		  srcs/Kitchen.cpp			\
		  srcs/Cook.cpp				\
		  srcs/NamedPipe.cpp			\
		  srcs/ScopedLock.cpp			\
		  srcs/Mutex.cpp			\
		  srcs/exceptions/PlazzaError.cpp	\
		  srcs/exceptions/RuntimeError.cpp	\
		  srcs/exceptions/BadCommandError.cpp	\
		  srcs/exceptions/ArgError.cpp

OBJS		= $(SRCS:.cpp=.o)

CXXFLAGS	= -W -Wall -Wextra -I./includes -g -pthread

CC		= g++

RM		= rm -rf

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) -pthread

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
