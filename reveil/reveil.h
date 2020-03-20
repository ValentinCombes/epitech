#ifndef	__REVEIL_H__
#define	__REVEIL_H__

#include "libmy.h"
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <curses.h>
#include <term.h>
#include <signal.h>

#define WINX 120
#define WINY 90

typedef	struct		s_alarm {
  int			hour;
  int			min;
  char			*alarm;
  struct s_alarm	*prev;
  struct s_alarm	*next;
}			t_alarm;

typedef struct		s_aff {
  int			bpp;
  int			sizeline;
  int			endian;
  char			*data;
  void			*img;
  void			*mlx_ptr;
  void			*win_ptr;
}			t_aff;

/*	in main.c	*/
t_alarm	*get_alarm();
int	main();

#endif
