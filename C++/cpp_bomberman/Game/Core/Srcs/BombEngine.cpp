//
// BombEngine.cpp for  in /home/menich_a/rendu/cpp_bomberman/Game/Game/Srcs
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Thu Jun 11 18:49:01 2015 Anatole Menichetti
// Last update Sat Jun 13 09:48:32 2015 Anatole Menichetti
//

#include "BombEngine.hpp"

BombEngine::BombEngine(Field &map)
  : _map(map), _flagExit(0)
{
  _decode = new Decode;
  _bonus[0] =  &BombEngine::_createBonusSpeed;
  _bonus[1] =  &BombEngine::_createBonusPower;
  _bonus[2] =  &BombEngine::_createBonusBomb;
  _thread.start(this, 0);
}

BombEngine::~BombEngine()
{}

/* ---------------- */
/* Bonus Generation */
/* ---------------- */

AObject*	BombEngine::_getRandomBonus(int const y, int const x) const
{
  if ((rand() % 100) <= LUCK_BONUS)
    return (_bonus[rand() % NB_BONUS](y, x, getMap()));
  return (NULL);
}

AObject*	BombEngine::_createBonusSpeed(int const y, int const x, Field &map)
{
  return (new BonusSpeed(y, x, *map.getModels()["Star"]));
}

AObject*	BombEngine::_createBonusPower(int const y, int const x, Field &map)
{
  return (new BonusPower(y, x, *map.getModels()["Mushroom"]));
}

AObject*	BombEngine::_createBonusBomb(int const y, int const x, Field &map)
{
  return (new BonusBomb(y, x, *map.getModels()["Bomb"]));
}

/* ------- */
/* Private */
/* ------- */

void	BombEngine::_putFlame(int const y, int const x, int &tmp, int const power)
{
  _boxFlag = 0;
  if (tmp < power
      && y < static_cast<int>(_map.getMap().size()) && y >= 0
      && x < static_cast<int>(_map.getMap()[y].size()) && x >= 0
      && (_map.getMap()[y][x] == NULL
	  || _map.getMap()[y][x]->getType() != WALL))
    {
      if (_map.getMap()[y][x] != NULL)
	_decode->reaction(_map.getMap()[y][x]->getType(), this, y, x, tmp, power);
      _map.getMap()[y][x] = new Flame(y, x, *_map.getModels()["Flower"], _boxFlag);
      _map.getMap()[y][x]->scale(glm::vec3(10,10,10));
      _map.getMap()[y][x]->initialize();
      tmp++;
    }
  else
    tmp = power;
}

void	BombEngine::_diffusionFlame(int const y, int const x, int const power)
{
  int	i = 0, flame_yp = 0,
    flame_yn = 0, flame_xp = 0,
    flame_xn = 0;

  while (i < power)
    {
      _putFlame(y - flame_yn, x, flame_yn, power);
      _putFlame(y + flame_yp, x, flame_yp, power);
      _putFlame(y, x + flame_xp, flame_xp, power);
      _putFlame(y, x - flame_xn, flame_xn, power);
      i++;
    }
}

/* ------ */
/* Public */
/* ------ */

Field&	BombEngine::getMap() const
{
  return (_map);
}

void	BombEngine::nothingReac(int const, int const, int &, int)
{}

void	BombEngine::nothing(int const, int const)
{}

void    BombEngine::flameReacFlame(int const y, int const x, int &, int)
{
  delete _map.getMap()[y][x];
  _map.getMap()[y][x] = NULL;
}

void    BombEngine::flameReacBox(int const y, int const x, int &tmp, int power)
{
  _boxFlag = 1;
  delete _map.getMap()[y][x];
  _map.getMap()[y][x] = NULL;
  tmp = power;
}

void    BombEngine::flameReacBomb(int const y, int const x, int &tmp, int power)
{
  Bomb*	bomb = reinterpret_cast<Bomb*>(_map.getMap()[y][x]);

  bomb->getPlayer().addBomb();
  power = bomb->getPlayer().getPower();
  delete _map.getMap()[y][x];
  _map.getMap()[y][x] = NULL;
  _diffusionFlame(y, x, power);
  tmp = power;
}

void    BombEngine::flameReacBonus(int const y, int const x, int &tmp, int power)
{
  delete _map.getMap()[y][x];
  _map.getMap()[y][x] = NULL;
  tmp = power;
}

void	BombEngine::exitThread()
{
  _flagExit = 1;
}

void	BombEngine::flameDiffusBomb(int const y, int const x)
{
  Bomb*	bomb = reinterpret_cast<Bomb*>(_map.getMap()[y][x]);
  int	power;

  if (bomb->explose())
    {
      power = bomb->getPlayer().getPower();
      delete _map.getMap()[y][x];
      _map.getMap()[y][x] = new Flame(y, x, *_map.getModels()["Bomb"], 0);
      _diffusionFlame(y, x, power);
    }
}

void	BombEngine::flameDiffusFlame(int const y, int const x)
{
  Flame *flame;
  AObject *bonus = NULL;

  flame = reinterpret_cast<Flame*>(_map.getMap()[y][x]);
  if (flame->isEnd())
    {
      if (flame->isBonus())
	bonus = _getRandomBonus(y, x);
      else
	bonus = NULL;
      delete _map.getMap()[y][x];
      _map.getMap()[y][x] = bonus;
      if (_map.getMap()[y][x] != NULL)
	_map.getMap()[y][x]->initialize();
    }
}

void	BombEngine::operator()(char const)
{
  srand(time(NULL));
  while (!_flagExit)
    for (size_t y = 0; y < _map.getMap().size(); y++)
      for (size_t x = 0; x < _map.getMap()[y].size(); x++)
	{
	  if (_map.getMap()[y][x] != NULL)
	    _decode->diffusion(_map.getMap()[y][x]->getType(), this, y, x);
	}
}
