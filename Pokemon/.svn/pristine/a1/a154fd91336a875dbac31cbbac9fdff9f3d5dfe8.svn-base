#ifndef	__MAP_HPP__
#define	__MAP_HPP__

#include <string>
#include "mySDL.hpp"

#define	FLOOR	'.'
#define	WALL	'w'
#define	GRASS	'g'
#define	TREE	't'

class		Map
{
private:
  std::string	_map;

  SDL_Surface	*floor;
  SDL_Surface	*wall;
  SDL_Surface	*tree;
  SDL_Surface	*grass;

public:
  Map(std::string map);
  ~Map();

  void	affCase(int x, int y, char c, mySDL *sdl);
  void	affMap(mySDL *sdl, int x, int y, int posx, int posy);

  char	getChar(int x, int y);
  int	goToLine(int line);
};

#endif
