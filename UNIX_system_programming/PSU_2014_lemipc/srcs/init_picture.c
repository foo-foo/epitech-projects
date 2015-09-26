/*
** init_pictur.c for  in /home/bencha_a/PSU_2014_lemipc
** 
** Made by Aniss Bencharif
** Login   <bencha_a@epitech.net>
** 
** Started on  Sat Mar  7 15:16:14 2015 Aniss Bencharif
** Last update Sun Mar  8 23:14:19 2015 Anatole Menichetti
*/

#include "../includes/graph.h"

void		load_img(char player, t_img *s, int i)
{
  if (player == 1)
    s->screens[i] = SDL_LoadBMP("imgs/cyan.bmp");
  if (player == 2)
    s->screens[i] = SDL_LoadBMP("imgs/green.bmp");
  if (player == 3)
    s->screens[i] = SDL_LoadBMP("imgs/yellow.bmp");
  if (player == 4)
    s->screens[i] = SDL_LoadBMP("imgs/purple.bmp");
  if (player == 5)
    s->screens[i] = SDL_LoadBMP("imgs/red.bmp");
  if (player == 6)
    s->screens[i] = SDL_LoadBMP("imgs/blue.bmp");
  SDL_BlitSurface(s->screens[i], NULL, s->screen, &s->pos);
  SDL_Flip(s->screen);
}

int		init_picture(SDL_Surface *screen, char *map, int size)
{
  t_img		s;
  int		i;
  int		x;
  int		y;

  i = 0;
  s.screens = malloc(size * size * sizeof(screen));
  s.screen = screen;
  if (screen == NULL)
    return (-1);
  if (map != NULL)
    {
      while (i < size * size)
        {
          get_pos(&x, &y, map[i], i, size);
          if (x != -42)
            {
              s.pos.y = x;
              s.pos.x = y;
	      load_img(map[i], &s, i);
            }
          i++;
        }
    }
  return (0);
}
