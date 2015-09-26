/*
** graph.h for  in /home/bencha_a/Desktop
** 
** Made by Aniss Bencharif
** Login   <bencha_a@epitech.net>
** 
** Started on  Fri Mar  6 14:30:21 2015 Aniss Bencharif
** Last update Sun Mar  8 23:21:33 2015 Anatole Menichetti
*/

#ifndef GRAPH_H_
# define GRAPH_H_

# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/msg.h>
# include "lemipc.h"

typedef struct	s_img
{
  SDL_Surface	**screens;
  SDL_Surface	*screen;
  SDL_Rect	pos;
}		t_img;

void	show_map(char *map, size_t m_size);

int	get_nbr_player(char *map, int size);

void	acces_shared_mem(SDL_Surface *screen);

int	manage_event(int s_event, SDL_Event event);

void	adjust_size(int *x, int *y, int i, int map_size);

void	get_pos(int *x, int *y, char map, int i, int size);

int	init_picture(SDL_Surface *screen, char *map, int size);

int	refresh_screen(int size, SDL_Surface *screen, int msg_id, int id);

#endif /* !GRAPH_H_ */
