/*
** aff_utils.c for my_irc in /home/combes_v//Proj/my_irc/aff
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Thu Apr 19 17:28:18 2012 valentin combes
** Last update Sun Apr 22 19:40:23 2012 valentin combes
*/

#include "libmy.h"
#include "aff.h"

int	count_nb_line(t_aff *tmp, int width, int res, int len_msg)
{
  char	*s;
  char	*tmps;

  s = my_strcreat(tmp->msg);
  while (len_msg > 0)
    {
      len_msg = my_strlen(tmp->name) + my_strlen(s) + 5;
      tmps = my_strcreat(s + width - 5 - my_strlen(tmp->name));
      s = xfree(s);
      s = tmps;
      if (len_msg < width)
	s = xfree(s);
      len_msg = my_strlen(s) + (my_strlen(tmp->name) + 5) - width;
      res++;
    }
  return (res);
}

t_aff	*get_first_msg(t_aff *list, int height, int width)
{
  t_aff	*tmp;
  int	len_msg;

  tmp = list;
  while (tmp->next)
    tmp = tmp->next;
  height -= 4;
  while (height > 0 && tmp->prev)
    {
      height--;
      tmp = tmp->prev;
      len_msg = my_strlen(tmp->name) + my_strlen(tmp->msg) + 5;
      if (len_msg > width)
	height -= (count_nb_line(tmp, width, 1, len_msg) - 1);
    }
  while (height < 0 && tmp->next)
    {
      height++;
      tmp = tmp->next;
      len_msg = my_strlen(tmp->name) + my_strlen(tmp->msg) + 5;
      if (len_msg > width)
	height += (count_nb_line(tmp, width, 1, len_msg) - 1);
    }
  return (tmp);
}

int	reaff_line(t_aff *tmp, int width, int res, int len_msg)
{
  char	*s;
  char	*tmps;

  s = my_strcreat(tmp->msg);
  while (len_msg > 0)
    {
      len_msg = my_strlen(tmp->name) + my_strlen(s) + 5;
      tmps = my_strcreat(s + width - 5 - my_strlen(tmp->name));
      s = xfree(s);
      s = tmps;
      my_printf("%C|% ", BOLD, my_strlen(tmp->name) + 4);
      my_printf("%ms", width - my_strlen(tmp->name) - 5, s);
      my_printf("%C|\n", BOLD);
      if (len_msg < width)
	s = xfree(s);
      len_msg = my_strlen(s) + (my_strlen(tmp->name) + 5) - width;
      res++;
    }
  return (res);
}

/* void	my_clear() */
/* { */
/*   char  *src; */
/*   char  *str; */

/*   src = xmalloc(4); */
/*   tgetent(NULL, "xterm"); */
/*   str = tgetstr("cl", &src); */
/*   my_printf(str); */
/*   str = xfree(str); */
/* } */

void	resize(int sig)
{
  (void)sig;
  aff_list(g_list);
  return;
}

