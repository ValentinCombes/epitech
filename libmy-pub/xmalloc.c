/*
** xmalloc.c for libmy in /home/valentin/Projets_persos/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Tue Feb 22 11:14:04 2011 valentin combes
** Last update Fri Mar  2 22:22:09 2012 valentin combes
*/

#include	"libmy.h"

void	*xmalloc(size_t n)
{
  void	*p;

  p = malloc(n);
  if (p == NULL)
    my_puterror("erreur de malloc.");
  return (p);
}

void	*xfree(void *p)
{
  if (p != NULL)
    free(p);
  else
    my_putwarn("you're trying to free some free space.\n");
  return (NULL);
}

void	*my_freetab(void **tableau)
{
  int	n;

  n = 0;
  if (tableau == NULL)
    {
      my_putwarn("you're trying to free some free space.\n");
      return (NULL);
    }
  while (tableau[n])
    {
      tableau[n] = xfree(tableau[n]);
      n++;
    }
  return (tableau = xfree(tableau));
}

void	my_swap(int *a, int *b)
{
  int	tmp;

  tmp = *a;
  *a = *b;
  *b = tmp;
}

int	my_tablen(char **tableau)
{
  int	y;

  y = 0;
  while (tableau[y])
    y++;
  return (y);
}
