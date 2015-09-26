//
// AObject.cpp for AObject in /home/rosain_f/projects/BomberMan/cube/v2
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Tue May  5 10:16:45 2015 Francois Rosain
// Last update Sat Jun 13 09:50:58 2015 Anatole Menichetti
//

#include "AObject.hpp"

AObject::AObject(e_object const type)
  : _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1), _type(type)
{}

/* --------- */
/* Functions */
/* --------- */

/* Charge l'object */
bool	AObject::initialize()
{
  return (true);
}

/* Gestion du comportement de l'objet */
void	AObject::update(gdl::Clock const &, gdl::Input &)
{}

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
glm::mat4 const	AObject::getTransformation() const
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

e_object	AObject::getType() const
{
  return (_type);
}
