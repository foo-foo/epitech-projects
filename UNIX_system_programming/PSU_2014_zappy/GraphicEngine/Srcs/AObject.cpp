//
// AObject.cpp for AObject in /home/rosain_f/projects/zappy/graphic
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Mon Jun 29 10:16:50 2015 Francois Rosain
// Last update Mon Jun 29 13:54:09 2015 Francois Rosain
//

#include "AObject.hpp"

AObject::AObject(e_object type)
  : _position(0,0,0), _rotation(0,0,0), _scale(1,1,1), _type(type)
{}

/* --------- */
/* Functions */
/* --------- */

/* Charge l'object */
bool	AObject::initialize()
{
  return (true);
}

/* ---------------------- */
/* Déplacement de l'objet */
/* ---------------------- */

void	AObject::translate(glm::vec3 const &v)
{
  _position += v;
}

void	AObject::rotate(glm::vec3 const &axis, float angle)
{
  _rotation += (axis * angle);
}

void    AObject::scale(glm::vec3 const &scale)
{
  _scale *= scale;
}

/* Placement de l'object */
glm::mat4	AObject::getTransformation()
{
  glm::mat4	transform(1);

  /* Translation */
  transform = glm::translate(transform, _position);
  /* Rotation */
  transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));
  /* Mise a l'échelle */
  transform = glm::scale(transform, _scale);
  return (transform);
}

e_object        AObject::getType() const
{
  return (_type);
}
