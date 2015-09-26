//
// Block.cpp for  in /home/menich_a/rendu/cpp_bomberman/Game/Game/Srcs
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Thu Jun 11 20:32:44 2015 Anatole Menichetti
// Last update Sat Jun 13 09:22:30 2015 Anatole Menichetti
//

#include "Block.hpp"

Block::Block(gdl::Texture* texture, e_object type)
  : AObject(type), _texture(texture)
{}

/* --------- */
/* Functions */
/* --------- */

void	Block::_initGeometry()
{
  _geometry.setColor(glm::vec4(1, 1, 1, 1));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
}

bool	Block::initialize()
{
  _initGeometry();
  _geometry.pushVertex(glm::vec3(0, 0, 0));
  _geometry.pushVertex(glm::vec3(1, 0, 0));
  _geometry.pushVertex(glm::vec3(1, 1, 0));
  _geometry.pushVertex(glm::vec3(0, 1, 0));

  _initGeometry();
  _geometry.pushVertex(glm::vec3(0, 0, 1));
  _geometry.pushVertex(glm::vec3(1, 0, 1));
  _geometry.pushVertex(glm::vec3(1, 1, 1));
  _geometry.pushVertex(glm::vec3(0, 1, 1));

  _initGeometry();
  _geometry.pushVertex(glm::vec3(0, 0, 0));
  _geometry.pushVertex(glm::vec3(0, 0, 1));
  _geometry.pushVertex(glm::vec3(0, 1, 1));
  _geometry.pushVertex(glm::vec3(0, 1, 0));

  _initGeometry();
  _geometry.pushVertex(glm::vec3(1, 0, 0));
  _geometry.pushVertex(glm::vec3(1, 0, 1));
  _geometry.pushVertex(glm::vec3(1, 1, 1));
  _geometry.pushVertex(glm::vec3(1, 1, 0));

  _initGeometry();
  _geometry.pushVertex(glm::vec3(0, 1, 0));
  _geometry.pushVertex(glm::vec3(1, 1, 0));
  _geometry.pushVertex(glm::vec3(1, 1, 1));
  _geometry.pushVertex(glm::vec3(0, 1, 1));

  _initGeometry();
  _geometry.pushVertex(glm::vec3(0, 0, 0));
  _geometry.pushVertex(glm::vec3(1, 0, 0));
  _geometry.pushVertex(glm::vec3(1, 0, 1));
  _geometry.pushVertex(glm::vec3(0, 0, 1));

  _geometry.build();
  return (true);
}

void	Block::draw(gdl::AShader &shader, gdl::Clock const &)
{
  _texture->bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}
