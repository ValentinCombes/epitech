/*
** str.c for eval_expr in /home/barre-_t//hl/piscine/eval_expr
** 
** Made by thibault barre-villeneuve
** Login   <barre-_t@epitech.net>
** 
** Started on  Sun Oct 24 16:13:28 2010 thibault barre-villeneuve
** Last update Tue Nov  2 16:23:37 2010 marie baudy
*/

#include "my.h"

int	replace_borne(char *str1, t_limits *limites, char *ops)
{
  int	left;
  int	right;

  left = limites->left;
  right = limites->right;
  if (str1[left] == ops[2] || str1[left] == ops[4] ||
      (str1[left] == ops[3] && left != 0) ||
      str1[left] == ops[5] || str1[left] == ops[6] &&
      left > 0)
    left = left + 1;
  if (str1[right] == ops[1])
    right++;  
  limites->left = left;
  limites->right = right;
  return (0);
}

int	find_size_replace(char *str1, char *str2, int left, int right)
{
  int	result;

  result = my_strlen(str1) - (right - left) + my_strlen(str2);
  result++;
  while (!str1[result])
    result--;
  if (result < 1)
    result = 1;
  return (result);
}

char	*my_replace(char *str1, char *str2, t_limits limits, char *ops)
{
  char	*result;
  int	size;
  int	counter;

  replace_borne(str1, &limits, ops);
  size = find_size_replace(str1, str2, limits.left, limits.right);
  result = my_malloc(size);
  counter = 0;
  while (counter < limits.left)
    {
      result[counter] = str1[counter];
      counter = counter + 1;
    }
  while (counter - limits.left < my_strlen(str2))
    {
      result[counter] = str2[counter - limits.left];
      counter = counter + 1;
    }
  while (str1[limits.right + counter - limits.left - my_strlen(str2)])
    {
      result[counter] = str1[limits.right + counter - limits.left
			     - my_strlen(str2)];
      counter = counter + 1;
    }
  result[counter] = '\0';
  return (result);
}

char	*epur_nbr_begin(char *nbr, t_limits limite, int position, char *ops)
{
  int	counter;
  char	*result;
  
  result = my_malloc(position - limite.left + 1);
  counter = limite.left;
  while (counter < position)
    {
      result[counter - limite.left] = nbr[counter];
      counter = counter + 1;
    }
  result[counter - limite.left] = '\0';
  my_abs(&result, 0, ops);
  return (result);
}

char	*my_remove(char *str, int min, int max, char *ops)
{
  char	*expr;
  int	counter;
  
  if (str == NULL || max <= min || min < 0 || max > my_strlen(str))
      return (NULL);
  if (str[min] == ops[0])
      min = min + 1;
  counter = 0;
  expr = my_malloc (max - min);
  while (counter < (max - min))
    {
      expr[counter] = str[min + counter];
      counter = counter + 1;
    }
  expr[counter] = '\0';
  return (expr);
}
