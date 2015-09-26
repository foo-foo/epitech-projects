//
// Mendiane.hpp for Mendiane in /home/rosain_f/rendu/PSU_2014_zappy/GraphicEngine/Srcs
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Wed Jul  1 15:44:31 2015 Francois Rosain
// Last update Wed Jul  1 15:44:59 2015 Francois Rosain
//

#ifndef _MENDIANE_
# define _MENDIANE_

/* LibGDL */
# include "Texture.hh"
# include "Geometry.hh"

/* Mendiane */
# include "ARessource.hpp"


class	Mendiane : public ARessource
{  
public:
  Mendiane(gdl::Model& model) : ARessource(model, MENDIANE) {};
  ~Mendiane() {};
};

#endif /* !_MENDIANE_ */
