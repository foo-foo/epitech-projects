
//
// Map.cpp for Map in /home/rosain_f/projects/zappy/graphic
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Mon Jun 29 10:00:35 2015 Francois Rosain
// Last update Sun Jul  5 11:19:23 2015 Francois Rosain
//

#include "Map.hpp"

Map::Map(size_t size_x, size_t size_y)
  : _sizeX(size_x), _sizeY(size_y), _ground(size_x * size_y)
{}

/* --------- */
/* Set / Get */
/* --------- */

size_t					Map::getSizeX() const
{
  return (_sizeX);
}

size_t					Map::getSizeY() const
{
  return (_sizeY);
}

std::vector<AObject*>&			Map::getGround()
{
  return (_ground);
}

std::map<std::string, gdl::Texture*>&	Map::getTextures()
{
  return (_textures);
}

std::map<std::string, gdl::Model*>&	Map::getModels()
{
  return (_models);
}

std::vector<Character*>&		Map::getCharacters()
{
  return (_characters);
}

/* ------- */
/* Private */
/* ------- */

void	Map::_createGround()
{
  size_t	x = 0;
  size_t	y = 0;
  AObject*	newground;

  while (y < _sizeY)
    {
      x = 0;
      while (x < _sizeX)
	{
	  newground = new Ground(_textures["Grass"]);
	  newground->initialize();
	  newground->translate(glm::vec3(x, 0, y));
	  _ground[MAP_TO_VECTOR(x, y, _sizeX)] = newground;
	  x++;
        }
      y++;
    }
}

/* --------- */
/* Functions */
/* --------- */

bool	Map::isSizeOk() const
{
  if (_sizeX * _sizeY <= MAP_MAX_SIZE)
    return (true);
  std::cout << std::endl;
  std::cout << "--- --- --- --- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "--- --- --- --- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Map is too BIG." << std::endl;
  std::cout << "Sorry but this GraphicEngine cannot load so many ressources." << std::endl;
  std::cout << "--- --- --- --- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "--- --- --- --- Asteks are so smart  :) --- --- --- --- ---" << std::endl << std::endl;
  return (false);
}

void	Map::initialize()
{
  if (!addTexture("Grass", "./GraphicEngine/Assets/Textures/grass.tga")
      || !addModel("Star", "./GraphicEngine/Assets/Models/Star/Star.fbx")
      || !addModel("Flower", "./GraphicEngine/Assets/Models/Flower/I_fireflower.obj")
      || !addModel("Bomb", "./GraphicEngine/Assets/Models/Bomb/Bomb.fbx")
      || !addModel("Mario", "./GraphicEngine/Assets/Models/mario/mario.fbx")
      || !addModel("Egg", "./GraphicEngine/Assets/Models/Egg/egg.obj"))
    std::cout << "Can\'t load all Assets." << std::endl;
  _createGround();
}

bool	Map::addTexture(std::string name, std::string path)
{
  gdl::Texture*	texture = new gdl::Texture();

  if (!texture->load(path))
    {
      std::cout << "Error : Can\'t load texture" << path << ">" << std::endl;
      return (false);
    }
  _textures[name] = texture;
  return (true);
}

bool    Map::addModel(std::string name, std::string path)
{
  gdl::Model	*model = new gdl::Model();

  if (!model->load(path))
    {
      std::cout << "Error : Can\'t load model <" << path << ">" << std::endl;
      return (false);
    }
  _models[name] = model;
  return (true);
}

void	Map::addCharacter(Character* character)
{
  _characters.push_back(character);
}

void	Map::addEgg(size_t x, size_t y)
{
  Egg*	egg = new Egg(getModels()["Egg"], x, y, _eggs.size() + 1);
  egg->translate(glm::vec3(x + 0.2f, 1.5f, x + 0.2f));
  egg->scale(glm::vec3(0.18f, 0.18f, 0.18f));
  _eggs.push_back(egg);
}

void	Map::removeEgg(int id)
{
  for (std::vector<Egg*>::iterator it = _eggs.begin(); it != _eggs.end(); it++)
    {
      if ((*it)->getId() == id)
	{
	  _eggs.erase(it);
	  break ;
	}
    }
}

std::vector<Egg*>&	Map::getEggs()
{
  return (_eggs);
}

void	Map::addRessource(int x, int y, e_object type)
{
  Ground*	ground = static_cast<Ground*>(this->getGround()[MAP_TO_VECTOR(x, y, this->getSizeX())]);

  switch (type)
    {
    case LINEMATE:
      ground->addRessource(LINEMATE, getModels()["Star"]);
      break ;
    case DERAUMERE:
      ground->addRessource(DERAUMERE, getModels()["Flower"]);
      break ;
    case SIBUR:
      ground->addRessource(SIBUR, getModels()["Bomb"]);
      break ;
    case MENDIANE:
      ground->addRessource(MENDIANE, getModels()["Star"]);
      break ;
    case PHIRAS:
      ground->addRessource(PHIRAS, getModels()["Flower"]);
      break ;
    case THYSTANE:
      ground->addRessource(THYSTANE, getModels()["Bomb"]);
      break ;
    case FOODR:
      ground->addRessource(FOODR, getModels()["Star"]);
      break ;
    default:
      break ;
    };
}

void		Map::resetGround(size_t x, size_t y)
{
  Ground*	ground = static_cast<Ground*>(this->getGround()[MAP_TO_VECTOR(x, y, this->getSizeX())]);
  ground->getRessources().clear();
}
