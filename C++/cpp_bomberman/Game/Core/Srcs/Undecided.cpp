//
// Undecided.cpp for  in /home/menich_a/rendu/cpp_bomberman/work_in_progress/v6
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Wed May 27 16:26:29 2015 Anatole Menichetti
// Last update Sat Jun 13 10:41:00 2015 Anatole Menichetti
//

#include "Undecided.hpp"

Undecided::Undecided(Character* const character, size_t const id) :
Bot(character, id), _lastPos(4242)
{}

void	Undecided::updateLastPos(char const action, size_t const x, size_t const y)
{
  if (action == LEFT)
    _lastPos = x - 1;
  if (action == RIGHT)
    _lastPos = x + 1;
  if (action == DOWN)
    _lastPos = y + 1;
  if (action == UP)
    _lastPos = y - 1;
  if (action == STAGN)
    _lastPos = 4242;
}

char	Undecided::getRandomWay(std::vector<std::vector <AObject*> > const &map, size_t const x, size_t const y) const
{
  char	action = rand() % 4;

  if ((action == LEFT && (!x ||
			  cannotAccessThisCase(map, x - 1, y, false) ||
			  isCurrentCaseDangerous(map, x - 1, y))) ||
      (action == RIGHT && (x >= map[0].size() - 1 ||
			   cannotAccessThisCase(map, x + 1, y, false) ||
			   isCurrentCaseDangerous(map, x + 1, y))) ||
      (action == DOWN && (y >= map.size() - 1 ||
			  cannotAccessThisCase(map, x, y + 1, false) ||
			  isCurrentCaseDangerous(map, x, y + 1))) ||
      (action == UP && (!y ||
			cannotAccessThisCase(map, x, y - 1, false) ||
			isCurrentCaseDangerous(map, x, y - 1))))
    return (-1);
  return (action);

}

void	Undecided::getBestWay(std::vector<std::vector <AObject*> > const &map, size_t const x, size_t const y, int choice[2])
{
  char	action;
  int	cpt = 0;

  if (_lastPos == 4242 || ((_lastMove == LEFT || _lastMove == RIGHT) && x == _lastPos) || ((_lastMove == DOWN || _lastMove == UP) && y == _lastPos))
    {
      while ((action = getRandomWay(map, x, y)) == -1)
	if (++cpt > 25)
	  {
	    action = STAGN;
	    break;
	  }
      updateLastPos(action, x, y);
    }
  else
    action = _lastMove;
  choice[DIRECTION] = action;
  choice[PRIORITY] = 0;
}

char	Undecided::getNextAction(Field &field)
{
  std::vector<std::vector <AObject*> >	&map = field.getMap();
  size_t const	x = _character->getX();
  size_t const	y = _character->getY();
  bool		danger;
  int		choice[2];

  pickUpBonusIfPossible(field, map, x, y);
  danger = isCurrentCaseDangerous(map, x, y);
  if (danger == true)
    {
      choice[DIRECTION] = getEscapeWay(map, x, y, false);
      updateLastPos(choice[DIRECTION], x, y);
    }
  else
    {
      if (_lastMove == STAGN && _stagnTime > 0)
	{
	  if (_bombs == _maxBombs)
	    _stagnTime -= 1;
	  return (STAGN);
	}
      getBestWay(map, x, y, choice);

      int	hit = getNbrHit(map, x, y);
      if (_bombs > 0 && hit && -hit < choice[PRIORITY] && getEscapeWay(map, x, y, true) != -1)
	choice[DIRECTION] = PUT_BOMB;

    }
  _lastMove = choice[DIRECTION];
  return (choice[DIRECTION]);
}
