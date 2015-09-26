//
// main.cpp for main in /home/rosain_f/projects/zappy/graphic
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Mon Jun 29 08:56:22 2015 Francois Rosain
// Last update Mon Jun 29 16:06:33 2015 Francois Rosain
//

#include "Map.hpp"
#include "GraphicEngine.hpp"

int	main()
{
  Map		map(20,10);
  GraphicEngine ge(map);
  
  if (!ge.initialize())
    {
      std::cout << "Error : Can\'t initialize GraphicEngine." << std::endl;
      return (-1);
    }
  while (ge.update())
    ge.draw();
  return (0);
}
