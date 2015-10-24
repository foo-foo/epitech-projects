//
// Bot.cpp for  in /home/menich_a/rendu/cpp_bomberman/work_in_progress/v6
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Wed May 27 16:26:29 2015 Anatole Menichetti
// Last update Tue Sep 15 09:51:53 2015 Anatole Menichetti
//

#include "Bot.hpp"
#include <algorithm>

Bot::Bot(Character* const character, size_t const id) :
  APlayer(character, id), _maxBombs(DEFAULT_BOMBS), _lastMove(STAGN), _stagnTime(0), _nbrStagnTurns(0)
{}

/*
**	Used to check if putting a bomb will be dangerous for IA.
*/
bool	Bot::willCurrentCaseBeDangerous(std::vector<std::vector <AObject*> > const &map, size_t x, size_t y) const
{
  size_t const	x0 = x;
  size_t const	characterX = _character->getX();
  size_t const	characterY = _character->getY();

  if (x == characterX)
    {
      while (x > characterX && (!map[y][x] || (map[y][x]->getType() != WALL && map[y][x]->getType() != BOX)))
	x -= 1;
      while (x < characterX && (!map[y][x] || (map[y][x]->getType() != WALL && map[y][x]->getType() != BOX)))
	x += 1;
      if (x == characterX)
	return (true);
    }
  if (y == characterY)
    {
      x = x0;
      while (y > characterY && (!map[y][x] || (map[y][x]->getType() != WALL && map[y][x]->getType() != BOX)))
	y -= 1;
      while (y < characterY && (!map[y][x] || (map[y][x]->getType() != WALL && map[y][x]->getType() != BOX)))
	y += 1;
      if (y == characterY)
	return (true);
    }
  return (false);
}

/*
**	Used to check the state of the current case.
*/
bool	Bot::cannotAccessThisCase(std::vector<std::vector <AObject*> > const &map, int const x, int const y, bool const needToPutBomb) const
{
  if (!map[y][x])
    return (false);

  int const	type = map[y][x]->getType();

  if (needToPutBomb)
    return (type == BOX || type == WALL || type == CHARACTER || type == FLAME || type == BOMB);
  return (type == BOX || type == WALL || type == CHARACTER);
}

/*
**	Recursive analyse for one way with potential field prorities method.
*/
void	Bot::getOneEscapeWayRec(std::vector<std::vector <AObject*> > const &map,
				int const min, int const max, size_t const x, size_t const y,
				int &choice, bool const needToPutBomb, size_t const dist,
				std::vector<std::pair<size_t, size_t> > &analysed) const
{
  int		ret;
  int const	size = analysed.size();

  if (min < max && (ret = getEscapeWayRec(map, x, y, needToPutBomb, dist + 1, analysed)) >= 0 && ret < choice)
    choice = ret;
  analysed.resize(size); // Reinit analysed cases to cases analysed at function start.
}

bool	Bot::currentCaseIsBetweenThreeWalls(std::vector<std::vector <AObject*> > const &map, size_t const x, size_t const y) const
{
  size_t	cpt = 0;

  if (!x || (map[y][x - 1] && (map[y][x - 1]->getType() == FLAME || map[y][x - 1]->getType() == BOMB || map[y][x - 1]->getType() == BOX || map[y][x - 1]->getType() == WALL)))
    cpt += 1;
  if (x + 1 == map[y].size() || (map[y][x + 1] && (map[y][x + 1]->getType() == FLAME || map[y][x + 1]->getType() == BOMB || map[y][x + 1]->getType() == BOX || map[y][x + 1]->getType() == WALL)))
    cpt += 1;
  if (!y || (map[y - 1][x] && (map[y - 1][x]->getType() == FLAME || map[y - 1][x]->getType() == BOMB || map[y - 1][x]->getType() == BOX || map[y - 1][x]->getType() == WALL)))
    cpt += 1;
  if (y + 1 == map.size() || (map[y + 1][x] && (map[y + 1][x]->getType() == FLAME || map[y + 1][x]->getType() == BOMB || map[y + 1][x]->getType() == BOX || map[y + 1][x]->getType() == WALL)))
    cpt += 1;
  return (cpt > 2);
}

