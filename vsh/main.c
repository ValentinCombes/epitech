#include "libmy.h"

void	my_cd(char *pwd, char *arg)
{
  char	*tmp;
}

void	my_cat(char *cmd)
{
  int	fd;
  char	**table;
  char	*line;
  int	n = 1;
  int	e = 0;

  table = my_str_to_wordtab(cmd);
  while (table[n])
    {
      if (!my_strcmp("-e", table[n]))
	e = 1;
      n++;
    }
  n = 1;
  while (table[n])
    {
      if (my_strcmp("-e", table[n]))
	{
	  fd = open(table[n], O_RDONLY);
	  line = get_next_line(fd);
	  while (line)
	    {
	      if (e)
		my_printf("%s$\n", line);
	      else
		my_printf("%s\n", line);
	      line = xfree(line);
	      line = get_next_line(fd);
	    }
	}
      n++;
    }
}

int	main()
{
  char	*s = NULL;
  char	*prompt = my_strcreat("\33[1m\33[34m~> \33[0m");
  char	*pwd;

  s = line_edit(0, prompt);
  my_printf("\n");
  while (my_strcmp("exit", s))
    {
      /* TODO tableau de pointeur sur fonctions */
      if (!my_strcmp("history", s))
	dump_history();
      if (!my_strcmp("pwd", s))
	my_printf("%s\n", pwd);
      if (!my_strcmp("clear", s))
	my_clear();
      if (!my_strncmp("cat ", s, 4))
	my_cat(s);
      s = xfree(s);
      s = line_edit(0, prompt);
      my_printf("\n");
    }
  s = xfree(s);
  exit (0);
}
