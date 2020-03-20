/*
** main.c for bistromathique in .
** 
** Made by Charlie Root
** Login   <rn@epita.fr>
** 
** Started on  Tue Oct 23 11:45:05 2001 Charlie Root
** Last update Tue Feb  5 06:48:58 2013 
*/

#include "bistromathique.h"

int		main(int ac,char **av)
{
  char		*expr;
  unsigned int	size;
  char		*ops;
  char		*base;

  ops = "()+-x/%";
  base = "0123456789";
  /*
  if (ac != 4)
    {
      my_putstr("Usage : ");
      my_putstr(av[0]);
      my_putstr(" base ops\"()+-*\/%\" exp_len\n");
      exit(1);
    }
  check_base(av[1]);
  check_ops(av[2]);
  expr = get_expr(size = atoi(av[3]));*/
  my_putstr(eval_expr(base,ops,av[1],size));
}

static void	check_base(char *b)
{
 if (strlen(b) < 2)
    {
      my_putstr("Bad base\n");
      exit(1);
    }
}

static char	*get_expr(unsigned int size)
{
  char	*expr;
  
  if (size <= 0)
    {
      my_putstr("Bad expr len\n");
      exit(1);
    }
  if ((expr = malloc(size+1))==0)
    {
      my_putstr("could not alloc\n");
      exit(1);
    }
  if (read(0,expr,size)!=size)
    {
      my_putstr("could not read\n");
      exit(1);
    }
  expr[size] = 0;
  return (expr);
}

static void	check_ops(char *ops)
{
  if (strlen(ops) != 7)
    {
      my_putstr("Bad ops\n");
      exit(1);
    }
}