/*
**	Recursive analyse for every way with potential field prorities method.
*/
int	Bot::getEscapeWayRec(std::vector<std::vector <AObject*> > const &map, size_t const x, size_t const y, bool const needToPutBomb, size_t const dist, std::vector<std::pair<size_t, size_t> > &analysed) const
{
  std::pair<size_t, size_t> const	pos(x, y);

  int const	xi = static_cast<int>(x);
  int const	yi = static_cast<int>(y);
  int		choice = DEFAULT_CHOICE;

  if (dist > PREVISION_MAX || cannotAccessThisCase(map, x, y, true) ||
      std::find(analysed.begin(), analysed.end(), pos) != analysed.end()) // Stop analyse: current case is not accessible
    return (-1);
  analysed.push_back(pos);
  if (!isCurrentCaseDangerous(map, x, y) &&
      (!needToPutBomb || !willCurrentCaseBeDangerous(map, x, y))) // Stop analyse: current case is safe.
    {
      if (currentCaseIsBetweenThreeWalls(map, x, y))
	return (5);
      return (1);
    }

  getOneEscapeWayRec(map, 0, x, x - 1, y, choice, needToPutBomb, dist, analysed);
  getOneEscapeWayRec(map, x + 1, map[0].size(), x + 1, y, choice, needToPutBomb, dist, analysed);
  getOneEscapeWayRec(map, y + 1, map.size(), x, y + 1, choice, needToPutBomb, dist, analysed);
  getOneEscapeWayRec(map, 0, y, x, y - 1, choice, needToPutBomb, dist, analysed);

  if (choice == DEFAULT_CHOICE) // if not any way is concluant: stop searching.
    return (-1);

  if (map[yi][xi] && map[yi][xi]->getType() == BONUS) // if current case is a bonus: priority is high.
    choice += ESCAPE_BONUS_PRIORITY;
  else
    choice += ESCAPE_NORMAL_PRIORITY; // if current case is empty: priority is low.
  return (choice);
}

/*
**	Used to get the escape way priority for one direction.
*/
void	Bot::getOneEscapeWay(std::vector<std::vector <AObject*> > const &map, int choice[2], char const direction,
			     int const min, int const max, int const x, int const y, bool const needToPutBomb,
			     std::vector<std::pair<size_t, size_t> > &analysed) const
{
  int	ret;

  if (min < max && (ret = getEscapeWayRec(map, x, y, needToPutBomb, 1, analysed)) >= 0 && ret < choice[PRIORITY])
    {
      if (!isOppositeWay(direction) || ret + OPPOSITE_MALUS < choice[0])
	{
	  if (isOppositeWay(direction)) // Malus priority is apply if IA wants to change way.
	    ret += OPPOSITE_MALUS;
	  choice[PRIORITY] = ret;
	  choice[DIRECTION] = direction;
	}
    }
  analysed.resize(1); // Reinit the analysed cases.
}



/*
**	Used to get the best escape way (with potential field priorities method).
*/
char	Bot::getEscapeWay(std::vector<std::vector <AObject*> > const &map, size_t const x, size_t const y, bool const needToPutBomb) const
{
  std::vector<std::pair<size_t, size_t> >	analysed; // analysed cases - to don't analyse twice same case in recursive
  int	choice[2];

  choice[PRIORITY] = DEFAULT_CHOICE;
  analysed.push_back(std::pair<size_t, size_t>(x, y)); // Used to store the analysed cases.

  getOneEscapeWay(map, choice, LEFT, 0, x, x - 1, y, needToPutBomb, analysed);
  getOneEscapeWay(map, choice, RIGHT, x + 1, map[0].size(), x + 1, y, needToPutBomb, analysed);
  getOneEscapeWay(map, choice, DOWN, y + 1, map.size(), x, y + 1, needToPutBomb, analysed);
  getOneEscapeWay(map, choice, UP, 0, y, x, y - 1, needToPutBomb, analysed);

  if (choice[PRIORITY] == DEFAULT_CHOICE) // Not any way is concluant.
    return (-1);
  return (choice[DIRECTION]); // Best way.
}

