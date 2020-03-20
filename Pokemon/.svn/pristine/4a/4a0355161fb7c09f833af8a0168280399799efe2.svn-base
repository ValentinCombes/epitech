#ifndef	__TRAINER_HPP__
#define	__TRAINER_HPP__

#include "mySDL.hpp"
#include "map.hpp"
#include <string>
// #include "pokemon.hpp"
// #include "objects.hpp"

// #include <list>

class		Trainer
{
private:
  std::string		_name;
  // std::list<Pokemon>	team;
  // std::list<Object>	inventory;
  // std::list<Badge>	badges;
  SDL_Surface		*up1;
  SDL_Surface		*up2;
  SDL_Surface		*up3;
  SDL_Surface		*down1;
  SDL_Surface		*down2;
  SDL_Surface		*down3;
  SDL_Surface		*left1;
  SDL_Surface		*left2;
  SDL_Surface		*left3;
  SDL_Surface		*right1;
  SDL_Surface		*right2;
  SDL_Surface		*right3;
  SDL_Surface		*curframe;
  Map			*map;
  SDL_Rect		mappos;
  SDL_Rect		pos;
  unsigned int		x;
  unsigned int		y;
  bool			isOnBike;

public:
  Trainer(std::string name, mySDL *sdl);
  ~Trainer();

  SDL_Rect		*getPos();
  SDL_Surface		*getCurFrame();
  mySDL			*sdlpoint;

  void			moveUp();
  void			moveDown();
  void			moveLeft();
  void			moveRight();
  void			useBike();
  void			setMap(Map *map);

  int			getX();
  int			getY();
};

#endif
