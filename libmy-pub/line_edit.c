/*
** line_edit.c for libmy in /home/combes_v//Projets_persos/svn/valentin/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Sat May 12 13:38:33 2012 valentin combes
** Last update Fri Oct 26 19:28:43 2012 
*/

#include "libmy.h"

static char	*ctrly = NULL;

void	longest_cut(char *name, char *longest)
{
  int	n = 0;

  while (name[n] == longest[n])
    n++;
  longest[n] = '\0';
}

char		*line_edit(int fd, char *prompt)
{
  int		insert;
  int		n;
  int		tmp;
  int		len;
  int		ret;
  char		buf[6];
  char		buffer[BUFSIZE];
  char		*s;
  t_hist	*tmp_history;

  tmp_history = NULL;
  non_canon_mode();
  n = 0;
  len = 0;
  insert = 1;
  while (n < BUFSIZE)
    buffer[n++] = '\0';
  n = 0;
  if (prompt)
    my_printf("%s", prompt);
  my_printf("%C \r", HIGHLIGHT);
  while (buf[0] != INTERRUPT)
    {
      aff_buffer(prompt, buffer, n, len);
      ret = read(fd, buf, 6);

      /* my_printf("%d {%d", ret, buf[0]); */
      /* int i = 1; */
      /* while (i < ret) */
      /* 	my_printf(".%d", buf[i++]); */
      /* my_printf("}\n"); */

      if (ret == 1)
	{

	  if (buf[0] == 9 || buf[0] == 4)
	    {
	      aff_buffer(prompt, buffer, -1, len + 1);
	      if (COMP == 1)
		line_search(buffer, &n, &len);
	    }
	  else if (buf[0] == 27);
	  else if (buf[0] == 12)
	    my_clear();
	  else if (buf[0] == 11)
	    {
	      if (ctrly)
		ctrly = xfree(ctrly);
	      ctrly = my_strcreat(buffer + n);
	      my_put_space(0, len + my_strlen(prompt) + 2);
	      my_printf("\r");
	      buffer[n] = '\0';
	      len = n;
	    }
	  else if (buf[0] == 25)
	    {

	      if (ctrly)
		{
		  my_strcpy(buffer + n, ctrly);
		  n += my_strlen(ctrly);
		  len += my_strlen(ctrly);
		}
	    }
	  else if (buf[0] == 127)
	    {

	      if (n > 0)
		{
		  n--;
		  if (n + 1 == len)
		    {
		      buffer[n] = '\0';
		      len--;
		    }
		  else if (insert == 1)
		    {
		      tmp = n;
		      while (tmp < len)
			{
			  buffer[tmp] = buffer[tmp + 1];
			  tmp++;
			}
		      len--;
		    }
		  else if (insert == 0)
		    {
		      buffer[n] = ' ';
		    }
		}
	    }
	  else if (buf[0] != INTERRUPT)
	    {

	      if (n < len && insert == 1)
		{
		  tmp = len + 1;
		  while (tmp > n)
		    {
		      buffer[tmp] = buffer[tmp - 1];
		      tmp--;
		    }
		  len++;
		}
	      buffer[n] = buf[0];
	      n++;
	      if (n - 1 == len)
		len++;
	    }
	}
      else if (ret == 3)
	{

	  if (prompt)
	    my_printf("% \r", len + 2 + my_strlen(prompt));
	  else
	    my_printf("% \r", len + 2);
	  if (buf[0] == 27 && buf[1] == 91
	      && buf[2] == 68 && n > 0)
	    n--;
	  if (buf[0] == 27 && buf[1] == 91
	      && buf[2] == 67 && n < len)
	    n++;
	  if (buf[0] == 27 && buf[1] == 91
	  	  && buf[2] == 66)
	      tmp_history = go_down_in_history(tmp_history, buffer, &n, &len);
	  if (buf[0] == 27 && buf[1] == 91
	      && buf[2] == 65)
	      tmp_history = go_up_in_history(tmp_history, buffer, &n, &len);
	}
      else if (ret == 4)
	{

	  if (buf[0] == 27 && buf[1] == 91
	      && buf[2] == 51 && buf[3] == 126
	      && n < len)
	    {
	      tmp = n;
	      while (tmp < len)
		{
		  buffer[tmp] = buffer[tmp + 1];
		  tmp++;
		}
	      len--;
	    }
	  if (buf[0] == 27 && buf[1] == 91
	      && buf[2] == 50 && buf[3] == 126)
	    {
	      if (insert == 1)
		insert = 0;
	      else
		insert = 1;
	    }
	}
      else if (ret == 6)
	{

	  if (buf[0] == 27 && buf[1] == 91
	      && buf[2] == 49 && buf[3] == 59
	      && buf[4] == 53)
	    {
	      if (buf[5] == 68)
		{
		  if (n > 0 && buffer[n] != ' ')
		    n--;
		  while (n > 0 && buffer[n] == ' ')
		    n--;
		  while (n > 0 && buffer[n - 1] != ' ')
		    n--;
		}
	      if (buf[5] == 67)
		{
		  while (n < len && buffer[n] == ' ')
		    n++;
		  while (n < len && buffer[n] != ' ')
		    n++;
		}
	    }
	}
    }
  s = my_strcreat(buffer);
  if (my_strlen(s))
    add_in_history(s, 0);
  canon_mode();
  aff_buffer(prompt, buffer, -1, len);
  clean_tmp_history();
  return (s);
}
