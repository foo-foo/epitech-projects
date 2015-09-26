//
// Phiras.hpp for Phiras in /home/rosain_f/rendu/PSU_2014_zappy/GraphicEngine/Srcs
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Wed Jul  1 15:43:51 2015 Francois Rosain
// Last update Wed Jul  1 15:43:58 2015 Francois Rosain
//

#ifndef _PHIRAS_
# define _PHIRAS_

/* LibGDL */
# include "Texture.hh"
# include "Geometry.hh"

/* Phiras */
# include "ARessource.hpp"


class	Phiras : public ARessource
{  
public:
  Phiras(gdl::Model& model) : ARessource(model, PHIRAS) {};
  ~Phiras() {};
};

#endif /* !_PHIRAS_ */
