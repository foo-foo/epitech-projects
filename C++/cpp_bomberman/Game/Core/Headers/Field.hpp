//
// Field.hpp for  in /home/menich_a/rendu/bomberbkp/Game/Game/Headers
// 
// Made by Anatole Menichetti
// Login   <menich_a@epitech.net>
// 
// Started on  Sat Jun 13 10:26:11 2015 Anatole Menichetti
// Last update Sat Jun 13 10:30:45 2015 Anatole Menichetti
//

#ifndef FIELD_HPP_
# define FIELD_HPP_

# include <iostream>
# include <fstream>
# include <string>
# include <map>
# include <vector>
# include <cstdlib>

/* Objects */

# include "Model.hh"
# include "Texture.hh"
# include "AObject.hpp"
# include "Wall.hpp"
# include "Box.hpp"
# include "Ground.hpp"

/* Objects in String */

# define CEMPTY	'-'
# define CBOX	'B'
# define CWALL	'W'

/* Gameplay */

# define MAP_MIN_SIZE	5

# define VISION	11


class Field
{
private:
  size_t	_height;
  size_t	_width;
  bool const	_random;
  std::vector<std::string*>			_mapInStr;
  std::vector< std::vector< AObject * > >	_map;
  std::vector< std::vector< AObject * > >	_ground;
  AObject*					_background;
  std::vector< std::vector< AObject * > * >	*_saveMapCoor;

  std::map<std::string, gdl::Model*>	_models;
  std::map<std::string, gdl::Texture*>	_textures;

  /* Create Map */
  void	_createMapFromStr();
  void	_createGround();
  void  _createWall();
  void  _createBoxY();
  void	_createBoxX();

public:
  Field(size_t, size_t);
  Field(std::string);
  ~Field();

  /* Create Map */  
  void	        initialize();

  /* Get */
  size_t	getHeight() const;
  size_t	getWidth() const;
  bool		getRandom() const;
  std::map<std::string, gdl::Model*>	&getModels();
  std::map<std::string, gdl::Texture*>&	getTextures();

  std::vector< std::vector< AObject * > > &	getMap();
  std::vector< std::vector< AObject * > * >&		getMapCoor(ssize_t y, ssize_t x);
  std::vector< std::vector< AObject * > > const &	getGround() const;
  AObject*						getBackground() const;
  
  /* Other */
  bool	addTexture(std::string const &, std::string const &);
  bool	addModel(std::string const &, std::string const &);
};

#endif //!FIELD_HPP_
