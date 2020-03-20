/*
** analyse_string.c for analyse_string in /home/baudy_m//Desktop/Projet/C/Bistromatique
** 
** Made by marie baudy
** Login   <baudy_m@epitech.net>
** 
** Started on  Tue Nov  2 15:58:37 2010 marie baudy
** Last update Tue Nov  2 16:03:49 2010 marie baudy
*/

#include "my.h"

char	*epur_nbr_end(char *str, t_limits limite, int pos_op, char *ops)
{
  char	*result;
  int	counter;

  result = malloc(limite.right - pos_op);
  if (result == 0)
    {
      my_putstr("Error with malloc\n");
      return (0);
    }
  counter = 1;
  while (counter + pos_op < limite.right)
    {
      result[counter - 1] = str[pos_op + counter];
      counter = counter + 1;
    }
  result[counter - 1] = '\0';
  my_abs(&result, 0, ops);
  return (result);
}

char	*remove_leading_zero(char **str, char *base, char *ops)
{
  int	i;
  int	signe;
  char	*temp;

  temp = *str;
  i = 0;
  signe = 0;
  if (temp[i] == ops[3])
    {
      signe = 1;
      i++;
    }
  while (temp[i] && temp[i] == base[0])
    i++;
  if (find_pos(base, temp[i]) == -1)
    i--;
  temp = my_remove(temp, i, my_strlen(temp), ops);
  if (signe)
    my_abs(&temp, -1, ops);
  *str = temp;
  return (temp);
}

t_limits	pos_number(char *str, int pos, char *base, char *ops)
{
  t_limits	result;

  result.left = pos - 1;
  result.right = pos + 1;
  while (find_pos(base, str[result.left]) != -1 && result.left > 0)
    result.left -= 1;
  while ((find_pos(ops, str[result.left]) == 2 ||
	  find_pos(ops, str[result.left]) == 3) &&
	 result.left > 0)
    result.left -= 1;
  if (find_pos(base, str[result.left]) != -1 &&
      result.left + 1 < pos &&
      (find_pos(ops, str[result.left + 1]) == 2 ||
       find_pos(ops, str[result.left + 1]) == 3))
    result.left += 2;
  while ((find_pos(ops, str[result.right]) == 2 ||
	  find_pos(ops, str[result.right]) == 3) &&
	 str[result.right])
    result.right += 1;
  while (find_pos(base, str[result.right]) != -1 &&
	 result.right < my_strlen(str))
    result.right += 1;
  return (result);
}

int	is_bigger(char *nb1, char *nb2, char *base)
{
  if (my_strlen(nb1) > my_strlen(nb2))
    return (1);
  if (my_strlen(nb1) < my_strlen(nb2))
    return (0);
  while (*nb1)
    {
      if (find_pos(base, *nb1) > find_pos(base, *nb2))
	return (1);
      if (find_pos(base, *nb1) < find_pos(base, *nb2))
	return (0);
      nb1++;
      nb2++;
    }
  return (1);
}

char	*inf_sous_order(char *nb1, char *nb2, char *base, char *ops)
{
  char	*result;

  if (is_bigger(nb1, nb2, base))
    result = (char *) inf_sous(nb1, nb2, base);
  else
    {
      result = (char *) inf_sous(nb2, nb1, base);
      my_abs(&result, -1, ops);
    }
  return (result);
}
