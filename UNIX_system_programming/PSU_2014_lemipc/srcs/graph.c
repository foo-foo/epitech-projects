/*
** test.c for  in /home/bencha_a/Desktop/lemipc
** 
** Made by Aniss Bencharif
** Login   <bencha_a@epitech.net>
** 
** Started on  Tue Mar  3 12:34:06 2015 Aniss Bencharif
** Last update Sun Mar  8 23:19:47 2015 Anatole Menichetti
*/

#include "../includes/graph.h"

int		main(void)
{
  SDL_Surface	*screen;
  SDL_Event	event;
  int		s_event;

  s_event = 1;
  screen = NULL;
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
      printf("lemipc graphic: cannot init SDL:  %s\n", SDL_GetError());
      return (EXIT_FAILURE);
    }
  atexit(SDL_Quit);
  screen = SDL_SetVideoMode(1024 , 1024, 16, SDL_HWSURFACE);
  SDL_WM_SetCaption("Lemipc", NULL);
  if (screen == NULL)
    {
      printf("lemipc graphic: cannot set video mode: %s\n", SDL_GetError());
      return (EXIT_FAILURE);
    }
  acces_shared_mem(screen);
  manage_event(s_event, event);
  return (EXIT_SUCCESS);
}

int		manage_event(int s_event, SDL_Event event)
{
  while (s_event != 1)
    {
      SDL_PollEvent(&event);
      if (event.type == SDL_QUIT)
	s_event = 1;
      if (event.type == SDL_KEYDOWN)
	if (event.key.keysym.sym == SDLK_ESCAPE)
	  s_event = 1;
    }
  return (EXIT_SUCCESS);
}
