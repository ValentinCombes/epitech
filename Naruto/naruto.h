#ifndef	__NARUTO_H__
#define	__NARUTO_H__

#define _XOPEN_SOURCE 500

#include "libmy.h"
#include <time.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>

#define GRID 1
#define TREE 2

typedef struct		s_perso
{
  int			nb;
  char			*name;
  int			allowed;
  struct s_perso	*prev;
  struct s_perso	*next;
}			t_perso;

typedef struct		s_user
{
  char			*name;
  int			id;
  int			lastused;
  int			win;
  int			lose;
  int			matchwin;
  int			matchlose;
  int			score;
  t_perso		*pers;
  struct s_user		*prev;
  struct s_user		*next;
}			t_user;

typedef struct		s_match
{
  t_user		*player1;
  t_user		*player2;
  t_perso		*pers1;
  t_perso		*pers2;
  int			round1;
  int			round2;
  struct s_match	*prev;
  struct s_match	*next;  
}			t_match;

typedef struct		s_poll
{
  int			nb;
  t_user		*players;
  t_match		*matchs;
  struct s_poll		*prev;
  struct s_poll		*next;
}			t_poll;

typedef struct		s_tournoi
{
  char			*name;
  int			team_max;
  int			fd;
  int			rounds;
  int			type;
  t_user		*player;
  t_match		*matchs;
  t_perso		*pers;
  t_poll		*poll;
  struct tm		*debut;
  struct tm		*fin;
}			t_tournoi;

typedef struct		s_resize
{
  int			team_max;
  t_user		*user;
  t_perso		*pers;
  int			end;
}			t_resize;

t_resize	resize;

/*	functions	*/

void		my_clear();
int		ouverture(char *str, char *prompt, t_tournoi *tournoi);
void		my_help();
int		add_player(char *str, t_tournoi *tournoi);
void		aff_border();
void		aff_ligne(t_perso *pers, t_perso *select, int posx, int posy, int line);
t_perso		*chose_perso(t_perso *pers, int posx, int posy, t_perso *select);
void		aff_perso(int team_max, t_perso *pers, t_user *user);
void		set_team(char *str, t_tournoi *tournoi);
void		allow(char *str, t_tournoi *tournoi);
void		teamsize(char *str, t_tournoi *tournoi);
void		show(char *str, t_tournoi *tournoi);
void		remove_player(char *str, t_tournoi *tournoi);
t_perso		*chose_perso_for_match(int posy, t_perso *pers);
t_perso		*select_perso_for_match(t_user *player, int size);
t_match		*add_match(t_user *player1, t_user *player2, t_tournoi *tournoi);
void		start(char *str, t_tournoi *tournoi);
void		aff_end(t_tournoi *tournoi);
void		end(t_tournoi *tournoi);
void		export(char *str, t_tournoi *tournoi);
void		load(char *str, t_tournoi *tournoi);
int		my_cmdanalyse(char *str, t_tournoi *tournoi);
t_perso		*add_perso(char *name, int allowed);
void		remplis_perso(t_tournoi *tournoi, int fd_perso);
void		free_perso(t_tournoi *tournoi);
void		look_for_args(int ac, char **av);
void		open_tournoi(int ac, char **av);
int		main(int ac, char **av);

#endif
