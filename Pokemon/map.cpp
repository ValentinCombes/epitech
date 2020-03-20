#include "map.hpp"

Map::Map(std::string map) : _map(map)
{
  floor = IMG_Load("textures/floor.png");
  wall = IMG_Load("textures/wall.png");
  tree = IMG_Load("textures/tree.png");
  grass = IMG_Load("textures/grass.png");
}

Map::~Map()
{
  SDL_FreeSurface(floor);
  SDL_FreeSurface(wall);
  SDL_FreeSurface(tree);
  SDL_FreeSurface(grass);
}

void		Map::affCase(int x, int y, char c, mySDL *sdl)
{
  SDL_Rect	pos;

  pos.x = x - 16;
  pos.y = y - 16;
  switch (c)
    {
    case FLOOR:
      SDL_BlitSurface(floor, NULL, sdl->screen, &pos);
      break;
    case WALL:
      SDL_BlitSurface(wall, NULL, sdl->screen, &pos);
      break;
    case TREE:
      SDL_BlitSurface(tree, NULL, sdl->screen, &pos);
      break;
    case GRASS:
      SDL_BlitSurface(grass, NULL, sdl->screen, &pos);
      break;
    }
}

int		Map::goToLine(int line)
{
  int		n = 0;
  int		curline = 0;

  while (curline < line)
    {
      while (_map[n] && _map[n] != '\n')
	n++;
      n++;
      curline++;
    }
  return n;
}

void		Map::affMap(mySDL *sdl, int x, int y, int posx, int posy)
{
  SDL_Rect	pos2;
  int		n = 0;
  int		nbline = - (WINY / 2);
  int		nbcol = - (WINX / 2);
  int		curcol;
  int		curline = 0;

  pos2.x = posx;
  pos2.y = posy;
  while (nbline < y - (WINY / 2))
    {
      curcol = n;
      if ((y - ((WINY / 2) - nbline)) >= 0)
	{
	  while (_map[n] != '\n')
	    n++;
	  n++;
	}
      nbline++;
    }
  n = curcol;
  nbline--;
  while (nbcol < x - (WINX / 2))
    nbcol++;

      while (nbline + curline < 0)
  	{
  	  curline++;
  	  pos2.y += 16;
  	}

  n = goToLine(curline + nbline);
  if (_map[n] && _map[n] == '\n')
    n++;

  SDL_FillRect(sdl->screen, NULL, 0x000000);
  while (curline < (WINY + 2) && _map[n] != '\0')
    {
      n += nbcol;
      curcol = 0;
      if (nbcol < 0)
	while (curcol + nbcol < 0)
	  {
	    curcol++;
	    pos2.x += 16;
	  }
      while (curcol < (WINX + 2) && _map[n + curcol] && _map[n + curcol] != '\n')
	{
	  this->affCase(pos2.x, pos2.y, _map[n + curcol], sdl);
	  pos2.x += 16;
	  curcol++;
	}
      pos2.x = posx;
      pos2.y += 16;
      curline++;
      n = goToLine(curline + nbline);
      if (_map[n] && _map[n] == '\n')
      	n++;
    }
}

char	Map::getChar(int x, int y)
{
  int	line = 0;
  int	i = 0;
  int	n = 0;

  while (line < y)
    {
      while (_map[n] != '\n')
	n++;
      n++;
      line++;
    }
  while (i < x)
    i++;
  n += i;

  return (_map[n]);
}
