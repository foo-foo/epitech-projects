//
// Ground.cpp for Groudn in /home/rosain_f/rendu/cpp_bomberman/work_in_progress/v5
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Fri May 15 14:05:10 2015 Francois Rosain
// Last update Sat Jun 13 10:33:02 2015 Anatole Menichetti
//

#include "Ground.hpp"

Ground::Ground(gdl::Texture* texture)
  : AObject(GROUND), _texture(texture)
{}

/* --------- */
/* Functions */
/* --------- */

bool	Ground::initialize()
{
  _geometry.setColor(glm::vec4(1,1,1,1));
  _geometry.pushVertex(glm::vec3(0,0,0));
  _geometry.pushVertex(glm::vec3(1,0,0));
  _geometry.pushVertex(glm::vec3(1,0,1));
  _geometry.pushVertex(glm::vec3(0,0,1));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.build();
  return (true);
}

void	Ground::draw(gdl::AShader &shader, gdl::Clock const &)
{
  _texture->bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}
