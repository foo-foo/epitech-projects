//
// Map.hpp for Map in /home/rosain_f/projects/zappy/graphic
// 
// Made by Francois Rosain
// Login   <rosain_f@epitech.net>
// 
// Started on  Mon Jun 29 10:00:43 2015 Francois Rosain
// Last update Sun Jul  5 11:13:14 2015 Francois Rosain
//

#ifndef _MAP_
# define _MAP_

# include <iostream>
# include <unistd.h>
# include <string>
# include <map>
# include <vector>

/* LibGDL */

# include "Texture.hh"

/* Map */
# include "AObject.hpp"
# include "Ground.hpp"
# include "Character.hpp"
# include "Egg.hpp"

# define MAP_TO_VECTOR(x, y, size)	(x + y * size)
# define MAP_MIN_SIZE	5

# define MAP_MAX_SIZE	625

class	Map
{
private:
  size_t				_sizeX;
  size_t				_sizeY;
  std::map<std::string, gdl::Texture*>	_textures;
  std::map<std::string, gdl::Model*>	_models;
  std::vector<AObject*>			_ground;
  std::vector<Character*>		_characters;
  std::vector<Egg*>			_eggs;
  void					_createGround();

public:
  Map(size_t, size_t);
  ~Map() {};
  
  size_t				getSizeX() const;
  size_t				getSizeY() const;
  std::map<std::string, gdl::Texture*>&	getTextures();
  std::map<std::string, gdl::Model*>&	getModels();
  std::vector<AObject*>&		getGround();
  std::vector<Character*>&		getCharacters();
  std::vector<Egg*>&			getEggs();

  void		initialize();
  bool		addTexture(std::string, std::string);
  bool		addModel(std::string, std::string);

  bool		isSizeOk() const;
  void		addCharacter(Character*);
  void		addEgg(size_t, size_t);
  void		removeEgg(int id);
  void		addRessource(int, int, e_object);
  void		resetGround(size_t, size_t);
};

#endif /* !_MAP_ */
