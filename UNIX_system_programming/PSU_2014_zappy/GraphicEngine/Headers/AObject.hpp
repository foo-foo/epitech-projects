//
// AObject.hpp for AObject in /home/rosain_f/projects/zappy/graphic
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Mon Jun 29 10:14:23 2015 Francois Rosain
// Last update Fri Jul  3 17:14:38 2015 Francois Rosain
//

#ifndef _A_OBJECT_
# define _A_OBJECT_

# include "glm/glm.hpp"
# include "glm/gtc/matrix_transform.hpp"

# include "Clock.hh"
# include "Input.hh"
# include "AShader.hh"

enum	e_object
  {
    GROUND,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTANE,
    FOODR,
    CHARACTER,
    EGG
  };

class	AObject
{
public:
  AObject(e_object);
  virtual ~AObject() {};

  virtual bool	initialize();
  // virtual void	update(gdl::Clock const &, gdl::Input &);
  virtual void	draw(gdl::AShader &, gdl::Clock const &) = 0;
  virtual void	translate(glm::vec3 const &);
  virtual void	rotate(glm::vec3 const &, float);
  virtual void	scale(glm::vec3 const &);
  virtual glm::mat4 getTransformation();
  e_object      getType() const;

protected:
  glm::vec3	_position;
  glm::vec3	_rotation;
  glm::vec3	_scale;
  e_object	_type;
};

#endif /* !_A_OBJECT_ */
