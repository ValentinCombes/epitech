/*
** syntaxe.c for syntax.c in /home/baudy_m//Desktop/Projet/C/Bistromatique
** 
** Made by marie baudy
** Login   <baudy_m@epitech.net>
** 
** Started on  Tue Nov  2 15:10:20 2010 marie baudy
** Last update Wed Nov  3 11:20:15 2010 marie baudy
*/

#include "my.h"

int	analyse(char *str, char *ops, char *base, int *level_paren)
{
  if (str[1] == ops[0])
    {
      if (find_pos(base, *str) != -1)
	return (1);
      (*level_paren)++;
    }
  if (str[1] == ops[1])
    {
      if (str[2])
	if (find_pos(base, str[2]) != -1)
	  return (1);
      (*level_paren)--;
    }
  if (*level_paren < 0)
    return (1);
  return (0);
}

int	syntax_error_paren(char *str, char *ops, char *base)
{
  int	level_paren;

  level_paren = 0;
  if (str[0] == ops[0])
    level_paren++;
  if (str[0] == ops[1])
    return (1);
  while (str[1])
    {
      if (analyse(str, ops, base, &level_paren) == 1)
	return (1);
      str++;
    }
  if (level_paren == 0)
    return (0);
  return (1);
}

int	syntax_error_character(char *str, char *base, char *ops)
{
  while (str[0])
    {
      if (find_pos(base, *str) == -1 && find_pos(ops, *str) == -1)
	return (1);
      str = str + 1;
    }
  return (0);
}

int	syntax_error_op(char *str, char *base, char *ops)
{
  return (0);
}

int	syntax_error(char *str, char *base, char *ops)
{
  if (syntax_error_character(str, base, ops) ||
      syntax_error_paren(str, ops, base))
    {
      my_putstr (SYNTAXE_ERROR_MSG);
      return (1);
    }
  return (0);
}
