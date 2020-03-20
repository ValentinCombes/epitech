/*
** tab_aff.c for libmy in /home/valentin/Projets_persos/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Tue Feb 22 11:14:04 2011 valentin combes
** Last update Sat May 12 14:03:38 2012 valentin combes
*/

#include	"libmy.h"

void    aff_border()
{
  int	width;

  my_printf("%C+", BOLD);
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  width = w.ws_col;
  width -= 2;
  while (width > 0)
    {
      if (width > 10)
        my_printf("%C%ms", BOLD, 10, "----------");
      else
        my_printf("%C%ms", BOLD, width, "----------");
      width -= 10;
    }
  my_printf("%C+\n", BOLD);
}

void	tab_void_line(int column, int width, int a)
{
  my_printf(" ");
  if (a == column - 1)
    my_printf("% ", width / (column) + (width % column));
  else
    my_printf("% ", width / (column));
  my_printf(" %C|", BOLD);
}

void	aff_strline(int width, int a, int column, char *str)
{
  my_printf(" ");
  if (a == column - 1)
    my_printf("%ms", width / (column) + (width % column) - 1, str);
  else
    my_printf("%ms", width / (column) - 1, str);
  my_printf(" %C|", BOLD);
}

void	aff_nbrline(int width, int a, int column, int nbr)
{
  my_printf(" ");
  if (a == column - 1)
    my_printf("%md", width / (column) + (width % column) - 1, nbr);
  else
    my_printf("%md", width / (column) - 1, nbr);
  my_printf(" %C|", BOLD);
}

void			aff_line_of_tab(char *str, t_tab **ttab, int line, int column)
{
  int			n;
  int			a;
  int			width;
  struct winsize	w;

  n = -1;
  a = 0;
  ioctl(0, TIOCGWINSZ, &w);
  width = w.ws_col - (2 * column) - 1;
  my_printf("%C|", BOLD);
  while (str[++n])
    if (str[n] == '%')
      {
	if (line < ttab[a]->size)
	  {
	    if (str[n + 1] == 's')
	      aff_strline(width, a, column, ((char **)(ttab[a]->data))[line]);
	    else if (str[n + 1] == 'd')
	      aff_nbrline(width, a, column, ((int *)(ttab[a]->data))[line]);
	  }
	else
	  tab_void_line(column, width, a);
	a++;
      }
  my_printf("\n");
}
