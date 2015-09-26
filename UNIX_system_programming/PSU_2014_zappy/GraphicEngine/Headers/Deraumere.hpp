//
// Deraumere.hpp for Linamate in /home/rosain_f/rendu/PSU_2014_zappy/GraphicEngine/Headers
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Wed Jul  1 15:40:07 2015 Francois Rosain
// Last update Wed Jul  1 15:40:22 2015 Francois Rosain
//

#ifndef _DERAUMERE_
# define _DERAUMERE_

/* LibGDL */
# include "Texture.hh"
# include "Geometry.hh"

/* Linemate */
# include "ARessource.hpp"


class	Deraumere : public ARessource
{  
public:
  Deraumere(gdl::Model& model) : ARessource(model, DERAUMERE) {};
  ~Deraumere() {};
};

#endif /* !_DERAUMERE_ */
