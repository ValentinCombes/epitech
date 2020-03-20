/*
** aff.h for my_irc in /home/combes_v//Proj/my_irc/aff
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Thu Apr 19 10:20:57 2012 valentin combes
** Last update Fri Apr 20 18:55:01 2012 valentin combes
*/

#ifndef __AFF_H__
# define __AFF_H__

# include <term.h>
# include <termios.h>
# include <signal.h>

# define BUF_SIZE	5000

typedef	struct	s_aff
{
  char		*name;
  char		*msg;
  struct s_aff	*prev;
  struct s_aff	*next;
}		t_aff;

t_aff	*g_list;

/*	in aff_buf.c	*/
void	put_cursor();
void	non_canon_mode();
void	aff_buf(char *buf, int rc, int wc);

/*	in aff_utils.c	*/
int	count_nb_line(t_aff *tmp, int width, int res, int len_msg);
t_aff	*get_first_msg(t_aff *list, int height, int width);
int	reaff_line(t_aff *tmp, int width, int res, int len_msg);
void	my_clear();
void	resize(int sig);

/*	in aff.c	*/
void	aff_border(int width);
int	aff_line(t_aff *tmp, int width);
void	aff_list(t_aff *list);
t_aff	*aff(char *name, char *message, t_aff *list);
void	my_free_list(t_aff *list);

#endif
