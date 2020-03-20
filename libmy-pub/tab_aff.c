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

void	aff_tab_head(char *str, t_tab **ttab, int column, int width)
{
  int	n;
  int	a;

  a = 0;
  n = 0;
  aff_border();
  my_printf("%C|", BOLD);
  while (str[n])
    {
      if (str[n] == '%')
  	{
	  my_printf(" ");
	  if (a == column - 1)
	    my_printf("%ms", width / (column) + (width % column),
		      ttab[a++]->title);
	  else
	    my_printf("%ms", width / (column), ttab[a++]->title);
	  my_printf("%C|", BOLD);
  	}
      n++;
    }
  my_printf("\n");
}

void			aff_the_tab(char *str, t_tab **ttab, int column)
{
  int			width;
  struct winsize	w;
  int			line;

  line = 0;
  ioctl(0, TIOCGWINSZ, &w);
  width = w.ws_col - (2 * column) - 1;
  aff_tab_head(str, ttab, column, width);
  aff_border();
  while (line < w.ws_row - 5)
    {
      aff_line_of_tab(str, ttab, line, column);
      line++;
    }
  aff_border();
}

void	tab_aff(char *str, ...)
{
  va_list	ap;
  int		n;
  t_tab		**ttab;
  int		column;
  int		a;

  n = -1;
  column = 0;
  va_start(ap, str);
  while (str[++n])
    if (str[n] == '%')
      column++;
  ttab = xmalloc((column + 1) * sizeof(*ttab));
  n = 0;
  a = 0;
  while (str[n])
    {
      if (str[n] == '%')
	ttab[a++] = (t_tab *) va_arg(ap, t_tab *);
      n++;
    }
  aff_the_tab(str, ttab, column);
  va_end(ap);
}
