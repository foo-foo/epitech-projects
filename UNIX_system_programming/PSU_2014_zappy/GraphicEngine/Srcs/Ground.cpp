//
// Ground.cpp for Ground in /home/rosain_f/projects/zappy/graphic
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Mon Jun 29 10:25:37 2015 Francois Rosain
// Last update Sat Jul  4 19:56:27 2015 Francois Rosain
//

#include "Ground.hpp"

Ground::Ground(gdl::Texture* texture)
  : AObject(GROUND), _texture(texture)
{}

/* --------- */
/* Get / Set */
/* --------- */

std::vector<AObject*>&	Ground::getRessources()
{
  return (_ressources);
}

/* --------- */
/* Functions */
/* --------- */

bool	Ground::initialize()
{

  _geometry.setColor(glm::vec4(1, 1, 1, 1));
  _geometry.pushVertex(glm::vec3(0, 1, 0));
  _geometry.pushVertex(glm::vec3(1, 1, 0));
  _geometry.pushVertex(glm::vec3(1, 1, 1));
  _geometry.pushVertex(glm::vec3(0, 1, 1));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.build();
  return (true);
}

void	Ground::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void) clock;
  _texture->bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

#include <iostream>
void	Ground::addRessource(e_object type, gdl::Model* model)
{
  float		x = this->_position.x;
  float		y = this->_position.y;
  float		z = this->_position.z;
  AObject*	res;

  switch (type)
    {
    case LINEMATE:
      _ressources.push_back(new Linemate(*model));
      res = _ressources.back();
      res->translate(glm::vec3(x + static_cast<ARessource*>(res)->getPaddingX(), y + 1,
			       z + static_cast<ARessource*>(res)->getPaddingY()));
      res->scale(glm::vec3(0.1f, 0.1f, 0.1f));
      res->rotate(glm::vec3(0,1,0), 180);
      break ;
    case DERAUMERE:
      _ressources.push_back(new Deraumere(*model));
      res = _ressources.back();
      res->translate(glm::vec3(x + static_cast<ARessource*>(res)->getPaddingX(), y + 1,
			       z + static_cast<ARessource*>(res)->getPaddingY()));
      res->scale(glm::vec3(0.02f, 0.02f, 0.02f));
      res->rotate(glm::vec3(0,1,0), 180);
      break ;
    case SIBUR:
      _ressources.push_back(new Sibur(*model));
      res = _ressources.back();
      res->translate(glm::vec3(x + static_cast<ARessource*>(res)->getPaddingX(), y + 1,
			       z + static_cast<ARessource*>(res)->getPaddingY()));
      res->scale(glm::vec3(0.1f, 0.1f, 0.1f));
      res->rotate(glm::vec3(0,1,0), 180);
      res->translate(glm::vec3(0,0.25f,0));
      break ;
    case MENDIANE:
      _ressources.push_back(new Mendiane(*model));
      res = _ressources.back();
      res->translate(glm::vec3(x + static_cast<ARessource*>(res)->getPaddingX(), y + 1,
			       z + static_cast<ARessource*>(res)->getPaddingY()));
      res->scale(glm::vec3(0.1f, 0.1f, 0.1f));
      break ;
    case PHIRAS:
      _ressources.push_back(new Phiras(*model));
      res = _ressources.back();
      res->translate(glm::vec3(x + static_cast<ARessource*>(res)->getPaddingX(), y + 1,
			       z + static_cast<ARessource*>(res)->getPaddingY()));
      res->scale(glm::vec3(0.02f, 0.02f, 0.02f));
      break ;
    case THYSTANE:
      _ressources.push_back(new Thystane(*model));
      res = _ressources.back();
      res->translate(glm::vec3(x + static_cast<ARessource*>(res)->getPaddingX(), y + 1,
			       z + static_cast<ARessource*>(res)->getPaddingY()));
      res->scale(glm::vec3(0.1f, 0.1f, 0.1f));
      break ;
    case FOODR:
      _ressources.push_back(new Food(*model));
      res = _ressources.back();
      res->translate(glm::vec3(x + static_cast<ARessource*>(res)->getPaddingX(), y + 1,
			       z + static_cast<ARessource*>(res)->getPaddingY()));
      res->scale(glm::vec3(0.1f, 0.1f, 0.1f));
      res->rotate(glm::vec3(1,0,0), 180);
      res->translate(glm::vec3(0,0.25f,0));
      break ;
    default:
      break ;
    };
}

void	Ground::removeRessource()
{
  // _ressources.pop();
}
