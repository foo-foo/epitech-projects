//
// Block.hpp for  in /home/menich_a/rendu/cpp_bomberman/Game/Game/Headers
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Thu Jun 11 20:35:14 2015 Anatole Menichetti
// Last update Thu Jun 11 20:40:08 2015 Anatole Menichetti
//

#ifndef _BLOCK_HPP_
# define _BLOCK_HPP_

# include <iostream>
# include "AObject.hpp"
# include "Texture.hh"
# include "Geometry.hh"

class	Block : public AObject
{
private:
  gdl::Texture*	_texture;
  gdl::Geometry	_geometry;

  void		_initGeometry();

public:
  Block(gdl::Texture *, e_object);
  virtual ~Block() {};

  virtual bool	initialize();
  virtual void	draw(gdl::AShader&, gdl::Clock const &);
};

#endif /* !_BLOCK_HPP_ */