/*
**	Used to check if current case isn't safe. If it's not, then need to look for escape way.
*/
bool	Bot::isCurrentCaseDangerous(std::vector<std::vector <AObject*> > const &map, size_t const x, size_t const y) const
{
  int const	x0 = static_cast<int>(x);
  int const	y0 = static_cast<int>(y);
  int		xi = static_cast<int>(x);
  int		yi = static_cast<int>(y);

  // check current case.
  if (map[yi][xi] && (map[yi][xi]->getType() == BOMB || map[yi][xi]->getType() == FLAME))
    return (true);
  // check left side cases.
  while (xi >= 0 && (!map[yi][xi] || map[yi][xi]->getType() != WALL || map[yi][xi]->getType() != BOX))
    {
      if (map[yi][xi] && map[yi][xi]->getType() == BOMB)
	{ 
	  if (dynamic_cast<Bomb*>(map[yi][xi])->getPlayer().getPower() / 2 + xi + 1 >= x0)
	    return (true);
	  else
	    break;
	}
      xi -= 1;
    }
  // check right side cases.
  xi = static_cast<int>(x);
  while (static_cast<size_t>(xi) < map[yi].size() && (!map[yi][xi] || map[yi][xi]->getType() != WALL || map[yi][xi]->getType() != BOX))
    {
      if (map[yi][xi] && map[yi][xi]->getType() == BOMB)
	{
	  if (xi - (dynamic_cast<Bomb*>(map[yi][xi])->getPlayer().getPower() / 2 + 1) <= x0)
	    return (true);
	  else
	    break;
	}
      xi += 1;
    }
  // check down side cases.
  xi = static_cast<int>(x);
  while (static_cast<size_t>(yi) < map.size() && (!map[yi][xi] || map[yi][xi]->getType() != WALL || map[yi][xi]->getType() != BOX))
    {
      if (map[yi][xi] && map[yi][xi]->getType() == BOMB)
	{
	  if (yi - (dynamic_cast<Bomb*>(map[yi][xi])->getPlayer().getPower() / 2 + 1) <= y0)
	    return (true);
	  else
	    break;
	}
      yi += 1;
    }
  // check up side cases.
  yi = static_cast<int>(y);
  while (yi >= 0 && (!map[yi][xi] || map[yi][xi]->getType() != WALL || map[yi][xi]->getType() != BOX))
    {
      if (map[yi][xi] && map[yi][xi]->getType() == BOMB)
	{
	  if (dynamic_cast<Bomb*>(map[yi][xi])->getPlayer().getPower() / 2 + 1 + yi >= y0)
	    return (true);
	  else
	    break;
	}
      yi -= 1;
    }
  return (false);
}

bool	Bot::isThereObstacle(std::vector<std::vector <AObject*> > const &map, size_t const x, size_t const y) const
{
  return (map[y][x] &&
      (map[y][x]->getType() == WALL ||
       map[y][x]->getType() == BOMB ||
       map[y][x]->getType() == BOX ||
       map[y][x]->getType() == BONUS ||
       map[y][x]->getType() == CHARACTER));
}

/*
**	Return the number of boxes hit if a bomb was at x;y - returns 0 if a bonus may be hit.
*/
int	Bot::getNbrHit(std::vector<std::vector <AObject*> > const &map, size_t const x, size_t const y) const
{
  int	power;
  int	hit = 0;

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
**	Check if the next move will be opposite to the last move.
*/
bool	Bot::isOppositeWay(char const move) const
{
  if (move == STAGN)
    return (false);
  return ((_lastMove == RIGHT && move == LEFT) ||
	  (_lastMove == LEFT && move == RIGHT) ||
	  (_lastMove == UP && move == DOWN) ||
	  (_lastMove == DOWN && move == UP));
}

/*
**	Look if there is a bonus on current case. If there is: enable the bonus.
*/
void	Bot::pickUpBonusIfPossible(Field &field, std::vector<std::vector <AObject*> > &map, int const x, int const y)
{
  if (static_cast<size_t>(y) < field.getHeight() && static_cast<size_t>(x) < field.getWidth()
      && map[y][x] != NULL
      && map[y][x]->getType() == BONUS)
    {
      if (reinterpret_cast<ABonus*>(map[y][x])->getType() == BOMB && _maxBombs < BOMB_LIMIT) // _maxBombs is used to know if a bomb have been put.
	_maxBombs += 1;
      reinterpret_cast<ABonus*>(map[y][x])->activate(this);
      delete map[y][x];
      map[y][x] = NULL;
    }
}

/*
**	Update the player action.
*/
void	Bot::update(gdl::Clock const &clock, Field& map)
{
  float	add;
  int	action;

  if (_character->isDancing())
    return ;
  action = getNextAction(map);
  if (action < 0 || action == STAGN)
    {
      if (++_nbrStagnTurns > STAGN_LIMIT)
	action = PUT_BOMB;
    }
  else
    _nbrStagnTurns = 0;
  if ((add = 0.1f * static_cast<float>(clock.getElapsed()) * SPEED(_speed)) > BOT_MAX_SPEED)
    add = BOT_MAX_SPEED;
  if (action < 4)
    (_character->*_launchMove[action])(add);
  else
    {
      _character->pauseModel();
      if (action == PUT_BOMB && map.getMap()[_character->getY()][_character->getX()] == NULL && _bombs > 0)
	{
	  map.getMap()[_character->getY()][_character->getX()] = new Bomb(static_cast<int>(_character->getY()), static_cast<int>(_character->getX()), this, *map.getModels()["Bomb"]);
	  map.getMap()[_character->getY()][_character->getX()]->initialize();
	  _bombs--;
	}
    }
}

