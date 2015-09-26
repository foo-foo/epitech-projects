//
// Nibbler.cpp for nibbler in /home/menich_a/bkp_nib4
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Sun Apr  5 10:03:39 2015 Anatole Menichetti
// Last update Sun Apr  5 21:44:25 2015 Anatole Menichetti
//

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <utility>
#include "../includes/Nibbler.hh"
#include "../includes/AGui.hh"

Nibbler::Nibbler(size_t width, size_t height): 
  _map(width * height, ' '), _width(width), _height(height), _dir(0), m_score(0), m_state(ENABLE), m_speed(SPEED), m_moves(0), m_nbrFruits(1), m_step(100), m_mutex(false), m_crazy(false), m_boost(false)
{
  int	i = 0;
 
  while(i < 4)
    {
      _snake.push_back(std::make_pair((height/2 + i), (width/2)));
      _map[((height/2 + i) * width) + (width/2)] = '1';
      ++i;
    }
  put_fruit('2');
  m_score -= 10;
  _dir_to_go[0] = &Nibbler::go_up;
  _dir_to_go[1] = &Nibbler::go_right;
  _dir_to_go[2] = &Nibbler::go_down;
  _dir_to_go[3] = &Nibbler::go_left;
}

Nibbler::~Nibbler()
{}

bool	Nibbler::check_coo(int w, int h)
{
  if (w >= 0 && w < static_cast<int>(_width) &&
      h >= 0 && h < static_cast<int>(_height) &&
      _map[h * _width + w] != '0' && _map[h * _width + w] != '1')
    return (true);
  disable();
  return (false);
}

void	Nibbler::move(int x, int y)
{
  if (check_coo(x, y))
    {
      std::pair <int, int> head = _snake.front();
      std::pair <int, int> tail = _snake.back();

      if (_map[y * _width + x] == ' ')
	{
	  _map[tail.first * _width + tail.second] = ' ';
	  _snake.pop_back();
	}
      if (_map[y * _width + x] == '2' || _map[y * _width + x] == '3' || _map[y * _width + x] == '4')
	put_fruit(_map[y * _width + x]);
      _map[head.first * _width + head.second] = '1';
      _map[y *_width + x] = '0';
      _snake.push_front(std::make_pair(y, x));
    }
}

void	Nibbler::go_up()
{
  move(_snake.front().second, _snake.front().first - 1);
}

void	Nibbler::go_down()
{
  move(_snake.front().second, _snake.front().first + 1);
}

void	Nibbler::go_left()
{
  move(_snake.front().second - 1, _snake.front().first);
}

void	Nibbler::go_right()
{
  move(_snake.front().second + 1, _snake.front().first);
}

void	Nibbler::go()
{
  (this->*_dir_to_go[_dir])();
}

void	Nibbler::put_fruit(char fruit)
{
  int		pos;
  size_t	oldScore = m_score;

  if (m_moves >= 3)
    m_score += 1;
  else
    m_score += 10;
  if (fruit == '3')
    m_speed += 5000;
  else if (fruit == '4')
    m_crazy = true;
  else
    m_crazy = false;
  std::cout << "\a";
  while (m_mutex == true);
  m_moves = 0;
  m_speed -= 500;
  if (oldScore < m_step && m_score >= m_step)
    {
      m_nbrFruits += 1;
      m_step = m_step * 2;
    }
  oldScore = 0;
  while (oldScore++ < m_nbrFruits)
    {
      if (_map.find(' ') == std::string::npos)
	return ;
      srand (time(NULL) + std::clock());
      fruit = rand() % 5;
      if (fruit < 2)
	fruit = 2;
      fruit += 48;
      pos = rand() % (_width * _height);
      while (_map[pos] != ' ')
	pos = rand() % (_width * _height);
      _map[pos] = fruit;
    }
}

void	Nibbler::turn_left()
{
  m_mutex = true;
  m_moves += 1;
  m_mutex = false;
  if (m_crazy)
    {
      _dir += 1;
      if (_dir > 3)
	_dir = 0;
    }
  else
    {
      _dir -= 1;
      if (_dir < 0)
	_dir = 3;
    }
}

void	Nibbler::turn_right()
{
  m_mutex = true;
  m_moves += 1;
  m_mutex = false;
  if (m_crazy)
    {
      _dir -= 1;
      if (_dir < 0)
	_dir = 3;
    }
  else
    {
      _dir += 1;
      if (_dir > 3)
	_dir = 0;
    }
}

size_t		Nibbler::getWidth() const
{
  return (_width);
}

size_t		Nibbler::getHeight() const
{
  return (_height);
}

size_t		Nibbler::getScore() const
{
  return (m_score);
}

bool		Nibbler::isActive() const
{
  return (m_state);
}

void		Nibbler::disable()
{
  m_state = DISABLE;
}

size_t		Nibbler::getSpeed() const
{
  return (m_speed);
}

void		Nibbler::boost()
{
  m_mutex = true;
  if (m_boost)
    {
      m_speed = m_speed * 3;
      m_boost = false;
    }
  else
    {
      m_speed = m_speed / 3;
      m_boost = true;
    }
  m_mutex = false;
}

void		Nibbler::speed(size_t speed)
{
  if (m_speed > MAX_SPEED && m_speed > speed)
    m_speed -= speed;
}

void		Nibbler::retry()
{
  int	i = 0;

  _dir = 0;
  m_score = 0;
  m_speed = SPEED;
  m_moves = 0;
  m_nbrFruits = 1;
  m_step = 100;
  m_crazy = false;
  m_boost = false;
  _map.replace(_map.begin(), _map.end(), _map.size(), ' ');
  _snake.erase(_snake.begin(), _snake.end());
  while(i < 4)
    {
      _snake.push_back(std::make_pair((_height/2 + i), (_width/2)));
      _map[((_height/2 + i) * _width) + (_width/2)] = '1';
      ++i;
    }
  put_fruit('2');
  m_score -= 10;
  m_state = ENABLE;
}

std::string const	&Nibbler::getMap() const
{
  return (_map);
}
