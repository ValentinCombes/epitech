/*
** inf_div.c for bistro in /home/combes_v//Bistro
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Fri Oct 29 17:24:16 2010 valentin combes
** Last update Wed Nov  3 23:01:23 2010 marie baudy
*/

#include "my.h"

char	*calc_one(t_div *ptr, char a, char *n, char *resultat)
{
  if (my_strdivcmp(ptr->tmp, ptr->nb2) < 0 
      && is_bigger(ptr->tmp, ptr->nb2, ptr->base) == 0)
    {
      resultat[ptr->i] = ptr->base[*n];
      ptr->nb1 = (char *) my_strdivcpy2(ptr->nb1, ptr->tmp);
      ptr->i++;
      ptr->tmp = (char *) my_strdivcpy(ptr->nb1, my_strlen(ptr->nb2), 
				       ptr->i, a);
      (*n) = 0;
    }
  return (resultat);
}

char	*calc_two(t_div *ptr, char a, char *resultat, char n)
{
  while (my_strdivcmp(ptr->tmp, ptr->nb2) < 0
	 && ptr->nb1[ptr->i + my_strlen(ptr->nb2) - 1] != '\0')
    {
      ptr->nb1 = (char *) my_strdivcpy2(ptr->nb1, ptr->tmp);
      resultat[ptr->i] = ptr->base[n];
      ptr->i++;
      ptr->tmp = (char *) my_strdivcpy(ptr->nb1, my_strlen(ptr->nb2), 
				       ptr->i, a);
    }
  return (resultat);
}

struct s_div	*init_struct_div(char *st1, char *st2, char *base, t_div *ptr)
{
  ptr = malloc(sizeof(t_div) * 6);
  ptr->nb1 = st1;
  ptr->nb2 = st2;
  ptr->base = base;
  return (ptr);
}

char	*inf_div(char *st1, char *st2, char *base)
{
  t_div	*ptr;
  char	n;
  char	*resultat;
  char	a;

  ptr = init_struct_div(st1, st2, base, ptr);
  a = n = ptr->i = 0;
  resultat = (char *) malloc_resultat(resultat, ptr->nb1, ptr->nb2);
  ptr->tmp = (char *) my_strdivcpy(ptr->nb1, my_strlen(ptr->nb2), ptr->i, a);
  while (is_bigger(ptr->tmp, ptr->nb2, ptr->base) == 0)
    {
      a = a + 1;
      ptr->tmp = (char *) my_strdivcpy(ptr->nb1, 
				       my_strlen(ptr->nb2), ptr->i, a);
    }
  while (my_strdivcmp(ptr->tmp, ptr->nb2) >= 0 
	 && ptr->nb1[ptr->i + my_strlen(ptr->nb2) - 1] != '\0' 
	 || is_bigger(ptr->tmp, ptr->nb2, ptr->base) > 0)
    {
      n = n + 1;
      ptr->tmp = (char *) inf_sous(ptr->tmp, ptr->nb2, ptr->base);
      resultat = calc_one(ptr, a, &n, resultat);
      resultat = calc_two(ptr, a, resultat, n);
    }
  return (resultat);
}
