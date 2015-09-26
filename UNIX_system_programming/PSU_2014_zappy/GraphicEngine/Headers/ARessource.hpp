//
// ARessource.hpp for ARessource in /home/rosain_f/rendu/PSU_2014_zappy/GraphicEngine/Srcs
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Wed Jul  1 13:35:56 2015 Francois Rosain
// Last update Wed Jul  1 15:35:12 2015 Francois Rosain
//

#ifndef _A_RESSOURCE_
# define _A_RESSOURCE_

/* LibGDL */
# include "Model.hh"

/* ARessources */
# include "AObject.hpp"

/* Padding */
# define PADD_X_LINEMATE	0.2
# define PADD_Y_LINEMATE	0.2

# define PADD_X_DERAUMERE	0.5
# define PADD_Y_DERAUMERE	0.2

# define PADD_X_SIBUR		0.2
# define PADD_Y_SIBUR		0.5

# define PADD_X_MENDIANE	0.8
# define PADD_Y_MENDIANE	0.8

# define PADD_X_PHIRAS		0.5
# define PADD_Y_PHIRAS		0.8

# define PADD_X_THYSTANE	0.8
# define PADD_Y_THYSTANE	0.5

# define PADD_X_FOOD		0.5
# define PADD_Y_FOOD		0.5

class	ARessource : public AObject
{
protected:
  gdl::Model&	_model;
  size_t	_x;
  size_t	_y;
  float		_padding_x;
  float		_padding_y;

public:
  ARessource(gdl::Model&, e_object);
  virtual ~ARessource() {};

  float	getPaddingX() const;
  float	getPaddingY() const;

  virtual void	draw(gdl::AShader&, gdl::Clock const &);
};

#endif /* !_A_RESSOURCE */
