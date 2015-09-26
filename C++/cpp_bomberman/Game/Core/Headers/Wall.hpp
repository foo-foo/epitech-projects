//
// Cube.hpp for Cube in /home/rosain_f/projects/BomberMan/cube/v2
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Tue May  5 10:35:38 2015 Francois Rosain
// Last update Thu Jun 11 20:40:40 2015 Anatole Menichetti
//

#ifndef _WALL_HPP_
# define _WALL_HPP_

# include "Block.hpp"

class	Wall : public Block
{
public:
  Wall(gdl::Texture*);
  virtual ~Wall() {};
};

#endif /* !_WALL_HPP_ */
