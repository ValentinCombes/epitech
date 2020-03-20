/*
** aff.c for my_irc in /home/combes_v//Proj/my_irc/aff
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Thu Apr 19 10:20:31 2012 valentin combes
** Last update Sun Apr 22 21:07:35 2012 valentin combes
*/

#include "libmy.h"
#include "aff.h"

void	aff_border(int width)
{

  my_printf("%C+", BOLD);
  width -= 2;
  while (width > 0)
    {
      if (width > 10)
	my_printf("%C%ms", BOLD, 10, "----------");
      else
	my_printf("%C%ms", BOLD, width, "----------");
      width -= 10;
    }
  my_printf("%C+\n", BOLD);
}

int	aff_line(t_aff *tmp, int width)
{
  int	len_msg;
  int	res;

  if (tmp)
    {
      res = 1;
      len_msg = my_strlen(tmp->name) + my_strlen(tmp->msg) + 5;
      my_printf("%C| %C%s%C: ", BOLD, RED, tmp->name, BLUE);
      my_printf("%ms", width - my_strlen(tmp->name) - 5, tmp->msg);
      my_printf("%C|\n", BOLD);
      if (len_msg > width)
	res = reaff_line(tmp, width, res, len_msg);
    }
  else
    {
      my_printf("%C| % |\n", BOLD, width - 2);
      res = 1;
    }
  return (res);
}

void	aff_list(t_aff *list)
{
  int	width;
  int	height;
  t_aff	*tmp;

  my_clear();
  width = tgetnum("co");
  height = tgetnum("li");
  if (width == -1 || height == -1)
    my_puterror("can't get size of term");
  tmp = get_first_msg(list, height, width);
  aff_border(width);
  height -= 3;
  while (height > 0)
    {
      if (tmp)
	{
	  height -= aff_line(tmp, width);
	  tmp = tmp->next;
	}
      else
	height -= aff_line(NULL, width);
    }
  aff_border(width);
}

t_aff	*aff(char *name, char *message, t_aff *list)
{
  t_aff	*new;
  t_aff	*tmp;

  if (name && message)
    {
      new = xmalloc(sizeof(*new));
      new->name = my_strcreat(name);
      new->msg = my_strcreat(message);
      new->prev = NULL;
      new->next = NULL;
      if (!list)
	list = new;
      else
	{
	  tmp = list;
	  while (tmp->next)
	    tmp = tmp->next;
	  tmp->next = new;
	  new->prev = tmp;
	}
    }
  aff_list(list);
  g_list = list;
  return (list);
}

void	my_free_list(t_aff *list)
{
  t_aff	*tmp;

  if (!list)
    return;
  tmp = list;
  while (tmp->next)
    {
      if (tmp->name)
	tmp->name = xfree(tmp->name);
      if (tmp->msg)
	tmp->msg = xfree(tmp->msg);
      tmp = tmp->next;
      if (tmp->prev)
	tmp->prev = xfree(tmp->prev);
    }
  if (tmp->name)
    tmp->name = xfree(tmp->name);
  if (tmp->msg)
    tmp->msg = xfree(tmp->msg);
  if (tmp)
    tmp = xfree(tmp);
}

