//
// Linemate.hpp for Linemate in /home/rosain_f/rendu/PSU_2014_zappy/client_src
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Wed Jul  1 13:18:04 2015 Francois Rosain
// Last update Fri Jul  3 17:15:01 2015 Francois Rosain
//

#ifndef _LINEMATE_
# define _LINEMATE_

/* LibGDL */
# include "Texture.hh"
# include "Geometry.hh"

/* Linemate */
# include "ARessource.hpp"


class	Linemate : public ARessource
{  
public:
  Linemate(gdl::Model& model) : ARessource(model, LINEMATE) {};
  ~Linemate() {};
};

#endif /* !_LINEMATE_ */
