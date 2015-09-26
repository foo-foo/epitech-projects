//
// Cube.hpp for Cube in /home/rosain_f/projects/BomberMan/cube/v2
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Tue May  5 10:35:38 2015 Francois Rosain
// Last update Thu Jun 11 20:41:55 2015 Anatole Menichetti
//

#ifndef _BOX_HPP_
# define _BOX_HPP_

# include "Block.hpp"

class	Box : public Block
{
public:
  Box(gdl::Texture*);
  virtual ~Box() {};
};

#endif /* !_BOX_HPP_ */
