/*
** my_op_particular.c for my_op_particular in /home/baudy_m//Desktop/Projet/C/Bistromatique
** 
** Made by marie baudy
** Login   <baudy_m@epitech.net>
** 
** Started on  Tue Nov  2 15:27:27 2010 marie baudy
** Last update Tue Nov  2 15:35:24 2010 marie baudy
*/

#include "my.h"

char	*my_add_particular(char *nb1, char *nb2, char *base, char *ops)
{
  char	*result;

  if (*nb1 == ops[3] && *nb2 == ops[3])
    {
      my_abs(&nb1, 1, ops);
      my_abs(&nb2, 1, ops);
      result = (char *) inf_add(nb1, nb2, base);
      my_abs(&result, -1, ops);
    }
  else if (*nb1 == ops[3] && *nb2 != ops[3])
    {
      my_abs(&nb1, 1, ops);
      result = (char *) my_sous_particular(nb2, nb1, base, ops);
    }
  else if (*nb1 != ops[3] && *nb2 == ops[3])
    {
      my_abs(&nb2, 1, ops);
      result = (char *) my_sous_particular(nb1, nb2, base, ops);
    }
  else
    result = (char *) inf_add(nb1, nb2, base);
  return (remove_leading_zero(&result, base, ops));
}

char	*my_sous_particular(char *nb1, char *nb2, char *base, char *ops)
{
  char	*result;

  if (*nb1 == ops[3] && *nb2 == ops[3])
    {
      my_abs(&nb1, 1, ops);
      my_abs(&nb2, 1, ops);
      result = (char *) my_sous_particular(nb2, nb1, base, ops);
    }
  else if (*nb1 == ops[3] && *nb2 != ops[3])
    {
      my_abs(&nb1, 1, ops);
      result = (char *) inf_add(nb1, nb2, base);
      my_abs(&result, -1, ops);
    }
  else if (*nb1 != ops[3] && *nb2 == ops[3])
    {
      my_abs(&nb2);
      result = (char *) inf_add(nb1, nb2, base);
    }
  else
    result = inf_sous_order(nb1, nb2, base, ops);
  return (remove_leading_zero(&result, base, ops));
}

char	*my_mult_particular(char *str1, char *str2, char *base, char *ops)
{
  char	*result;

  if (*str1 != ops[3] && *str2 != ops[3])
    {
      return ((char *) inf_mult(str1, str2, base));
    }
  if (*str1 == ops[3] && *str2 == ops[3])
    {
      my_abs(&str1, 1, ops);
      my_abs(&str2, 1, ops);
      return ((char *) inf_mult(str1, str2, base));
    }
  if (*str1 == ops[3])
    my_abs(&str1, 1, ops);
  else
    my_abs(&str2, 1, ops);
  result = (char *) inf_mult(str1, str2, base);
  my_abs(&result, -1, ops);
  return (result);
}

char	*my_div_particular(char *str1, char *str2, char *base, char *ops)
{
  char	*result;

  if (*str2 == '0')
    {
      my_putstr("Division par ");
      my_putchar(base[0]);
      my_putchar('\n');
      exit(1);
    }
  if (*str1 != ops[3] && *str2 != ops[3])
    return ((char *) inf_div(str1, str2, base));
  if (*str1 == ops[3] && *str2 == ops[3])
    {
      my_abs(&str1, 1, ops);
      my_abs(&str2, 1, ops);
      return ((char *) inf_div(str1, str2, base));
    }
  if (*str1 == ops[3])
    my_abs(&str1, 1, ops);
  else
    my_abs(&str2, 1, ops);
  result = (char *) inf_div(str1, str2, base);
  my_abs(&result, -1, ops);
  return (result);
}
