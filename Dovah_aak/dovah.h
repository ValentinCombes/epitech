#ifndef	DOVAH_H__
# define	DOVAH_H__

# include	"libmy.h"
# include	<SDL/SDL.h>
# include	<SDL/SDL_image.h>
# include	<SDL/SDL_ttf.h>

typedef	struct		s_sign
{
  SDL_Surface		*sprite;
  char			*alph;
  struct s_sign		*prev;
  struct s_sign		*next;
}			t_sign;

typedef	struct		s_aff
{
  t_sign		*sign;
  SDL_Surface		*screen;
  TTF_Font		*police;
  SDL_Event		event;
  SDL_Rect		*positions;
  SDL_Color		black;
  SDL_Color		white;
}			t_aff;

#endif
