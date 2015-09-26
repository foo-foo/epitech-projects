//
// Ground.hpp for Ground in /home/rosain_f/rendu/cpp_bomberman/work_in_progress/v5
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Fri May 15 14:03:23 2015 Francois Rosain
// Last update Sat Jun 13 10:32:48 2015 Anatole Menichetti
//

#ifndef _GROUND_HPP_
# define _GROUND_HPP_

# include <iostream>

# include "AObject.hpp"
# include "Texture.hh"
# include "Geometry.hh"

class	Ground : public AObject
{
private:
  gdl::Texture*	_texture;
  gdl::Geometry	_geometry;

public:
  Ground(gdl::Texture*);
  virtual ~Ground() {};

  virtual bool	initialize();
  virtual void	draw(gdl::AShader&, gdl::Clock const &);
};

#endif /* !_GROUND_HPP_ */
