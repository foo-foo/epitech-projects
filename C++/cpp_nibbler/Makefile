##
## Makefile for nibbler in /home/menich_a/rendu/cpp_nibbler
## 
## Made by Anatole Menichetti
## Login   <menich_a@epitech.net>
## 
## Started on  Thu Apr  2 16:21:38 2015 Anatole Menichetti
## Last update Sun Apr  5 23:32:23 2015 audurier julien
##

nibbler		= nibbler

ncurses		= lib_nibbler_ncurses.so

sdl		= lib_nibbler_sdl.so

opengl		= lib_nibbler_opengl.so

SRCS		= srcs/main.cpp		\
		  srcs/AGui.cpp		\
		  srcs/Parser.cpp	\
		  srcs/DLLoader.cpp	\
		  srcs/NibError.cpp	\
		  srcs/Nibbler.cpp

OBJS		= $(SRCS:.cpp=.o)

NCURSES_SRCS	= ncurses/Gui.cpp	\
		  srcs/NibError.cpp	\
		  srcs/AGui.cpp		\
		  srcs/Nibbler.cpp

SDL_SRCS	= sdl/Gui.cpp		\
		  srcs/AGui.cpp		\
		  srcs/Nibbler.cpp	\
		  srcs/NibError.cpp

OPENGL_SRCS	= opengl/Gui.cpp	\
		  srcs/NibError.cpp	\
		  srcs/AGui.cpp		\
		  srcs/Nibbler.cpp

RM		= rm -f

CC		= g++

CXXFLAGS	= -W -Wall -Wextra -Werror -std=c++11

all:            $(nibbler) $(ncurses) $(sdl) $(opengl)

$(nibbler):	$(OBJS)
		$(CC) -o $(nibbler) $(OBJS) -ldl -pthread

$(ncurses):	$(NCURSES_SRCS)
		$(CC) -shared -fpic -lncurses $(NCURSES_SRCS) -o $(ncurses)

$(sdl):		$(SDL_SRCS)
		$(CC) -shared -fpic -lSDL -lSDLmain -lSDL_ttf $(SDL_SRCS) -o $(sdl)

$(opengl):	$(OPENGL_SRCS)
		$(CC) -shared -fpic -lSDL -lSDLmain -lGLU -lGL -lSDL_ttf $(OPENGL_SRCS) -o $(opengl)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(ncurses) $(sdl) $(opengl) $(nibbler)

re:		fclean all

.PHONY:		all clean fclean re
