//
// Human.cpp for  in /home/menich_a/Downloads/v6
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Wed May 27 11:09:57 2015 Anatole Menichetti
// Last update Sun Jun 14 15:31:17 2015 Anatole Menichetti
//

#include "Human.hpp"

Human::Human(Character* const character, gdl::Input &input, size_t const id,
	     sf::Sound &pickBonusSound, sf::Sound &putBombSound)
  : APlayer(character, id), _inputKeys(5, 0), _input(input),
    _pickBonusSound(pickBonusSound), _putBombSound(putBombSound)
{
  if (id % 2)
    setInputKeys(SDLK_KP_8, SDLK_KP_5, SDLK_KP_4, SDLK_KP_6, SDLK_KP_0);
  else
    setInputKeys(SDLK_z, SDLK_s, SDLK_q, SDLK_d, SDLK_SPACE);
}

void	Human::setInputKeys(int const up, int const down, int const left, int const right, int const bomb)
{
  _inputKeys[0] = up;
  _inputKeys[1] = down;
  _inputKeys[2] = left;
  _inputKeys[3] = right;
  _inputKeys[4] = bomb;
}

std::vector<int>&	Human::getInputKeys()
{
  return (_inputKeys);
}

/* --------- */
/* Functions */
/* --------- */

/*
**	Check if next case is accessible and pick up bonus if needed.
*/
bool	Human::_checkInput(float const y, float const x, Field& field)
{
  std::vector<std::vector<AObject*> > &map = field.getMap();
  int const	cX = _character->getX();
  int const	cY = _character->getY();

  // Pick up bonus if needed.
  if (y < field.getHeight() && y >= 0
      && x < field.getWidth() && x >= 0
      && map[y][x] && map[y][x]->getType() == BONUS)
    {
      _pickBonusSound.Play();
      _character->pickBonus();
      reinterpret_cast<ABonus*>(map[y][x])->activate(this);
      delete map[y][x];
      map[y][x] = NULL;
    }

  // Returns true if player can access target case.
  return (y < field.getHeight() && y >= 0
  	  && x < field.getWidth() && x >= 0
  	  && (!map[y][x] || map[y][x]->getType() == FLAME ||
	      (map[cY][cX] && map[y][x]->getType() == BOMB &&
	       map[cY][cX]->getType() == BOMB && static_cast<int>(y) == cY && static_cast<int>(x) == cX)));
}

bool	Human::tryMove(Field &field, int const move, float const y, float const x, float const add)
{
  if (!_input.getKey(_inputKeys[move]) || !_checkInput(y, x, field))
    return (false);
  (_character->*_launchMove[move])(add);
  return (true);
}

void	Human::update(gdl::Clock const &clock, Field& field)
{
  float add;
  short	cpt = 0;
  float const	x = _character->getX();
  float	const y = _character->getY();
  std::vector<std::vector<AObject*> > &map = field.getMap();

  add = 0.1f * static_cast<float>(clock.getElapsed()) * SPEED(_speed);

  cpt += tryMove(field, DOWN, y + add, x, add);
  cpt += tryMove(field, UP, y - add, x, add);
  cpt += tryMove(field, LEFT, y, x - add, add);
  cpt += tryMove(field, RIGHT, y, x + add, add);
  if (!cpt)
    _character->pauseModel();
  if (_input.getKey(_inputKeys[PUT_BOMB]) &&
      !map[y][x] && _bombs > 0)
    {
      _putBombSound.Play();
      _character->putBomb();
      map[y][x] = new Bomb(y, x, this, *field.getModels()["Bomb"]);
      map[y][x]->initialize();
      _bombs--;
    }
}

bool	Human::isHuman() const
{
  return (true);
}
