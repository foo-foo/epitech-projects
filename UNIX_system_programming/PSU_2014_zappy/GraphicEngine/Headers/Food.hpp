//
// Food.hpp for Food in /home/rosain_f/rendu/PSU_2014_zappy/GraphicEngine/Srcs
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Wed Jul  1 15:45:28 2015 Francois Rosain
// Last update Wed Jul  1 16:11:34 2015 Francois Rosain
//

#ifndef _FOOD_
# define _FOOD_

/* LibGDL */
# include "Texture.hh"
# include "Geometry.hh"

/* Food */
# include "ARessource.hpp"


class	Food : public ARessource
{  
public:
  Food(gdl::Model& model) : ARessource(model, FOODR) {};
  ~Food() {};
};

#endif /* !_FOOD_ */
