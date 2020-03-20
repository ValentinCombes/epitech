/*
** gestion_op.c for eval_expr in /home/barre-_t//hl/piscine/eval_expr
** 
** Made by thibault barre-villeneuve
** Login   <barre-_t@epitech.net>
** 
** Started on  Sun Oct 24 16:12:08 2010 thibault barre-villeneuve
** Last update Tue Feb  5 05:03:31 2013 
*/

#include "my.h"

int	find_pos(char *base, char c)
{
  int	index;
  
  index = 0;
  while (base[index] != '\0')
    {
      if (base[index] == c)
	return (index);
      index++;
    }
  return (-1);
}

int	str_contain_operator(char *str, char *ops)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] == ops[2] || (str[i] == ops[3] && i != 0) ||
	  str[i] == ops[4] || str[i] == ops[5] || str[i] == ops[6])
	return (0);
      i = i + 1;
    }
  return (1);
}

int	c_contain_operator(char c, int ordre, int counter, char *ops)
{
  if (((c == ops[2] || (c == ops[3] && counter != 0)) && ordre == 1)
      || ((c == ops[5] || c == ops[6] || c == ops[4]) && ordre == 0))
    return (0);
  if ((c == ops[2] || c == ops[3] || c == ops[5] || c == ops[4]) &&
      counter == -1)
    return (0);
  return (1);
}

char	*my_do_op(char *str, int *counter, char *base, char *ops)
{
  if (str[*counter] == ops[4] && find_pos(base, str[*counter - 1]) != -1)
    {
      str = my_mult(str, *counter, base, ops);
      *counter = -1;
    }
  if (str[*counter] == ops[5] && find_pos(base, str[*counter - 1]) != -1)
    {
      str = my_div(str, *counter, base, ops);
      *counter = -1;
    }
  if (str[*counter] == ops[6] && find_pos(base, str[*counter - 1]) != -1)
    {
      str = my_modulo(str, *counter, base, ops);
      *counter = -1;
    }
  if (str[*counter] == ops[3] && find_pos(base, str[*counter - 1]) != -1)
    str = my_sous(str, *counter, base, ops);
  if (str[*counter] == ops[2] && find_pos(base, str[*counter - 1]) != -1)
    str = my_add(str, *counter, base, ops);
  if (*counter != -1)
    *counter = 0;
  return (str);
}
