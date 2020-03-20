/*
** line_edit.c for libmy in /home/combes_v//Projets_persos/svn/valentin/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Sat May 12 16:22:13 2012 valentin combes
** Last update Sat Oct 27 15:25:43 2012 
*/

#include "libmy.h"

static struct termios	save;
int	avoid_leak = 0;

void			non_canon_mode()
{
  struct termios	term;
  char			*src;
  char			*tmp;

  src = malloc(16);
  if (!avoid_leak)
    {
      tgetent(NULL, "xterm");
      avoid_leak = 1;
    }
  tmp = tgetstr("vi", &src);
  my_printf("%s", tmp);
  tmp = xfree(tmp);
  tcgetattr(0, &save);
  tcgetattr(0, &term);
  term.c_cc[VTIME] = 0;
  term.c_cc[VMIN] = 1;
  term.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(0, 0, &term);
}

void			canon_mode()
{
  char			*src;
  char			*tmp;

  src = malloc(16);
  if (!avoid_leak)
    {
      tgetent(NULL, "xterm");
      avoid_leak = 1;
    }
  tmp = tgetstr("ve", &src);
  my_printf("%s", tmp);
  tmp = xfree(tmp);
  tcsetattr(0, 0, &save);
}

int	my_nblen(int nb)
{
  int	puiss;
  int	a;

  puiss = 1;
  a = 1;
  while ((nb / puiss) >= 10)
    {
      puiss = puiss * 10;
      a++;
    }
  return (a);
}

int	my_get_size_of_hidden_char(int width, int pos, int len, int *start)
{
  int	end = 0;
  int	tmp;

  if (pos > width)
    {
      width -= 2;
      *start = my_nblen(pos - width);
      *start = my_nblen(*start + (pos - width)) + (pos - width);
      width -= (my_nblen(*start));
    }
  if ((len - (*start)) > width)
    {
      if (len - pos > 3)
	{
	  /* my_printf("%C2\n", GREEN); */
	  width -= 2;
	  end = my_nblen((len - *start) - width);
	  end = my_nblen(end + ((len - *start) - width)) + ((len - *start) - width);
	  if (*start)
	    {
	      end -= 3;
	      tmp = my_nblen(*start);
	      (*start) += my_nblen(end) + 2;
	      if (my_nblen(*start) > tmp)
		(*start)++;
	    }
	  width -= (my_nblen(end));
	}
      else
	{
	  /* my_printf("%C2\n", GREEN); */
	  if (*start)
	    {
	      tmp = my_nblen(*start);
	      (*start) += (len - pos);
	      if (my_nblen(*start) > tmp)
		(*start)++;
	    }
	  else if (pos > width)
	    {
	      *start = my_nblen(end) + 2;
	      *start += my_nblen(*start);
	    }
	}
    }
  if ((*start) && end)
    {
      if ((*start) < 6)
      	(*start) += 2;
    }
  else if (end)
    {
      if (pos > width)
	{
	  width -= 2;
	  (*start) = my_nblen(pos - width);
	  (*start) = my_nblen((*start) + (pos - width)) + (pos - width);
	  width -= (my_nblen(*start));
	}
    }
  return (end);
}

void	aff_buff_part(int width, char *buffer, int pos, int len)
{
  int	start;
  int	end;

  start = 0;
  end = 0;
  width -= 1;

  end = my_get_size_of_hidden_char(width, pos, len, &start);

  if (start)
    my_printf("[%d]", start);
  if (pos == len)
    my_printf("%ms%C ", pos - start, buffer + start, HIGHLIGHT);
  else
    my_printf("%ms%C%c%C%ms", pos - start, buffer + start, HIGHLIGHT, buffer[pos], WHITE, (len - pos) - end, buffer + pos + 1);
  if (end)
    my_printf("[%d]", end);
  my_printf("\r");
}

int	my_promptlen(char *prompt)
{
  int	n = 0;
  int	a = 0;

  while (prompt[n])
    {
      if (prompt[n] == '\33' && prompt[n + 1] == '[')
	{
	  a++;
	  while (prompt[n] && prompt[n] != 'm')
	    {
	      n++;
	      a++;
	    }
	}
      n++;
    }
  return (n - a);
}

void	aff_buffer(char *prompt, char *buffer, int pos, int len)
{
  int	width;

  tgetent(NULL, "xterm");
  width = tgetnum("co");
  if (prompt)
    {
      my_printf(prompt);
      width -= my_promptlen(prompt);
    }

  if (width > len)
    {
      if (pos == len)
	my_printf("%s%C ", buffer, HIGHLIGHT);
      else
	my_printf("%ms%C%c%C%ms", pos, buffer, HIGHLIGHT, buffer[pos], WHITE, len - pos - 1, buffer + pos + 1);

      my_printf("% \r", width - len);
    }
  else
    aff_buff_part(width, buffer, pos, len);
}

void    my_clear()
{
  char  *src;
  char  *str;

  src = xmalloc(4);
  if (!avoid_leak)
    {
      tgetent(NULL, "xterm");
      avoid_leak = 1;
    }
  str = tgetstr("cl", &src);
  my_printf(str);
  str = xfree(str);
}
