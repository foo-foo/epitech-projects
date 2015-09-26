//
// Monster.cpp for  in /home/menich_a/rendu/cpp_bomberman/work_in_progress/v6
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Wed May 27 16:26:29 2015 Anatole Menichetti
// Last update Sat Jun 13 10:37:17 2015 Anatole Menichetti
//

#include "Monster.hpp"

Monster::Monster(Character* const character, size_t const id) :
  Bot(character, id), _lastPos(4242)
{}

void	Monster::updateLastPos(char const action, size_t const x, size_t const y)
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

char	Monster::getRandomWay(std::vector<std::vector <AObject*> > const &map, size_t const x, size_t const y) const
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

void	Monster::getBestWay(std::vector<std::vector <AObject*> > const &map, size_t const x0, size_t const y0, int choice[2])
{
  char	action;
  int	cpt = 0;
  size_t	x = x0;
  size_t	y = y0;

  if (_lastMove == LEFT)
    x--;
  if (_lastMove == RIGHT)
    x++;
  if (_lastMove == UP)
    y--;
  if (_lastMove == DOWN)
    y++;

  if (_lastPos == 4242 || cannotAccessThisCase(map, x, y, false) ||
      isCurrentCaseDangerous(map, x, y))
    {
      while ((action = getRandomWay(map, x0, y0)) == -1)
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

char	Monster::getNextAction(Field &field)
{
  std::vector<std::vector <AObject*> >	&map = field.getMap();
  size_t const	x = _character->getX();
  size_t const	y = _character->getY();
  int		choice[2];
      
  getBestWay(map, x, y, choice);
  _lastMove = choice[DIRECTION];
  return (choice[DIRECTION]);
}
