/*
** naruto.h for Naruto2 in /home/valentin/Projets_persos/Naruto2
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Thu Apr 19 10:20:31 2012 valentin combes
** Last update Sun Apr 22 21:07:35 2012 valentin combes
*/

#ifndef	__NARUTO_H__
#define	__NARUTO_H__

#define _XOPEN_SOURCE 500

#include "libmy.h"
#include <time.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

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
  int			save;
  int			teamsize;
  int			fd;
  int			rounds;
  int			type;
  t_user		*player;
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

/*		in main.c		*/
void		look_for_args(int ac, char **av, t_tournoi *tournoi);
int		open_game(char *str, t_tournoi *tournoi);
int		main(int ac, char **av);

/*		in character.c		*/
t_perso		*add_character(char *name, int allowed);
void		fill_character(t_tournoi *tournoi, int fd_perso);
void		free_character(t_tournoi *tournoi);
void		show_character(t_tournoi * tournoi);

/*		in loop.c		*/
void		loop(t_tournoi *tournoi);

/*		in fill_game.c		*/
void		fill_game(char *s, t_tournoi *tournoi);
int		gamecmp(char *str, t_tournoi *tournoi);

/*		in init.c		*/
char	  	*set_game(char *str, t_tournoi *tournoi);
void		init_teamsize(t_tournoi *tournoi);
void		init_rounds(t_tournoi *tournoi);
int		init_game(t_tournoi *tournoi);
void		init(int ac, char **av, t_tournoi *tournoi);

#endif
