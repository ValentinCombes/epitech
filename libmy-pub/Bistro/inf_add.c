/*
** inf_add.c for inf_add in /home/baudy_m//Projet/C/Bistromatique
** 
** Made by marie baudy
** Login   <baudy_m@epitech.net>
** 
** Started on  Tue Oct 26 16:28:52 2010 marie baudy
** Last update Tue Nov  2 11:53:29 2010 thibault barre-villeneuve
*/

#include "my.h"

int	define_pos2(int cnt, char *base, char *nb2)
{
  int	pos2;

  if (cnt < my_strlen(nb2))
    pos2 = find_pos(base, nb2[cnt]);
  else
    pos2 = 0;
  return (pos2);
}

void	define_pos_add_and_ret(int *pos_add, char *base, int *ret)
{
  if (*pos_add >= my_strlen(base))
    {
      *pos_add = *pos_add - my_strlen(base);
      *ret = 1;
    }
  else
    *ret = 0;
}

void	swap_char(char **res, char **nb1, char **nb2)
{
  if (my_strlen(*nb2) > my_strlen(*nb1))
    {
      *res = *nb1;
      *nb1 = *nb2;
      *nb2 = *res;
    }
}

char	*inf_add(char *nb1, char *nb2, char *base)
{
  char	*res;
  int	pos_add;
  int	ret;
  int	cnt;

  nb1 = my_revstr(nb1);
  nb2 = my_revstr(nb2);
  swap_char(&res, &nb1, &nb2);
  res = (char *) my_malloc((my_strlen(nb2) + 2) * sizeof(*res));
  ret = cnt = 0;
  while (nb1[cnt] != '\0')
    {
      pos_add = find_pos(base, nb1[cnt]) +
	define_pos2(cnt, base, nb2) + ret;
      define_pos_add_and_ret(&pos_add, base, &ret);
      res[cnt] = base[pos_add];
      cnt++;
    }
  if (ret)
    {
      res[cnt] = base[ret];
      cnt ++;
    }
  res[cnt] = '\0';
  return (my_revstr(res));
}
