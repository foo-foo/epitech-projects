/*
** graph.c for graph.c in /home/benoit_l/rendu/lem-in
** 
** Made by Benoit Leo
** Login   <benoit_l@epitech.net>
** 
** Started on  Tue Apr 22 10:59:42 2014 Benoit Leo
** Last update Sun May  4 19:43:13 2014 menich_a
*/

#include <unistd.h>
#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

int		gerekey(int keycode, void *param)
{
  if (keycode == 65307)
    exit(0);
  return (0);
}

int		put_pixel_image(t_img *img, int x, int y, int c1, int c2, int c3)
{
  int		pos;

  if (x >= img->width || y >= img->height || x < 0 || y < 0)
    return (1);
  pos = (y * img->szline) + (x * 4);
  img->data[pos] = c1;
  img->data[pos + 1] = c2;
  img->data[pos + 2] = c3;
  return (0);
}

void		trace_connections(t_coord *first_room, t_coord *coord, t_img *img)
{
  int		i;
  t_coord	*room;
  char		**connections;

  connections = coord->connection;
  i = 0;
  if (connections)
    while (connections[i])
      {
	room = first_room;
	while (room && strcmp(room->room_name, connections[i]))
	  room = room->next;
	if (room)
	  {
	    draw_line(img, (coord->x * 10 + 1) % 1500,
		   (coord->y * 10 + 1) % 850 + 150, (room->x * 10 + 1) % 1500,
		   (room->y * 10 + 1) % 850 + 150);
	  }
	i = i + 1;
      }
}

void		anthill(t_img *img, t_img *lem, char *buff, t_coord *coord)
{
  t_ant		*ants;
  t_coord	*rooms;
  char		**way;

  put_square(lem, buff);
  rooms = coord;
  while (rooms)
    {
      if (rooms->check > 0)
	put_circle(img, (rooms->x * 10 + 1) % 1500,
		 (rooms->y * 10 + 1) % 850 + 150, 40);
      else
    	put_circle(img, (rooms->x * 10 + 1) % 1500,
		 (rooms->y * 10 + 1) % 850 + 150, 20);
      trace_connections(coord, rooms, img);
      rooms = rooms->next;
    }
  gereexpose(img);
  way = get_way(NULL);
  ants = create_ants_list(get_nbr_ants(NULL), coord);
  move_ants(way, coord, ants, lem);
}

int		main()
{
  t_img		*img;
  t_img		*lem;
  char		*buff;
  t_coord	*coord;

  sleep(5);
  coord = NULL;
  coord = get_room_coord(get_data(), coord, 0);
  if ((buff = strdup(ANT_IMG)) == NULL)
    return (1);
  img = creat_img(img);
  lem = creat_ants(lem, img);
  sky(img);
  grass(img);
  ground(img);
  anthill(img, lem, buff, coord);
  mlx_key_hook(img->window, &gerekey, img);
  mlx_expose_hook(img->window, &gereexpose, img);
  mlx_expose_hook(img->window, &gereexpose_coord, img);
  mlx_loop(img->init);
  return (0);
}
