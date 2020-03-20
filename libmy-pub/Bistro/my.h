/*
** my.h for my in /afs/epitech.net/users/all/baudy_m/rendu/lib/my
** 
** Made by marie baudy
** Login   <baudy_m@epitech.net>
** 
** Started on  Tue Oct 19 14:25:34 2010 marie baudy
** Last update Tue Feb  5 06:06:55 2013 
*/

#ifndef __MY_H__
#define __MY_H__

#include "bistromathique.h"
#include <stdlib.h>
#include <string.h>

typedef struct	s_limits
{
  int		left;
  int		right;
}		t_limits;

typedef struct	s_div
{
  char		*nb1;
  char		*nb2;
  char		*base;
  char		*tmp;
  int		i;
}		t_div;

typedef struct	s_mul
{
  char	*base;
  int	size_base;
  int	p1;
  int	p2;
  int	len_1;
  int	len_2;
  int	nb1;
  int	nb2;
}		t_mul;

void	my_putchar(char c);
void	my_putstr(char *str);
void	my_sort_int_tab(int *tab, int size);

void	*my_memset(void *str, char c, int n);

int	my_isneg(int nb);
int	my_put_nbr(int nb);
int	my_swap(int *a, int *b);
int	my_strlen(char *str);
int	my_getnbr(char *str);
int	my_power_rec(int nb, int power);
int	my_square_root(int nb);
int	my_is_prime(int nombre);
int	my_find_prime_sup(int nb);
int	my_strcmp(char *s1, char *s2);
int	my_strncmp(char *s1, char *s2, int nb);
int	my_str_isalpha(char *str);
int	my_str_isnum(char *str);
int	my_str_islower(char *str);
int	my_str_isupper(char *str);
int	my_str_isprintable(char *str);
int	my_showstr(char *str);
int	my_showmem(char *str, int size);
int	my_strlcat(char *dest, char *src, int size);
int	my_getnbr_base(char *str, char *base);
int	my_putnbr_base(int nb, char *base);
int     c_contain_operator(char c, int ordre, int counter, char *ops);
int     str_contain_operator(char *str, char *ops);
int     max_level_paren(char *str, char *ops);
int     init_max_level_paren(int *a, int *b, int *c, int *d);
int     replace_left(char *str1, int *left, char *ops);
int	char_to_int(char *base, char c);
int	is_bigger(char *nb1, char *nb2, char *base);

char	*my_strcpy(char *dest, char *src);
char	*my_strncpy(char *dest, char *src, int n);
char	*my_revstr(char *str);
char	*my_strstr(char *str, char *to_find);
char	*my_strupcase(char *str);
char	*my_strlowcase(char *str);
char	*my_strcapitalize(char *str);
char	*my_strcat(char *dest, char *src);
char	*my_strncat(char *dest, char *src, int nb);
char    *eval_expr(char *base,char *ops,char *expr,unsigned int size);
char    *my_eval_expr(char *str, char *base, char *ops);
char    *my_do_op(char *str, int *counter, char *base, char *ops);
char    *my_itoa(int nb);
char    *my_div(char *str, int counter, char *base, char *ops);
char    *my_modulo(char *str, int counter, char *base, char *ops);
char    *my_sous(char *str, int counter, char *base, char *ops);
char    *my_add(char *str, int counter, char *base, char *ops);
char    *my_mult(char *str, int counter, char *base, char *ops);
char    *eval_paren(char *str, char *ops, char *base);
char    *my_remove(char *str, int min, int max, char *ops);
char    *my_replace(char *str1, char *str2, t_limits limits, char *ops);
char	*my_sous_particular(char *nb1, char *nb2, char *base, char *ops);
char	*my_add_particular(char *nb1, char *nb2, char *base, char *ops);
char	*my_mult_particular(char *str1, char *str2, char *base, char *ops);
char	*my_div_particular(char *str1, char *str2, char *base, char *ops);
char	*inf_sous_order(char *nb1, char *nb2, char *base, char *ops);
char	*initialise_res_and_r(char *res, int **r, int size);
char	*finish(t_mul *ptr, char *res, int *r, int len_2);
char	*inf_mult(char *nb1, char *nb2, char *base);
char	*remove_leading_zero(char **str, char *base, char *ops);
char	*epur_nbr_end(char *str, t_limits limite, int pos_op, char *ops);
char	*my_malloc(unsigned int size);

char	**my_str_to_wordtab(char *str);

struct s_mul	*init_struct(t_mul *ptr, char *base, char *n1, char *n2);

t_limits	pos_number(char *str, int pos, char *base, char *ops);

static void     check_base(char *base);
static void     check_ops(char *ops);

static char     *get_expr(unsigned size);


#endif /* __MY_H__ */
