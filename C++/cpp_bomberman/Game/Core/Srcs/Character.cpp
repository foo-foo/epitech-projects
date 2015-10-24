//
// Character.cpp for Character in /home/rosain_f/rendu/cpp_bomberman/work_in_progress/v4
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Fri May 15 11:45:17 2015 Francois Rosain
// Last update Tue Sep 15 08:52:12 2015 Anatole Menichetti
//

#include "Character.hpp"

Character::Character(size_t id)
  : AObject(CHARACTER), _id(id)
{
  std::pair<std::string, float>	modelsInfos[4];

  modelsInfos[0].first = "./Assets/mario/mario.fbx";
  modelsInfos[0].second = .75;
  modelsInfos[1].first = "./Assets/peach/peach.fbx";
  modelsInfos[1].second = .0075;
  modelsInfos[2].first = "./Assets/darunia/darunia.fbx";
  modelsInfos[2].second = .0075;
  modelsInfos[3].first = "./Assets/sacboy/sacboy.fbx";
  modelsInfos[3].second = .2;
  if (id < 1 || id > 3)
    id = 4;
  _modelFile = modelsInfos[id - 1].first;
  _modelScale = modelsInfos[id - 1].second;
}

Character::Character()
  : AObject(CHARACTER), _modelFile("./Assets/sacboy/sacboy.fbx"), _modelScale(.2), _id(0)
{}

Character::~Character()
{}

/* --------- */
/* Functions */
/* --------- */

bool    Character::initialize(int const y, int const x)
{
  if (!_model.load(_modelFile))
    {
      std::cout << "Error : can\'t load model." << std::endl;
      return (false);
    }
  if (!_model.createSubAnim(0, "pickbonus", 20, 50) ||
      !_model.createSubAnim(0, "stop", 75, 190) ||
      !_model.createSubAnim(0, "run", 200, 224) ||
      !_model.createSubAnim(0, "danse", 250, 546) ||
      !_model.createSubAnim(0, "putbomb", 230, 250))
    std::cout << "Error : can\'t create sub animes." << std::endl;
  if (!_model.setCurrentSubAnim("stop"))
    std::cout << "Error : can\'t start animation on model." << std::endl;
   _x = x;
   _y = y;
   _mooving = false;
   this->scale(glm::vec3(_modelScale, _modelScale, _modelScale));
   translate(glm::vec3(_x,0,_y));
   return (true);
}

void	Character::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _model.draw(shader, getTransformation(), clock.getElapsed());
}

/* ------- */
/* Get/Set */
/* ------- */

float	Character::getX() const
{
  return (_x);
}

float	Character::getY() const
{
  return (_y);
}

/* --------- */
/* Movements */
/* --------- */

void	Character::_animationHandler()
{
 if (!_mooving)
    {
      if (!_model.setCurrentSubAnim("run"))
	std::cout << "Error : can\'t start animation on model." << std::endl;
      _mooving = true;
      _model.pause(false);
    }
}

void	Character::moveDown(float const add)
{
  _animationHandler();
  _rotation = glm::vec3(0,0,0);
  translate(glm::vec3(0,0,add));
  _y += add;
}

void	Character::moveUp(float const add)
{
  _animationHandler();
  _rotation = glm::vec3(0,180,0);
  translate(glm::vec3(0,0,-add));
  _y -= add;
}

void	Character::moveLeft(float const add)
{
  _animationHandler();
  _rotation = glm::vec3(0,-90,0);
  translate(glm::vec3(-add,0,0));
  _x -= add;
}

void	Character::moveRight(float const add)
{
  _animationHandler();
  _rotation = glm::vec3(0,90,0);
  translate(glm::vec3(add,0,0));
  _x += add;
}

void	Character::pauseModel()
{
 if (_mooving && !_model.setCurrentSubAnim("stop"))
   std::cout << "Error : can\'t start animation on model." << std::endl;
 _mooving = false;
}

void	Character::putBomb()
{
 if (!_model.setCurrentSubAnim("putbomb"))
   std::cout << "Error : can\'t start animation on model." << std::endl;
}

bool	Character::isDancing()
{
  return (_isDancing);
}

void	Character::danse()
{
 if (!_model.setCurrentSubAnim("danse"))
   std::cout << "Error : can\'t start animation on model." << std::endl;
 else
   _isDancing = true;
}

void	Character::pickBonus()
{
 if (!_model.setCurrentSubAnim("pickbonus"))
   std::cout << "Error : can\'t start animation on model." << std::endl;
}

bool	Character::isMonster() const
{
  return (_id == 3);
}

void    Character::teleport(std::vector<std::vector <AObject*> > const &map)
{
  size_t const	x = map[0].size() / 2;
  size_t const	y = map.size() / 2;
  float const	add = 0.280;

  while (_x > x)
    moveLeft(add);
  while (_x < x)
    moveRight(add);
  while (_y > y)
    moveUp(add);
  while (_y < y)
    moveDown(add);
}
