//
// Warrior.cpp for  in /home/menich_a/rendu/cpp_bomberman/work_in_progress/v6
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Wed May 27 16:26:29 2015 Anatole Menichetti
// Last update Sat Jun 13 15:51:21 2015 Anatole Menichetti
//

#include "Warrior.hpp"
#include <algorithm>

Warrior::Warrior(Character* const character, size_t const id, std::vector<Character*> &ennemies) :
  Bot(character, id), _ennemies(ennemies)
{}

/*
**	Recursive analyse of each way with potential field priorities method.
*/
int	Warrior::getBestWayRec(std::vector<std::vector <AObject*> > const &map, size_t const x, size_t const y, int const dist, std::vector<std::pair<size_t, size_t> > &analysed) const
{
  std::pair<size_t, size_t>	pos(x, y);

  int		xi = static_cast<int>(x);
  int		yi = static_cast<int>(y);
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
  if (currentCaseIsBetweenThreeWalls(map, x, y))
    choice[PRIORITY] += 5;
  return (choice[PRIORITY]);
}

/*
**	Analyse of one way to get it's priority (potential field).
*/
void	Warrior::getOneBestWay(std::vector<std::vector <AObject*> > const &map,
			       int const min, int const max, size_t const x, size_t const y,
			       char const direction, int choice[2],
			       std::vector<std::pair<size_t, size_t> > &analysed) const
{
  int	ret;

  if (min < max && (ret = getBestWayRec(map, x, y, 1, analysed)) < BAD_WAY &&
      (ret < choice[PRIORITY] || (ret == choice[PRIORITY] && isOppositeWay(choice[DIRECTION]) && direction == _lastMove)) && !isCurrentCaseDangerous(map, x, y))
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
**	Valeur absolue
*/
int	Warrior::absoluteValue(int const value) const
{
  return (value > 0 ? value : -value);
}

/*
**	Fill the tab with malus for each direction which is less than 10 cases from an ennemy
*/
void	Warrior::getEnnemiesDirections(int directions[4], bool const checkIfSameLine) const
{
  size_t	i = 0;
  int		distanceX;
  int		distanceY;
  int		bonusHits = 0;
  size_t const	x = _character->getX();
  size_t const	y = _character->getY();

  while (i < 4)
    {
      directions[i] = 0;
      i += 1;
    }
  i = 0;
  while (i < _ennemies.size())
    {
      distanceX = x - _ennemies[i]->getX();
      distanceY = y - _ennemies[i]->getY();
      if (distanceX || distanceY)
	{
	  if (checkIfSameLine && (!distanceX || !distanceY))
	    bonusHits += DISTANCE_ENNEMY_MAX;
	  if (absoluteValue(distanceX) + absoluteValue(distanceY) < DISTANCE_ENNEMY_MAX)
	    {
	      if (distanceX > 0 && DISTANCE_ENNEMY_MAX - distanceX > directions[LEFT])
		directions[LEFT] = DISTANCE_ENNEMY_MAX - distanceX;
	      if (distanceX < 0 && DISTANCE_ENNEMY_MAX + distanceX > directions[RIGHT])
		directions[RIGHT] = DISTANCE_ENNEMY_MAX + distanceX;
	      if (distanceY > 0 && DISTANCE_ENNEMY_MAX - distanceY > directions[UP])
		directions[UP] = DISTANCE_ENNEMY_MAX - distanceY;
	      if (distanceY < 0 && DISTANCE_ENNEMY_MAX + distanceY > directions[DOWN])
		directions[DOWN] = DISTANCE_ENNEMY_MAX + distanceY;
	    }
	}
      i += 1;
    }
  i = 0;
  if (!checkIfSameLine)
    while (i < 4)
      {
	if (directions[i])
	  directions[i] += MALUS_NEAR_ENNEMY;
	i += 1;
      }
  directions[0] += bonusHits;
}

/*
**	Analyse each way to get the best (potential field priorities method).
*/
void	Warrior::getBestWay(std::vector<std::vector <AObject*> > const &map, size_t const x, size_t const y, int choice[2])
{
  std::vector<std::pair<size_t, size_t> > analysed; // Used to store analysed cases (to don't analyse twice the same in recursive).
  int	ennemiesDirections[4];

  getEnnemiesDirections(ennemiesDirections, false);
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

bool	Warrior::nextActionIsDangerous(std::vector<std::vector <AObject*> > const &map, char const action, size_t x, size_t y) const
{
  if (action == LEFT)
    x--;
  if (action == RIGHT)
    x++;
  if (action == UP)
    y--;
  if (action == DOWN)
    y++;
  return (isCurrentCaseDangerous(map, x, y) || cannotAccessThisCase(map, x, y, true));
}

/*                                                                                                                   
**      Return the number of boxes hit if a bomb was at x;y - returns 0 if a bonus may be hit.                       
*/
int     Warrior::getNbrHit(std::vector<std::vector <AObject*> > const &map, size_t const x, size_t const y) const
{
  int   power;
  int   hit = 0;

  // get left hits.                                                                                                  
  power = 0;
  while (x - power > 0 && power < _power / 2 && !isThereObstacle(map, x - power, y))
    power += 1;
  if (static_cast<int>(x) - power >= 0 && map[y][x - power])
    {
      if (map[y][x - power]->getType() == BONUS)
        return (0);
      if (map[y][x - power]->getType() == BOX)
        hit += 1;
    }
  // get right hits.                                                                                                 
  power = 0;
  while (x + power + 1 < map[y].size() && power < _power / 2 && !isThereObstacle(map, x + power, y))
    power += 1;
  if (x + power < map[y].size() && map[y][x + power])
    {
      if (map[y][x + power]->getType() == BONUS)
        return (0);
      if (map[y][x + power]->getType() == BOX)
        hit += 1;
    }
  // get up hits.                                                                                                    
  power = 0;
  while (static_cast<int>(y) - power > 0 && power < _power / 2 && !isThereObstacle(map, x, y - power))
    power += 1;
  if (static_cast<int>(y) - power >= 0 && map[y - power][x])
    {
      if (map[y - power][x]->getType() == BONUS)
        return (0);
      if (map[y - power][x]->getType() == BOX)
        hit += 1;
    }
  // get down hits.                                                                                                  
  power = 0;
  while (y + power + 1 < map.size() && power < _power / 2 && !isThereObstacle(map, x, y + power))
    power += 1;
  if (y + power < map.size() && map[y + power][x])
    {
      if (map[y + power][x]->getType() == BONUS)
        return (0);
      if (map[y + power][x]->getType() == BOX)
        hit += 1;
    }
  return (hit);
}

/*
**	Analyse the best action realisable for current situation.
*/
char	Warrior::getNextAction(Field &field)
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
      choice[DIRECTION] = getEscapeWay(map, x, y, false);
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
      int	ennemiesDirections[4];

      getEnnemiesDirections(ennemiesDirections, true);
      for (int i = 0 ; i < 4 ; i++)
	if (ennemiesDirections[i] - _power > 0)
	  hit += ennemiesDirections[i];
      if (_bombs > 0 && hit && -hit < choice[PRIORITY] &&
	  (tmp = getEscapeWay(map, x, y, true)) != -1 && !nextActionIsDangerous(map, tmp, x, y))
	choice[DIRECTION] = PUT_BOMB;
      if (nextActionIsDangerous(map, choice[DIRECTION], x, y) && !isCurrentCaseDangerous(map, x, y))
	choice[DIRECTION] = STAGN;
    }
  _lastMove = choice[DIRECTION];
  return (choice[DIRECTION]);
}
