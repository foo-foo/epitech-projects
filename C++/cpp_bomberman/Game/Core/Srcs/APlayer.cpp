//
// APlayer.cpp for  in /home/menich_a/Downloads/v6
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Wed May 27 11:38:58 2015 Anatole Menichetti
// Last update Sat Jun 13 13:02:39 2015 Anatole Menichetti
//

#include "APlayer.hpp"

APlayer::APlayer(Character* const character, size_t const id) :
  _character(character), _speed(DEFAULT_SPEED),
  _bombs(DEFAULT_BOMBS), _power(DEFAULT_POWER), _id(id)
{
  _launchMove[0] = &Character::moveUp;
  _launchMove[1] = &Character::moveDown;
  _launchMove[2] = &Character::moveLeft;
  _launchMove[3] = &Character::moveRight;
}

/* --------- */
/* Set / Get */
/* --------- */

float	APlayer::getSpeed() const
{
  return (_speed);
}

void	APlayer::addSpeed()
{
  if (_speed + 1 < MAX_SPEED)
    _speed++;
}

int	APlayer::getPower() const
{
  return (_power);
}

void	APlayer::addPower()
{
  if (_power + 1 < MAX_POWER)
    _power++;
}

int	APlayer::getBomb() const
{
  return (_bombs);
}

void	APlayer::addBomb()
{
  if (_bombs + 1 < MAX_BOMBS)
    _bombs++;
}

size_t	APlayer::getId() const
{
  return (_id);
}

bool	APlayer::isHuman() const
{
  return (false);
}
