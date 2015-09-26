//
// Soldier.cpp for  in /home/menich_a/rendu/cpp_bomberman/work_in_progress/v6
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Wed May 27 16:26:29 2015 Anatole Menichetti
// Last update Sat Jun 13 10:40:27 2015 Anatole Menichetti
//

#include "Soldier.hpp"
#include <algorithm>

Soldier::Soldier(Character* const character, size_t const id) :
  Bot(character, id)
{}

/*
**	Recursive analyse of each way with potential field priorities method.
*/
int	Soldier::getBestWayRec(std::vector<std::vector <AObject*> > const &map, size_t const x, size_t const y, int const dist, std::vector<std::pair<size_t, size_t> > &analysed) const
{
  std::pair<size_t, size_t>	pos(x, y);

  int const	xi = static_cast<int>(x);
  int const	yi = static_cast<int>(y);
  int const	size = analysed.size() + 1;
  int		choice[2];
  int		ret;
  char		type = GROUND;

  // analyse current case.
  if (map[yi][xi])
    type = map[yi][xi]->getType();
  if (dist > PREVISION_MAX || cannotAccessThisCase(map, x, y, false) ||
      std::find(analysed.begin(), analysed.end(), pos) != analysed.end())
    return (FORBIDDEN_CASE);
  analysed.push_back(pos);
  if (isCurrentCaseDangerous(map, x, y))
    return (DANGEROUS_CASE);

  choice[PRIORITY] = DEFAULT_CHOICE;
  // recursive analyse of each way.
  if (x > 0)
    {
      choice[PRIORITY] = getBestWayRec(map, x - 1, y, dist + 1, analysed);
      choice[DIRECTION] = LEFT;
    }
  analysed.resize(size);
  if (x + 1 < map[0].size() && (ret = getBestWayRec(map, x + 1, y, dist + 1, analysed)) < choice[PRIORITY])
    {
      choice[PRIORITY] = ret;
      choice[DIRECTION] = RIGHT;
    }
  analysed.resize(size);
  if (y + 1 < map.size() && (ret = getBestWayRec(map, x, y + 1, dist + 1, analysed)) < choice[PRIORITY])
    {
      choice[PRIORITY] = ret;
      choice[DIRECTION] = DOWN;
    }
  analysed.resize(size);
  if (y > 0 && (ret = getBestWayRec(map, x, y - 1, dist + 1, analysed)) < choice[PRIORITY])
    {
      choice[PRIORITY] = ret;
      choice[DIRECTION] = UP;
    }
  analysed.resize(size);

  if (choice[PRIORITY] == DEFAULT_CHOICE ||
      choice[PRIORITY] == DANGEROUS_CASE ||
      choice[PRIORITY] == FORBIDDEN_CASE)
    choice[DIRECTION] = STAGN;

  // handle priorities.
  if (choice[PRIORITY] == FORBIDDEN_CASE)
    choice[PRIORITY] = FORBIDDEN_PRIORITY;
  if (choice[PRIORITY] == DANGEROUS_CASE)
    choice[PRIORITY] = DANGEROUS_PRIORITY;
  else
    choice[PRIORITY] -= getNbrHit(map, x, y) - dist / 2;
  if (type == BONUS)
    choice[PRIORITY] += BONUS_PRIORITY;
  else
    choice[PRIORITY] += NORMAL_PRIORITY;
  return (choice[PRIORITY]);
}

/*
**	Analyse of one way to get it's priority (potential field).
*/
void	Soldier::getOneBestWay(std::vector<std::vector <AObject*> > const &map,
			       int const min, int const max, size_t const x, size_t const y,
			       char const direction, int choice[2],
			       std::vector<std::pair<size_t, size_t> > &analysed) const
{
  int	ret;

  if (min < max && (ret = getBestWayRec(map, x, y, 1, analysed)) < BAD_WAY &&
      ret < choice[PRIORITY] && !isCurrentCaseDangerous(map, x, y))
	{
	  if (isOppositeWay(direction))
	    ret += OPPOSITE_MALUS; // Malus priority apply if IA want's to change way.
	  if (ret < choice[PRIORITY])
	    {
	      choice[PRIORITY] = ret;
	      choice[DIRECTION] = direction;
	    }
	}
  analysed.resize(1); // Reinit analysed cases.
}

/*
**	Analyse each way to get the best (potential field priorities method).
*/
void	Soldier::getBestWay(std::vector<std::vector <AObject*> > const &map, size_t const x, size_t const y, int choice[2])
{
  std::vector<std::pair<size_t, size_t> > analysed; // Used to store analysed cases (to don't analyse twice the same in recursive).

  analysed.push_back(std::pair<size_t, size_t>(x, y)); // Add the current case to the analysed ones.
  choice[PRIORITY] = DEFAULT_CHOICE;

  // Analyse each way.
  getOneBestWay(map, 0, x, x - 1, y, LEFT, choice, analysed);
  getOneBestWay(map, x + 1, map[0].size(), x + 1, y, RIGHT, choice, analysed);
  getOneBestWay(map, y + 1, map.size(), x, y + 1, DOWN, choice, analysed);
  getOneBestWay(map, 0, y, x, y - 1, UP, choice, analysed);

  if (choice[PRIORITY] == DEFAULT_CHOICE)
    choice[DIRECTION] = STAGN;
  if (isOppositeWay(choice[DIRECTION]) && choice[PRIORITY] > 0 && _bombs < _maxBombs) // If IA is undecided: stagn for a while
    {
      _stagnTime = STAGN_TIME; // IA will stagn for STAGN_TIME turns.
      choice[DIRECTION] = STAGN;
    }
}

bool	Soldier::nextActionIsDangerous(std::vector<std::vector <AObject*> > const &map, char const action, size_t x, size_t y) const
{
  if (action == LEFT)
    x--;
  if (action == RIGHT)
    x++;
  if (action == UP)
    y--;
  if (action == DOWN)
    y++;
  return (isCurrentCaseDangerous(map, x, y));
}

/*
**	Analyse the best action realisable for current situation.
*/
char	Soldier::getNextAction(Field &field)
{
  std::vector<std::vector <AObject*> >	&map = field.getMap();
  size_t const	x = _character->getX();
  size_t const	y = _character->getY();
  bool		danger;
  int		choice[2];
  int		tmp;

  pickUpBonusIfPossible(field, map, x, y);
  danger = isCurrentCaseDangerous(map, x, y);
  if (danger == true)
    choice[1] = getEscapeWay(map, x, y, false);
  else
    {
      if (_lastMove == STAGN && _stagnTime > 0)
	{
	  if (_bombs == _maxBombs)
	    _stagnTime -= 1;
	  return (STAGN);
	}
      getBestWay(map, x, y, choice);

      int const	hit = getNbrHit(map, x, y);
      if (_bombs > 0 && hit && -hit < choice[PRIORITY] && (tmp = getEscapeWay(map, x, y, true)) != -1 && !nextActionIsDangerous(map, tmp, x, y))
	choice[DIRECTION] = PUT_BOMB;

    }
  if (nextActionIsDangerous(map, choice[DIRECTION], x, y) && !isCurrentCaseDangerous(map, x, y))
    choice[DIRECTION] = STAGN;
  _lastMove = choice[DIRECTION];
  return (choice[DIRECTION]);
}
