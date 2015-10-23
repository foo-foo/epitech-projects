##
## Makefile for  in /home/menich_a/rendu/cpp_bomberman/Game
## 
## Made by Anatole Menichetti
## Login   <menich_a@epitech.net>
## 
## Started on  Tue May 15 06:46:59 2015 Anatole Menichetti
## Last update Tue Sep 15 07:26:35 2015 Anatole Menichetti
##

NAME		= bomberman

SRCS		= Core/Srcs/main.cpp \
		Core/Srcs/ABonus.cpp \
		Core/Srcs/AObject.cpp \
                Core/Srcs/APlayer.cpp \
                Core/Srcs/Block.cpp \
                Core/Srcs/Bomb.cpp \
                Core/Srcs/BombEngine.cpp \
                Core/Srcs/BonusBomb.cpp \
                Core/Srcs/BonusPower.cpp \
                Core/Srcs/BonusSpeed.cpp \
                Core/Srcs/Bot.cpp \
                Core/Srcs/Box.cpp \
                Core/Srcs/Character.cpp \
                Core/Srcs/Decode.cpp \
                Core/Srcs/Field.cpp \
		Core/Srcs/Flame.cpp \
                Core/Srcs/GameEngine.cpp \
                Core/Srcs/Ground.cpp \
                Core/Srcs/Human.cpp \
                Core/Srcs/Legend.cpp \
                Core/Srcs/Monster.cpp \
                Core/Srcs/Recruit.cpp \
                Core/Srcs/Soldier.cpp \
                Core/Srcs/Teub.cpp \
                Core/Srcs/Undecided.cpp \
                Core/Srcs/Wall.cpp \
                Core/Srcs/Warrior.cpp

INC		= -ICore/Headers -ILibBomberman_linux_x64/includes

OBJS		= $(SRCS:.cpp=.o)

CXX		= g++ $(INC) $(XLIB)

CXXFLAGS	= -W -Wall -Wextra -Werror

XLIB		= -L/usr/lib64 -L ./LibBomberman_linux_x64/libs/ -lgdl_gl -lGL -lGLEW -lfbxsdk -lSDL2 -lm -ldl -lrt\
 -g3 -lsfml-audio -L/usr/X11R6/lib -lpthread $(INC)


RM		= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) $(OBJS) -o $(NAME) $(XLIB)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
