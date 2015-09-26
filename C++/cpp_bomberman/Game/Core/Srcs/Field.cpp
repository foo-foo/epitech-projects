//
// Field.cpp for Field in /home/rosain_f/rendu/cpp_bomberman/work_in_progress/v5
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Fri May 15 14:08:05 2015 Francois Rosain
// Last update Sat Jun 13 10:30:10 2015 Anatole Menichetti
//

#include "Field.hpp"

Field::Field(size_t y, size_t x)
  : _height((y % 2) ? y + 2 : y + 3), _width((x % 2) ? x + 2 : x + 3), _random(true), _saveMapCoor(NULL)
{}

Field::Field(std::string file)
  : _random(false), _saveMapCoor(NULL)
{
  std::ifstream	ifs;
  char		c;
  int		i = 0;

  ifs.open(file.c_str());
  if (!ifs.is_open())
    std::cout << "Map Error : Can\'t open file : " << file << std::endl;
  // throw

  // Fill the string containing map objects.
  _mapInStr.push_back(new std::string);
  while (ifs.good())
    {
      c = ifs.get();
      if (c == '\n')
	{
	  _mapInStr.push_back(new std::string);
	  i++;
	}
      else if (c != EOF)
	*_mapInStr[i] += c;
    }
  ifs.close();

  _height = (_mapInStr.size() % 2 ? _mapInStr.size() : _mapInStr.size());
  _width = (_mapInStr[0]->size() % 2 ? _mapInStr[0]->size() : _mapInStr[0]->size());

  /* Check map size */
  if (_height < MAP_MIN_SIZE
      || _width < MAP_MIN_SIZE)
    std::cout << "Map Error : too small." << std::endl; // throw

  /* Check map equilibrate */
  for (unsigned int h = 0; h < _height; h++)
    if (_mapInStr[h]->size() != _width)
      std::cout << "Map Error : not equilibrated." << h << std::endl; // throw

  /* Check objects on map */
  for (unsigned int h = 0; h < _height; h++)
    for (unsigned int i = 0; i < _width; i++)
      {
	if ((*_mapInStr[h])[i] != CEMPTY
	    && (*_mapInStr[h])[i] != CWALL
	    && (*_mapInStr[h])[i] != CBOX)
	  std::cout << "Map Error : invalid character." << std::endl; // throw
      }

  /* Correction of the map */
  (*_mapInStr[0])[0] = CEMPTY;
  (*_mapInStr[0])[1] = CEMPTY;
  (*_mapInStr[1])[0] = CEMPTY;
   
  (*_mapInStr[0])[_width - 2] = CEMPTY;
  (*_mapInStr[0])[_width - 1] = CEMPTY;
  (*_mapInStr[1])[_width - 1] = CEMPTY;

  (*_mapInStr[_height - 2])[0] = CEMPTY;
  (*_mapInStr[_height - 1])[0] = CEMPTY;
  (*_mapInStr[_height - 1])[1] = CEMPTY;

  (*_mapInStr[_height - 2])[_width - 1] = CEMPTY;
  (*_mapInStr[_height - 1])[_width - 2] = CEMPTY;
  (*_mapInStr[_height - 1])[_width - 1] = CEMPTY;

  /* Display Map */
  std::cout << "map" << std::endl;
  for (unsigned int h = 0; h < _height; h++)
    std::cout << *_mapInStr[h] << h << std::endl;

  _height += 2;
  _width += 2;
  std::cout << ">>> >>> >>> FIELD CREATED" << std::endl;
}

Field::~Field()
{
  size_t	x, y;
  
  y = 0;
  while (y < _map.size())
    {
      // if(_saveMapCoor != NULL && _saveMapCoor->size() > y)
      // 	delete (*_saveMapCoor)[y];
      x = 0;
      if (!_map[y].empty())
	{
	  while (x < _map[y].size())
	    {
	      delete _map[y][x];
	      x++;
	    }
	  y++;
	}
    }
  // if(_saveMapCoor != NULL)
  //   delete _saveMapCoor;
}


/*
** Create Map
*/

void	Field::_createWall()
{
  size_t	y, x;

  y = 0;
  while (y < _height)
    {
      _map.push_back(std::vector<AObject*>(_width));
      x = 0;
      while (x < _width)
	{
	  _map[y][x] = 
	    (((x % 2) == 1 && (y % 2) == 1) || x == 0 || x == _width - 1 || y == 0 || y == _height - 1) ? new Wall(_textures["Wall"])  : NULL ; 
	  ++x;
	}	
      ++y;
    }
}

void	Field::_createBoxY()
{
  size_t	y, x;

  //etape 2 : mis en plase de mur cassable sur les adresse x inpaire 
  y = 0;
  while (y < _height / 2)
    {
      x = 0;
      while ((y % 2) && x < y)
	{
	  if (_map[y][x] == NULL)
	    _map[y][x] = new Box(_textures["Box"]);
	  if (_map[y][_width - x - 1] == NULL)
	    _map[y][_width - x - 1] = new Box(_textures["Box"]);
	  if (_map[_height - y - 1][_width - x - 1] == NULL)
	    _map[_height - y - 1][_width - x - 1] = new Box(_textures["Box"]);
	  if (_map[_height - y - 1][x] == NULL)
	    _map[_height - y - 1][x] = new Box(_textures["Box"]);
	  ++x;
	}
      ++y;
    }
}

