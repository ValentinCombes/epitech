#include "trainer.hpp"

Trainer::Trainer(std::string name, mySDL *sdl) : _name(name), x(0), y(0), sdlpoint(sdl)
{
  up1 = IMG_Load("textures/hero/up1.png");
  up2 = IMG_Load("textures/hero/up2.png");
  up3 = IMG_Load("textures/hero/up3.png");
  down1 = IMG_Load("textures/hero/down1.png");
  down2 = IMG_Load("textures/hero/down2.png");
  down3 = IMG_Load("textures/hero/down3.png");
  left1 = IMG_Load("textures/hero/left1.png");
  left2 = IMG_Load("textures/hero/left2.png");
  left3 = IMG_Load("textures/hero/left3.png");
  right1 = IMG_Load("textures/hero/right1.png");
  right2 = IMG_Load("textures/hero/right2.png");
  right3 = IMG_Load("textures/hero/right3.png");
  curframe = down1;
  x = WINX / 2 - 1;
  y = WINY / 2;
  pos.x = ((WINX - 2) * 16) / 2;
  pos.y = ((WINY - 2) * 16) / 2;
}

Trainer::~Trainer()
{
  SDL_FreeSurface(up1);
  SDL_FreeSurface(up2);
  SDL_FreeSurface(up3);
  SDL_FreeSurface(down1);
  SDL_FreeSurface(down2);
  SDL_FreeSurface(down3);
  SDL_FreeSurface(left1);
  SDL_FreeSurface(left2);
  SDL_FreeSurface(left3);
  SDL_FreeSurface(right1);
  SDL_FreeSurface(right2);
  SDL_FreeSurface(right3);
}

void	Trainer::useBike()
{
  this->isOnBike = !this->isOnBike;
}

void	Trainer::moveUp()
{
  if (y > 0 && map->getChar(x, y - 1) != 'w' && map->getChar(x, y - 1) != 't')
    {
      y--;
      curframe = up2;
      SDL_Delay(60);
      map->affMap(sdlpoint, x, y, 0, -16);
      SDL_BlitSurface(curframe, NULL, sdlpoint->screen, &pos);
      SDL_Flip(sdlpoint->screen);
      curframe = up3;
      SDL_Delay(60);
      map->affMap(sdlpoint, x, y, 0, -8);
      SDL_BlitSurface(curframe, NULL, sdlpoint->screen, &pos);
      SDL_Flip(sdlpoint->screen);
      curframe = up1;
      SDL_Delay(60);
      map->affMap(sdlpoint, x, y, 0, 0);
      SDL_BlitSurface(curframe, NULL, sdlpoint->screen, &pos);
      SDL_Flip(sdlpoint->screen);
    }
  else
    {
      curframe = up1;
      map->affMap(sdlpoint, x, y, 0, 0);
      SDL_BlitSurface(curframe, NULL, sdlpoint->screen, &pos);
      SDL_Flip(sdlpoint->screen);
    }
}

void	Trainer::moveDown()
{
  if (map->getChar(x, y + 1) != 'w' && map->getChar(x, y + 1) != 't')
    {
      y++;
      curframe = down2;
      SDL_Delay(60);
      map->affMap(sdlpoint, x, y, 0, 16);
      SDL_BlitSurface(curframe, NULL, sdlpoint->screen, &pos);
      SDL_Flip(sdlpoint->screen);
      curframe = down3;
      SDL_Delay(60);
      map->affMap(sdlpoint, x, y, 0, 8);
      SDL_BlitSurface(curframe, NULL, sdlpoint->screen, &pos);
      SDL_Flip(sdlpoint->screen);
      curframe = down1;
      SDL_Delay(60);
      map->affMap(sdlpoint, x, y, 0, 0);
      SDL_BlitSurface(curframe, NULL, sdlpoint->screen, &pos);
      SDL_Flip(sdlpoint->screen);
    }
  else
    {
      curframe = down1;
      map->affMap(sdlpoint, x, y, 0, 0);
      SDL_BlitSurface(curframe, NULL, sdlpoint->screen, &pos);
      SDL_Flip(sdlpoint->screen);
    }
}

void	Trainer::moveLeft()
{
  if (x > 0 && map->getChar(x - 1, y) != 'w' && map->getChar(x - 1, y) != 't')
    {
      x--;
      curframe = left2;
      SDL_Delay(60);
      map->affMap(sdlpoint, x, y, -16, 0);
      SDL_BlitSurface(curframe, NULL, sdlpoint->screen, &pos);
      SDL_Flip(sdlpoint->screen);
      curframe = left3;
      SDL_Delay(60);
      map->affMap(sdlpoint, x, y, -8, 0);
      SDL_BlitSurface(curframe, NULL, sdlpoint->screen, &pos);
      SDL_Flip(sdlpoint->screen);
      curframe = left1;
      SDL_Delay(60);
      map->affMap(sdlpoint, x, y, 0, 0);
      SDL_BlitSurface(curframe, NULL, sdlpoint->screen, &pos);
      SDL_Flip(sdlpoint->screen);
    }
  else
    {
      curframe = left1;
      map->affMap(sdlpoint, x, y, 0, 0);
      SDL_BlitSurface(curframe, NULL, sdlpoint->screen, &pos);
      SDL_Flip(sdlpoint->screen);
    }
}

void	Trainer::moveRight()
{
  if(map->getChar(x + 1, y) != 'w' && map->getChar(x + 1, y) != 't')
    {
      x++;
      curframe = right2;
      SDL_Delay(60);
      map->affMap(sdlpoint, x, y, 16, 0);
      SDL_BlitSurface(curframe, NULL, sdlpoint->screen, &pos);
      SDL_Flip(sdlpoint->screen);
      curframe = right3;
      SDL_Delay(60);
      map->affMap(sdlpoint, x, y, 8, 0);
      SDL_BlitSurface(curframe, NULL, sdlpoint->screen, &pos);
      SDL_Flip(sdlpoint->screen);
      curframe = right1;
      SDL_Delay(60);
      map->affMap(sdlpoint, x, y, 0, 0);
      SDL_BlitSurface(curframe, NULL, sdlpoint->screen, &pos);
      SDL_Flip(sdlpoint->screen);
    }
  else
    {
      curframe = right1;
      map->affMap(sdlpoint, x, y, 0, 0);
      SDL_BlitSurface(curframe, NULL, sdlpoint->screen, &pos);
      SDL_Flip(sdlpoint->screen);
    }
}

SDL_Rect	*Trainer::getPos()
{
  return &pos;
}

SDL_Surface	*Trainer::getCurFrame()
{
  return curframe;
}

void		Trainer::setMap(Map *_map)
{
  mappos.x = 0;
  mappos.y = 0;
  map = _map;
}

int		Trainer::getX()
{
  return x;
}

int		Trainer::getY()
{
  return y;
}
