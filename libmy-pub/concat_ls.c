/*
** concat_ls.c for libmy in /home/combes_v//Projets_persos/svn/valentin/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Sat Apr  7 19:06:05 2012 valentin combes
** Last update Sat Oct 27 13:48:17 2012 
*/

#include	"libmy.h"

char	*my_nbr_to_fullstr(int nb)
{
  char	*str;
  int	puiss;
  char	sign;
  int	n = 0;

  puiss = 1;
  if (nb < 0) {
    sign = '-';
    nb = -nb;
  }
  while ((1000000 / puiss) > 10) {
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
  return (str);
}

char	*my_nbr_to_str(int nb)
{
  char	*str;
  int	puiss;
  char	sign;
  int	n = 0;

  puiss = 1;
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
  return (str);
}

char	*addlsline(t_ls *tmp, char *prec, int mls, int mlnl)
{
  char	*str;
  char	*str2;
  char	*res;

  str = my_nbr_to_nstr(tmp->nlink, mlnl);
  str2 = my_nbr_to_nstr(tmp->size, mls);
  res = add_to_line(prec, tmp->rights);
  res = add_to_line(res, str);
  res = add_to_line(res, tmp->uname);
  res = add_to_line(res, tmp->gname);
  res = add_to_line(res, str2);
  res = add_to_line(res, tmp->time);
  res = add_to_line(res, tmp->name);
  str = xfree(str);
  str2 = xfree(str2);
  str = my_strcat(res, "\n");
  res = xfree(res);
  res = str;
  return (res);
}

char	*concatls(t_ls *list, char *ls_flags)
{
  t_ls	*tmp;
  t_ls	*tmp2;
  char	*res;
  int	max_len_size;
  int	max_len_nlink;

  (void)ls_flags;
  tmp = list;
  res = xmalloc(1 * sizeof(*res));
  res[0] = '\0';
  max_len_size = get_max_len_size(list);
  max_len_nlink = get_max_len_nlink(list);
  while (tmp)
    {
      res = addlsline(tmp, res, max_len_size, max_len_nlink);
      tmp2 = tmp;
      tmp = tmp->next;
      free_t_ls(tmp2);
    }
  return (res);
}

