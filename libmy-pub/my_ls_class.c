/*
** my_ls_class.c for libmy in /home/combes_v//Projets_persos/svn/valentin/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Sat Apr  7 19:06:05 2012 valentin combes
** Last update Sat Apr  7 23:02:01 2012 valentin combes
*/

#include	"libmy.h"

char	*complete_nb(char *str, int size)
{
  char	*tmp;

  while (my_strlen(str) < size)
    {
      tmp = my_strcat(" ", str);
      str = xfree(str);
      str = tmp;
    }
  return (str);
}

char	*my_nbr_to_nstr(int nb, int size)
{
  char	*str;
  int	puiss = 1;
  char	sign;
  int	n = 0;

  if (nb < 0) {
    sign = '-';
    nb = -nb;
  }
  while ((nb / puiss) >= 10) {
    puiss = puiss * 10;
    n++;
  }
  str = xmalloc((n + 2) * sizeof(*str));
  n = 0;
  if (sign == '-')
    str[n++] = sign;
  while (puiss >= 1) {
    str[n++] = (nb / puiss) + '0';
    nb = nb % puiss;
    puiss = puiss / 10;
  }
  str[n] = '\0';
  str = complete_nb(str, size);
  return (str);
}

int	my_lscmp(char *s1, char *s2)
{
  int	n;
  int	diff;

  n = 0;
  diff = get_ls_char_val(s1[n]) - get_ls_char_val(s2[n]);
  while (s1[n] != '\0' && diff == 0)
    {
      diff = get_ls_char_val(s1[n]) - get_ls_char_val(s2[n]);
      n++;
    }
  if (s1[n] == '\0' && s2[n] != '\0')
    {
      diff = get_ls_char_val(s1[n]) - get_ls_char_val(s2[n]);
      n++;
    }
  return (diff);
}

t_ls	*file_class_comp(t_ls **this)
{
  t_ls	*tmp;
  t_ls	*tmp2;

  tmp = *this;
  tmp2 = *this;
  while (tmp)
    {
      if (my_lscmp(tmp2->name, tmp->name) > 0)
	tmp2 = tmp;
      tmp = tmp->next;
    }
  if (tmp2 != *this)
    {
      if (tmp2->prev)
	tmp2->prev->next = tmp2->next;
      if (tmp2->next)
	tmp2->next->prev = tmp2->prev;
    }
  else
    {
      *this = tmp2->next;
      if (*this)
	(*this)->prev = NULL;
    }
  return (tmp2);
}

t_ls	*file_class(t_ls *this)
{
  t_ls	*tmp2;
  t_ls	*tmp3;
  t_ls	*list;

  list = NULL;
  while (this)
    {
      tmp2 = file_class_comp(&this);
      if (list)
	{
	  tmp3->next = tmp2;
	  tmp2->next = NULL;
	  tmp2->prev = tmp3;
	  tmp3 = tmp3->next;
	}
      else
	{
	  list = tmp2;
	  tmp2->prev = NULL;
	  tmp2->next = NULL;
	  tmp3 = list;
	}
    }
  return (list);
}

