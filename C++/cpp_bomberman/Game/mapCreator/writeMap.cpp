//
// writeMap.cpp for  in /home/menich_a/rendu/cpp_bomberman/Game
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Sun Jun 14 18:09:20 2015 Anatole Menichetti
// Last update Sun Jun 14 18:40:52 2015 Anatole Menichetti
//

#include <cstdlib>
#include <iostream>
#include <vector>

void    createWall(int nb, std::vector<std::vector<char> > &map)
{
  size_t        y, x;

  y = 0;
  while (y < nb)
    {
      map.push_back(std::vector<char>(nb));
      x = 0;
      while (x < nb)
        {
          map[y][x] =
            (((x % 2) == 1 && (y % 2) == 1)) ? 'W'  : '-';
          ++x;
        }
      ++y;
    }
}

void    createBoxY(int nb, std::vector<std::vector<char> > &map)
{
  size_t        y, x;

  //etape 2 : mis en plase de mur cassable sur les adresse x inpaire                                                          
  y = 0;
  while (y < nb / 2)
    {
      x = 0;
      while (!(y % 2) && x < y)
        {
          if (map[y][x] == '-')
            map[y][x] = 'B';
          if (map[y][nb - x - 1] == '-')
            map[y][nb - x - 1] = 'B';
          if (map[nb - y - 1][nb - x - 1] == '-')
            map[nb - y - 1][nb - x - 1] = 'B';
          if (map[nb - y - 1][x] == '-')
            map[nb - y - 1][x] = 'B';
          ++x;
        }
      ++y;
    }
}

void    createBoxX(int nb, std::vector<std::vector<char> > &map)
{
  size_t        y, x;

  //etape 3 : mis en plase de mur cassable sur les adresse y inpaire                                                          
  x = 0;
  while (x < nb / 2)
    {
      y = 0;
      while (x && !(x % 2) && y < x + 1)
        {
          if (map[y][x] == '-')
            map[y][x] = 'B';
          if (map[nb - y - 1][x] == '-')
            map[nb - y - 1][x] = 'B';
          if (map[nb - y - 1][nb - x - 1] == '-')
            map[nb - y - 1][nb - x - 1] = 'B';
          if (map[y][nb - x - 1] == '-')
            map[y][nb - x - 1] = 'B';
          ++y;
        }
      ++x;
    }
}


int main(int ac, char **av)
{
  if (ac > 1)
    {
      int nb = atoi(av[1]);
      std::vector<std::vector<char> > map;

      createWall(nb, map);
      createBoxY(nb, map);
      createBoxX(nb, map);

      for (int y = 0; y < nb; y++){
	for (int x = 0; x < nb; x++)
	  std::cout << map[y][x];
	std::cout << std::endl;
      }
    }
  return 0;
}
