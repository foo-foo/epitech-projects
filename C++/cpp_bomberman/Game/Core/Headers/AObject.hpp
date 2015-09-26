//
// AObject.hpp for AObject in /home/rosain_f/projects/BomberMan/cube/v2
//
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
//
// Started on  Tue May  5 09:54:08 2015 Francois Rosain
// Last update Sat Jun 13 09:50:47 2015 Anatole Menichetti
//

#ifndef _AOBJECT_HPP_
# define _AOBJECT_HPP_

/* SDL 2 */
# include "SdlContext.hh"

/* Gestion des matrix */
# include "glm/glm.hpp"
# include "glm/gtc/matrix_transform.hpp"

# include "Clock.hh"
# include "Input.hh"
# include "AShader.hh"

class	APlayer;

/*  Classe Abstraite représentant un objet  */
/*    Position  /  Rotation   /  Echelle    */
enum    e_object
  {
    CHARACTER,
    WALL,
    BOX,
    FLAME,
    GROUND,
    BOMB,
    BONUS
  };

class	AObject
{
public:
  AObject(e_object const);
  virtual ~AObject() {};

  virtual bool	initialize();
  virtual void	update(gdl::Clock const &, gdl::Input &);
  virtual void	draw(gdl::AShader &, gdl::Clock const &) = 0;
  virtual void	translate(glm::vec3 const &);
  virtual void	rotate(glm::vec3 const &, float const);
  virtual void	scale(glm::vec3 const &);
  virtual glm::mat4 const	getTransformation() const;
  e_object			getType() const;
  
protected:
  glm::vec3		_position;
  glm::vec3		_rotation;
  glm::vec3		_scale;
  e_object const	_type;
};

#endif /* !_AOBJECT_HPP_ */
