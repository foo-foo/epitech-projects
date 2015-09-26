//
// Ground.hpp for Ground in /home/rosain_f/projects/zappy/graphic
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Mon Jun 29 10:24:49 2015 Francois Rosain
// Last update Wed Jul  1 15:43:02 2015 Francois Rosain
//

#ifndef _GROUND_
# define _GROUND_

# include <vector>

/* LibGDL */
# include "Texture.hh"
# include "Geometry.hh"

/* Ground */
# include "AObject.hpp"
# include "ARessource.hpp"

/* Ressources */
# include "Linemate.hpp"
# include "Deraumere.hpp"
# include "Sibur.hpp"
# include "Mendiane.hpp"
# include "Phiras.hpp"
# include "Thystane.hpp"
# include "Food.hpp"

class	Ground : public AObject
{
private:
  gdl::Texture*	_texture;
  gdl::Geometry	_geometry;
  std::vector<AObject*>	_ressources;

public:
  Ground(gdl::Texture*);
  virtual ~Ground() {};

  virtual bool	initialize();
  virtual void	draw(gdl::AShader&, gdl::Clock const &);

  std::vector<AObject*>&	getRessources();

  void	addRessource(e_object, gdl::Model*);
  void	removeRessource();
};

#endif /* !_GROUND_ */
