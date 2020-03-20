/*
** parenteses.c for eval_expr in /home/barre-_t//hl/piscine/eval_expr
** 
** Made by thibault barre-villeneuve
** Login   <barre-_t@epitech.net>
** 
** Started on  Sun Oct 24 16:10:50 2010 thibault barre-villeneuve
** Last update Tue Nov  2 16:16:10 2010 marie baudy
*/

#include "my.h"

int	init_max_level_paren(int *a, int *b, int *c, int *d)
{
  *a = 0;
  *b = 0;
  *c = 0;
  *d = 0;
  return (0);
}

int	max_level_paren(char *str, char *ops)
{
  int	topLevel;
  int	level;
  int	result;
  int	counter;

  init_max_level_paren(&level, &result, &topLevel, &counter);
  while (str[counter])
    {
      if (str[counter] == ops[0])
	{
	  level = level + 1;
	  if (level > topLevel)
	    {
	      topLevel = level;
	      result = counter;
	    }
	}
      if (str[counter] == ops[1])
	level = level - 1;
      counter = counter + 1;
    }
  return (result);
}

char		*eval_paren(char *str, char *ops, char *base)
{
  t_limits	limite;
  int		nb_paren;
  char		*temp;

  limite.left = max_level_paren(str, ops);
  limite.right = limite.left + 1;
  while (str[limite.right] != ops[1] && str[limite.right])
    limite.right = limite.right + 1;
  while (str_contain_operator(str, ops) == 0)
    {
      limite.left = max_level_paren(str, ops);
      limite.right = limite.left + 2;
      while (str[limite.right] != ops[1] && str[limite.right])
	limite.right = limite.right +1;
      temp = my_remove(str, limite.left, limite.right, ops);
      str = my_replace(str, my_eval_expr(my_remove(str, limite.left,
						   limite.right, ops),
					 base, ops), limite, ops);
    }
  return (str);
}