void	Field::_createBoxX()
{
  size_t	y, x;

  //etape 3 : mis en plase de mur cassable sur les adresse y inpaire 
  x = 0;
  while (x < _width / 2)
    {
      y = 0;
      while (x > 1 && (x % 2) && y < x + 1)
	{
	  if (_map[y][x] == NULL)
	    _map[y][x] = new Box(_textures["Box"]);
	  if (_map[_height - y - 1][x] == NULL)
	    _map[_height - y - 1][x] = new Box(_textures["Box"]);
	  if (_map[_height - y - 1][_width - x - 1] == NULL)
	    _map[_height - y - 1][_width - x - 1] = new Box(_textures["Box"]);
	  if (_map[y][_width - x - 1] == NULL)
	    _map[y][_width - x - 1] = new Box(_textures["Box"]);
	  ++y;
	}
      ++x;
    }
}

void	Field::_createGround()
{
  size_t	x, y;

  y = 0;
  x = 0;
  while (y < _height)
    {
      _ground.push_back(std::vector< AObject *>(_width));
      x = 0;
      while (x < _width)
  	{
  	  _ground[y][x] = new Ground(_textures["Grass"]);
  	  x++;
  	}
      y++;
    }
  _background = new Ground(_textures["Sky"]);
}

/*
**	Create a map with a string from a map file.
*/
void	Field::_createMapFromStr()
{
  // Only walls on first line
  _map.push_back(std::vector<AObject*>(_width));
  for (size_t x = 0; x < _width; x++)
    _map[0][x] = new Wall(_textures["Wall"]);

  // Other lines
  for (size_t h = 1; h < _height - 1; h++)
    {
      _map.push_back(std::vector<AObject*>(_width));
      // Wall on first case of each line
      _map[h][0] = new Wall(_textures["Wall"]);
      // Str defined cases
      for (size_t w = 1; w < _width - 1; w++)
	{
	  if ((*_mapInStr[h - 1])[w - 1] == CBOX)
	    _map[h][w] = new Box(_textures["Box"]);
	  else if ((*_mapInStr[h - 1])[w - 1] == CWALL)
	    _map[h][w] = new Wall(_textures["Wall"]);
	  else
	    _map[h][w] = NULL;
	}
      // Wall on last case of each line
      _map[h][_width - 1] = new Wall(_textures["Wall"]);
    }
  // Only walls on last line
  _map.push_back(std::vector<AObject*>(_width));
  for (size_t x = 0; x < _width; x++)
    _map[_height - 1][x] = new Wall(_textures["Wall"]);
}

void	Field::initialize()
{
  if (!addTexture("Box", "./Textures/box.tga")
      || !addTexture("Wall", "./Textures/wall.tga")
      || !addTexture("Grass", "./Textures/grass.tga")
      || !addTexture("Sky", "./Textures/sky.tga")
      || !addTexture("LeftPipe", "./Textures/leftPipe.tga")
      || !addTexture("RightPipe", "./Textures/rightPipe.tga")
      || !addTexture("Icon_Bomb", "./Textures/bomb.tga")
      || !addTexture("Icon_Power", "./Textures/power.tga")
      || !addTexture("Icon_Speed", "./Textures/speed.tga")
      || !addTexture("Face_One", "./Textures/mario_face.tga")
      || !addTexture("Face_Two", "./Textures/luigi_face.tga")
      || !addModel("Bomb", "./Assets/bobomb/bobomb.fbx")
      || !addModel("Mushroom", "./Assets/mushroom/MarioShroom_Red.fbx")
      || !addModel("Flower", "./Assets/Fire/I_fireflower.obj")
      || !addModel("Star", "./Assets/Star/Star.fbx"))
    std::cout << "Can\'t load textures." << std::endl;
  _createGround();
  if (_random)
    {
      _createWall();
      _createBoxY();
      _createBoxX();
    }
  else
    _createMapFromStr();
}

/*
** Get
*/

size_t	Field::getHeight() const
{
  return (_height);
}

size_t	Field::getWidth() const
{	
  return (_width);
}

std::map<std::string, gdl::Model*>		&Field::getModels()
{
  return (_models);
}

std::map<std::string, gdl::Texture*>&		Field::getTextures()
{
  return (_textures);
}

std::vector< std::vector< AObject* > > &	Field::getMap()
{
  return (_map);
}

std::vector< std::vector< AObject* > > const &	Field::getGround() const
{
  return (_ground);
}

AObject*	Field::getBackground() const
{
  return (_background);
}

/*
**	Other
*/

bool    Field::addTexture(std::string const &name, std::string const &path)
{
  gdl::Texture	*texture = new gdl::Texture();

  if (!texture->load(path))
    {
      std::cout << "Error : Can\'t load texture <" << path << ">" << std::endl;
      return (false);
    }
  _textures[name] = texture;
  return (true);
}

bool    Field::addModel(std::string const &name, std::string const &path)
{
  gdl::Model	*model = new gdl::Model();

  if (!model->load(path))
    {
      std::cout << "Error : Can\'t load model <" << path << ">" << std::endl;
      return (false);
    }
  _models[name] = model;
  return (true);
}
