/*
** eval_expr.c for eval_expr in /home/baudy_m//Projet/C/Bistromatique
** 
** Made by marie baudy
** Login   <baudy_m@epitech.net>
** 
** Started on  Tue Oct 26 11:51:17 2010 marie baudy
** Last update Tue Nov  2 15:17:15 2010 marie baudy
*/

#include "my.h"

char	*eval_expr(char *base, char *ops, char *str, unsigned int size)
{
  char	*result;
  
  if (!syntax_error(str, base, ops) && str_contain_operator(str, ops) == 0)
    {
      result = eval_paren(str, ops, base);
      my_putstr(result);
      free (result);
    }
  else 
    if (str_contain_operator(str, ops))
      my_putstr(str);
  return ("\n");
}

char	*my_eval_expr(char *str, char *base, char *ops)
{
  int	counter;

  while (str_contain_operator(str, ops) == 0)
    {
      counter = 1;
      while (str[counter] &&
	     c_contain_operator(str[counter], 0, counter, ops) == 1)
	counter = counter + 1;
      str = my_do_op(str, &counter, base, ops);
      if ((str[counter] == '\0' && counter != -1) || counter == 0)
	counter = 1;
      while (str[counter] && counter != -1)
	{
	  if (c_contain_operator(str[counter], 1, counter, ops) == 0 &&
	      find_pos(base, str[counter - 1]) != -1)
	    {
	      str = my_do_op(str, &counter, base, ops);
	      counter = 0;
	    }
	  counter = counter + 1;
	}
    }
  return (str);
}
