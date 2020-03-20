/*
** main_test.c for libmy in /home/valentin/Projets_persos/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Tue Feb 22 11:14:04 2011 valentin combes
** Last update Wed Apr 11 18:34:00 2018 
*/

# define INTERRUPT	'\n'
#include "libmy.h"

void	  aff_charizard();

void	affiche_un_tableau()
{
  t_tab	*a;
  char	**s;

  a = xmalloc(sizeof(*a));
  a->title = my_strcreat("Pokemon");
  s = my_str_to_wordtab("Bulbasaure Ivysaure Venusaure Charmander Charmeleon Charizard Squirtle Wartortle Blastoise");
  a->data = s;
  a->size = 9;
  tab_aff("%s %s", a, a);
  my_freetab(a->data);
  a->title = xfree(a->title);
  a = xfree(a);
}

char	*update_pwd(char *pwd, char *path, int fl)
{
  int	n;
  int	a;
  char	*result = NULL;

  a = my_strlen(pwd) - 1;
  if (path[0] == '/')
    {
      if (fl == 1)
	pwd = xfree(pwd);
      return (my_strcreat(path));
    }
  while (path[n])
    {
      if (!my_strncmp("../", path + n, 3))
	{
	  while (a > 0 && pwd[a] != '/')
	    a--;
	  pwd[a--] = '\0';
	  n += 2;
	}
      else if (!my_strncmp("..", path + n, 2))
	{
	  while (a > 0 && pwd[a] != '/')
	    a--;
	  pwd[a--] = '\0';
	  n++;
	}
      else
	{
	  if (pwd[my_strlen(pwd) - 1] != '/')
	    {
	      char	*tmp;
	      tmp = my_strcat(pwd, "/");
	      result = my_strcat(tmp, path + n);
	      tmp = xfree(tmp);
	    }
	  else
	    result = my_strcat(pwd, path + n);
	  while (path[n])
	    n++;
	  n--;
	}
      n++;
    }
  if (result == NULL)
    result = my_strcreat(pwd);
  if (fl == 1)
    pwd = xfree(pwd);
  return (result);
}

int	main()
{
  char	*s;
  char	*prompt;
  char	*pwd;

  pwd = getcwd(NULL, 0);
  aff_charizard();
  add_in_search("ls");
  add_in_search("quit");
  add_in_search("history");
  add_in_search("tab");
  prompt = my_strcreat("\33[1m\33[34m~> \33[0m");
  s = line_edit(0, prompt);
  my_printf("\n");
  while (my_strcmp("quit", s))
    {
      if (!my_strcmp("history", s))
  	dump_history();
      else if (!my_strcmp("tab", s))
  	affiche_un_tableau();
      else if (!my_strcmp("pwd", s))
  	my_printf("%s\n", pwd);
      else if (!my_strcmp("clear", s))
  	my_clear();
      else if (s && my_strlen(s))
  	{
  	  int	count = 0;
  	  if (!my_strncmp("ls", s, 2) || !my_strncmp("ll", s, 2))
  	    {
  	      char	**tabulo;
	      char	*new_path = NULL;
  	      tabulo = my_str_to_wordtab(s);
	      if (tabulo[1] && tabulo[1][0] != '-')
		new_path = update_pwd(my_strcreat(pwd), tabulo[1], 1);
	      else
		new_path = ".";
  	      if (tabulo[1] && tabulo[2])
  		my_ls(new_path, PRINT, tabulo[2] + 1);
  	      else if (tabulo[1] && my_strcmp("-r", tabulo[1]))
  		my_ls(new_path, PRINT, NULL);
  	      else if (tabulo[1] && !my_strcmp("-r", tabulo[1]))
  		my_ls(pwd, PRINT, tabulo[1] + 1);
  	      else
  		my_ls(pwd, PRINT, NULL);
  	      my_freetab((void **)tabulo);
  	    }
	  else if (!my_strncmp("find ", s, 5))
	    {
	      char	**tabulo;
	      tabulo = my_str_to_wordtab(s);
	      if (tabulo[1] && tabulo[2])
		{
		  my_printf("\"%s\" was found at the index %d of \"%s\"\n", tabulo[1], my_strstr(tabulo[2], tabulo[1]), tabulo[2]);
		}
	    }
	  else if (!my_strncmp("cat ", s, 4))
	    {
	      int	fd;
  	      char	**tabulo;
	      char	*line;
  	      tabulo = my_str_to_wordtab(s);
	      if (tabulo[1])
		{
		  fd = open(tabulo[1], O_RDONLY);
		  line = get_next_line(fd);
		  while (line)
		    {
		      my_printf("%s\n", line);
		      line = xfree(line);
		      line = get_next_line(fd);
		    }
		}
  	      my_freetab((void **)tabulo);
	    }
	  /* else if (!my_strncmp("bistro ", s, strlen("bistro ")))
	     my_printf("bistro: %s\n", bistro(s + strlen("bistro "))); */
  	  else
  	    {
  	    }
  	}
      s = xfree(s);
      s = line_edit(0, prompt);
      my_printf("\n");
    }
  s = xfree(s);
  prompt = xfree(prompt);
  free_history();
  remove_from_search("ls");
  remove_from_search("quit");
  remove_from_search("history");
  remove_from_search("tab");

  return (0);
}
