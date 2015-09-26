//
// Thystane.hpp for Thystane in /home/rosain_f/rendu/PSU_2014_zappy/GraphicEngine/Srcs
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Wed Jul  1 15:45:06 2015 Francois Rosain
// Last update Wed Jul  1 15:45:24 2015 Francois Rosain
//

#ifndef _THYSTANE_
# define _THYSTANE_

/* LibGDL */
# include "Texture.hh"
# include "Geometry.hh"

/* Thystane */
# include "ARessource.hpp"


class	Thystane : public ARessource
{  
public:
  Thystane(gdl::Model& model) : ARessource(model, THYSTANE) {};
  ~Thystane() {};
};

#endif /* !_THYSTANE_ */
