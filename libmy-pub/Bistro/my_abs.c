/*
** my_abs.c for bistromathique in /home/barre-_t//afs/public/bistro
** 
** Made by thibault barre-villeneuve
** Login   <barre-_t@epitech.net>
** 
** Started on  Sat Oct 30 10:31:18 2010 thibault barre-villeneuve
** Last update Tue Nov  2 15:22:41 2010 marie baudy
*/

#include "my.h"

void	add_sign(char **str, char sign)
{
  char	*result;
  char	*temp;
  int	counter;
  
  counter = 0;
  temp = *str;
  result = malloc(my_strlen(temp) + 1);
  result[0] = sign;
  while (temp[counter])
    {
      result[counter + 1] = temp[counter];
      counter++;
    }
  result[counter + 1] = '\0';
  free (*str);
  *str = result;
}

void		my_abs(char **str, int sens, char *ops)
{
  char		*result;
  t_limits	limite;
  int		signe;
  
  result = *str;
  signe = 1;
  limite.left = limite.right = 0;
  while (result[limite.right] &&
	 (find_pos(ops, result[limite.right]) == 2 ||
	  find_pos(ops, result[limite.right]) == 3))
    {
      if (find_pos(ops, result[limite.right]) == 3)
	signe *= -1;
      limite.right = limite.right + 1;
    }
  result = my_remove(result, limite.right, my_strlen(result), ops);
  if ((signe == -1 && sens == 0) || sens < 0)
      add_sign(&result, ops[3]);
  *str = result;
}
