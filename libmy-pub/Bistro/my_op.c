/*
** my_op.c for eval_expr in /home/barre-_t//hl/piscine/eval_expr
** 
** Made by thibault barre-villeneuve
** Login   <barre-_t@epitech.net>
** 
** Started on  Sun Oct 24 16:06:52 2010 thibault barre-villeneuve
** Last update Tue Nov  2 16:13:51 2010 marie baudy
*/

#include "my.h"

char		*my_mult(char *str, int counter, char *base, char *ops)
{
  t_limits	limite;
  char		*nb1;
  char		*nb2;

  limite = pos_number(str, counter, base, ops);
  nb1 = (char *) epur_nbr_begin(str, limite, counter, ops);
  nb2 = (char *) epur_nbr_end(str, limite, counter, ops);
  remove_leading_zero(&nb1, base, ops);
  remove_leading_zero(&nb2, base, ops);
  str = (char *) my_replace (str, my_mult_particular(nb1, nb2, base, ops),
			     limite, ops);
  free (nb1);
  free (nb2);
  return (str);
}

char		*my_add(char *str, int counter, char *base, char *ops)
{
  t_limits	limite;
  char		*nb1;
  char		*nb2;

  limite = pos_number(str, counter, base, ops);
  nb1 = (char *) epur_nbr_begin(str, limite, counter, ops);
  nb2 = (char *) epur_nbr_end(str, limite, counter, ops);
  remove_leading_zero(&nb1, base, ops);
  remove_leading_zero(&nb2, base, ops);
  str = (char *) my_replace (str,
			     my_add_particular(nb1, nb2, base, ops),
			     limite, ops);
  free (nb1);
  free (nb2);
  return (str);
}

char            *my_sous(char *str, int counter, char *base, char *ops)
{
  t_limits      limite;
  char          *nb1;
  char          *nb2;

  limite = pos_number(str, counter, base, ops);
  nb1 = (char *) epur_nbr_begin(str, limite, counter, ops);
  nb2 = (char *) epur_nbr_end(str, limite, counter, ops);
  remove_leading_zero(&nb1, base, ops);
  remove_leading_zero(&nb2, base, ops);
  str = (char *) my_replace(str,
			    (char *) my_sous_particular(nb1, nb2, base, ops),
			    limite, ops);
  free (nb1);
  free (nb2);
  return (str);

}

char		*my_modulo(char *str, int counter, char *base, char *ops)
{
  t_limits	limite;

  limite.left = counter - 1;
  limite.right = counter + 1;
  while (str[limite.left] >= '0' && str[limite.left] <= '9' &&
         limite.left > 0 && (str[limite.left] != '-' &&
			   c_contain_operator(str[limite.left], 0,
					      -1, ops) == 0))
    limite.left = limite.left - 1;
  while ((str[limite.right] >= '0' && str[limite.right] <= '9' ||
	  (str[limite.right] == '-' && limite.right == counter + 1))
	 && str[limite.right])
    limite.right = limite.right + 1;
  if (my_getnbr(&str[counter + 1]) == 0)
    {
      my_putstr("Division par ");
      my_putchar(base[0]);
      my_putchar('\n');
      exit(1);
    }
  return (my_replace(str, my_itoa(my_getnbr(&str[limite.left - 1])
				  % my_getnbr(&str[counter + 1])),
		     limite, ops));
}

char		*my_div(char *str, int counter, char *base, char *ops)
{
  t_limits	limite;
  char		*nb1;
  char		*nb2;

  limite = pos_number(str, counter, base, ops);
  nb1 = (char *) epur_nbr_begin(str, limite, counter, ops);
  nb2 = (char *) epur_nbr_end(str, limite, counter, ops);
  remove_leading_zero(&nb1, base, ops);
  remove_leading_zero(&nb2, base, ops);
  str = (char *) my_replace (str, (char *)
			     my_div_particular(nb1, nb2, base, ops),
			     limite, ops);
  free (nb1);
  free (nb2);
  return (str);

}
