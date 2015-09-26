//
// Sibur.hpp for Sibur in /home/rosain_f/rendu/PSU_2014_zappy/GraphicEngine/Srcs
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Wed Jul  1 15:44:09 2015 Francois Rosain
// Last update Wed Jul  1 15:44:21 2015 Francois Rosain
//

#ifndef _SIBUR_
# define _SIBUR_

/* LibGDL */
# include "Texture.hh"
# include "Geometry.hh"

/* Sibur */
# include "ARessource.hpp"


class	Sibur : public ARessource
{  
public:
  Sibur(gdl::Model& model) : ARessource(model, SIBUR) {};
  ~Sibur() {};
};

#endif /* !_SIBUR_ */
