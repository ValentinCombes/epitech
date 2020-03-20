/*
** main.c for main in /home/baudy_m//Desktop/Projet/C
** 
** Made by marie baudy
** Login   <baudy_m@epitech.net>
** 
** Started on  Thu Oct 28 13:52:46 2010 marie baudy
** Last update Tue Nov  2 14:34:52 2010 marie baudy
*/

#include "my.h"

int	char_to_int(char *base, char c)
{
  int	index;

  index = 0;
  while (base[index] != c)
    index++;
  return (index);
}

char	*initialise_res_and_r(char *res, int **r, int size)
{
  res = malloc(size+1);
  res[size] = 0;
  *r = malloc(size * sizeof(**r));
  my_memset(*r, 0, size * sizeof(**r));
  return (res);
}

char	*finish(t_mul *ptr, char *res, int *r, int len_2)
{
  while (ptr->p1 < ptr->len_1 + len_2)
    {
      if (ptr->p2 || r[ptr->p1] || ptr->p1 == ptr->len_1 + len_2 - 1)
        res[ptr->p2++] = ptr->base[r[ptr->p1]];
      ptr->p1++;
    }
  return (res);
}

struct	s_mul *init_struct(t_mul *ptr, char *base, char *n1, char *n2)
{
  ptr = malloc(sizeof(t_mul) * 5);
  ptr->base = base;
  ptr->size_base = my_strlen(ptr->base);
  ptr->len_1 = my_strlen(n1);
  ptr->len_2 = my_strlen(n2);
  ptr->p1 = ptr->len_1 -1;
  return (ptr);
}

char	*inf_mult(char *nb1, char *nb2, char *base)
{
  char	*res;
  int	*r;
  t_mul	*ptr;

  ptr = init_struct(ptr, base, nb1, nb2);
  res = initialise_res_and_r(res, &r, ptr->len_1 + ptr->len_2);
  while (ptr->p1 >= 0)
    {
      ptr->p2 = ptr->len_2 -1;
      while (ptr->p2 >= 0)
	{
	  r[ptr->p1 + ptr->p2 + 1] += char_to_int(ptr->base, nb1[ptr->p1]) 
	    * char_to_int(ptr->base, nb2[ptr->p2]);
	  r[ptr->p1 + ptr->p2] += r[ptr->p1 + ptr->p2 + 1] / ptr->size_base;
	  r[ptr->p1 + ptr->p2 + 1] = r[ptr->p1 + ptr->p2 + 1] % ptr->size_base;
	  ptr->p2--;
	}
      ptr->p1--;
    }
  ptr->p1 = ptr->p2 = 0;
  res = finish(ptr, res, r, ptr->len_2);
  free(ptr);
  free(r);
  return (res);
}
