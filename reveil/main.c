#include "reveil.h"

t_alarm	*first = NULL;

t_alarm		*get_alarm()
{
  int		fd;
  char		*s;
  char		**tablo;
  t_alarm	*alarm;
  t_alarm	*current;
  int		n;

  n = 1;
  alarm = NULL;
  fd = open("alarm", O_RDONLY);
  if (fd != -1) {
    s = get_next_line(fd);
    while (s) {
      if (alarm == NULL) {
	alarm = xmalloc(sizeof(*alarm));
	current = alarm;
	alarm->prev = NULL;
	alarm->next = NULL;
      }
      else {
	current->next = xmalloc(sizeof(*current->next));
	current->next->prev = current;
	current = current->next;
	current->next = NULL;
      }
      tablo = my_str_to_wordtab(s);
      current->hour = my_get_nbr(tablo[0]);
      current->min = my_get_nbr(tablo[1]);
      current->alarm = my_strcreat(tablo[2]);
      my_printf("%Calarm%d set to %T with %s\n", BLUE, n, current->hour, current->min, 0, current->alarm);
      tablo = my_freetab((void *) tablo);
      s = xfree(s);
      s = get_next_line(fd);
      n++;
    }
  }
  return (alarm);
}

void		get_sigint(int sig)
{
  t_alarm	*current;
  t_alarm	*tmp;
  int		n = 1;

  int	f;
  int	x;
  int	a;
  int	b;
  int	c;
  char	*s;

  current = first;
  if (sig)
    {
  /*     canon_mode(); */
  /*     my_printf("\r%CSIGINT caught :\n", RED); */
  /*     canon_mode(); */
  /*     srand(getpid() * 42); */
  /*     x = rand() % 100; */
  /*     a = rand() % 6; */
  /*     b = rand() % 42; */
  /*     c = rand() % 20; */
  /*     my_printf("%Cif you want to quit, give me the right answer : f(x) = %d.x^2 + %d.x + %d for x = %d\n", BLUE, a, b, c, x); */
  /*     s = line_edit(0, "~> "); */
  /*     f = a * (x * x) + b * x + c; */
  /*     while (atoi(s) != f) */
  /* 	{ */
  /* 	  s = xfree(s); */
  /* 	  my_printf("%Cwrong answer : f(x) = %d.x^2 + %d.x + %d for x = %d\n", RED, a, b, c, x); */
  /* 	  s = line_edit(0, "~> "); */
  /* 	} */
  /*     s = xfree(s); */
  /*     while (current) */
  /* 	{ */
  /* 	  tmp = current->next; */
  /* 	  current->alarm = xfree(current->alarm); */
  /* 	  current = xfree(current); */
  /* 	  current = tmp; */
  /* 	  my_printf("%Calarm%d freed\n", RED, n); */
  /* 	  n++; */
  /* 	} */
      canon_mode();
      my_printf("%Cnow exiting.\n", RED);
      canon_mode();
      exit (0);
    }
}

void		reveil()
{
  time_t	t;
  struct tm	*temps;
  int		pid = 0;
  t_alarm	*alarm;
  t_alarm	*current;
  int		my_stdcout = 21;
  int		my_stdcerr = 42;

  non_canon_mode();
  t = time(&t);
  temps = localtime(&t);
  my_printf("%Cstarted at %T\n", GREEN, temps->tm_hour, temps->tm_min, temps->tm_sec);
  alarm = get_alarm();
  first = alarm;
  while (42) {
    t = time(&t);
    temps = localtime(&t);
    if (alarm != NULL && temps->tm_sec == 0) {
      current = alarm;
      while (current) {
	if (current->hour == temps->tm_hour && current->min == temps->tm_min) {
	  if (pid != 0)
	    kill(pid, SIGTERM);
	  my_printf("%Cstart %s at %T\n", GREEN, current->alarm, temps->tm_hour, temps->tm_min, temps->tm_sec);
	  pid = fork();
	  if (pid == -1)
	    my_puterror("fail on fork");
	  if (pid == 0) {
	    dup2(1, my_stdcout);
	    if (close(1))
	      my_putwarn("fail to close 1.");
	    dup2(2, my_stdcerr);
	    if (close(2))
	      my_putwarn("%Ffail to close 2.", my_stdcerr);
	    system("amixer set Master unmute 100%");
	    execl("/usr/bin/cvlc", "cvlc", current->alarm, "--random", NULL);
	  }
	}
	current = current->next;
      }
    }
    my_printf("%T%   \r", temps->tm_hour, temps->tm_min, temps->tm_sec, 15);
    signal(SIGINT, get_sigint);
    sleep(1);
  }
}

void		timer(int time)
{
  struct tm	temps;
  int		pid;

  temps.tm_sec = 0;
  temps.tm_min = 0;
  temps.tm_hour = 0;

  temps.tm_min = time % 60;
  temps.tm_hour = time / 60;

  while (42)
    {
      my_printf("%T   \r", temps.tm_hour, temps.tm_min, temps.tm_sec);
      if (temps.tm_hour == 0 && temps.tm_min == 0 && temps.tm_sec == 0)
	{
	  pid = fork();
	  if (pid == -1)
	    my_puterror("fail on fork");
	  if (pid == 0) {
	    system("amixer set Master unmute 75%");
	    execl("/usr/bin/cvlc", "cvlc", "media/alegria.mp3", "--volume", "1024", NULL);
	  }
	  temps.tm_sec = -1;
	}
      signal(SIGINT, get_sigint);
      if (temps.tm_sec > 0)
	temps.tm_sec--;
      else
	{
	  if (temps.tm_min > 0)
	    {
	      temps.tm_sec = 59;
	      temps.tm_min--;
	    }
	  else if (temps.tm_hour > 0)
	    {
	      temps.tm_sec = 59;
	      temps.tm_min = 59;
	      temps.tm_hour--;
	    }
	}
      sleep(1);
    }
}

int		main(int ac, char **av)
{
  /* aff_charizard(); */
  if (ac > 1)
    {
      if (ac == 3 &&my_strcmp(av[1], "-timer") == 0)
	{
	  timer(my_get_nbr(av[2]));
	}
      else
	reveil();
    }
  else
    reveil();

  return (0);
}
