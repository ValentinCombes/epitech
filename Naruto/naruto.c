#include "naruto.h"

int	teamin = 0;
int	g_save = 1;

int		ouverture(char *str, char *prompt, t_tournoi *tournoi)
{
  int		fd;
  int		fd_perso;
  time_t	t;
  struct tm	*temps;
  char		*path;
  char		*path_perso;
  int		good = 0;
  char		*s;

  t = time(&t);
  tournoi->debut = temps = localtime(&t);
  while (good != 1)
    {
      if (!my_strcmp(str, "ngnt4") || !my_strcmp(str, "Naruto Gekitou Ninja Taisen 4")) {
	tournoi->name = my_strcreat("Naruto Gekitou Ninja Taisen 4");
	path = my_strcreat("ngnt4");
	good = 1;
      }
      else if (!my_strcmp(str, "nun5") || !my_strcmp(str, "Naruto Ultimate Ninja 5")) {
	tournoi->name = my_strcreat("Naruto Ultimate Ninja 5");
	tournoi->rounds = 1;
	path = my_strcreat("nun5");
	good = 1;
      }
      else if (!my_strcmp(str, "nsgnts") || !my_strcmp(str, "Naruto Shippuden Gekitou Ninja Taisen Special")) {
	tournoi->name = my_strcreat("Naruto Shippuden Gekitou Ninja Taisen Special");
	path = my_strcreat("nsgnts");
	good = 1;
      }
      else if (!my_strcmp(str, "ncon") || !my_strcmp(str, "Naruto Clash of Ninja")) {
	tournoi->name = my_strcreat("Naruto Clash of Ninja");
	path = my_strcreat("ncon");
	good = 1;
      }
      else if (!my_strcmp(str, "quit")) {
	return (-1);
      }
      else {
	my_printf("%Cinvalid game.\n%C%C%s% \r", RED, BLUE, BOLD, prompt, my_strlen(prompt) + my_strlen(str) + 3);
	str = xfree(str);
	s = line_edit(0, prompt);
	str = my_epurstr(s);
	/* str = get_next_line(1); */
	s = xfree(s);
	return (-42);
      }
    }
  
  s = my_strcat(path, "_perso");
  path_perso = my_strcat("perso/", s);
  s = xfree(s);
  fd_perso = open(path_perso, O_RDONLY);
  if (fd_perso == - 1)
    my_puterror("no characters file.");
  remplis_perso(tournoi, fd_perso);
  path_perso = xfree(path_perso);
  close(fd_perso);
  fd = open(path, O_APPEND | O_RDWR, 0666);
  if (fd == -1)
    fd = open(path, O_CREAT | O_APPEND | O_RDWR, 0666);
  if (fd == -1)
    my_puterror("can't open data, contact the dev.");
  my_printf("Tournoi de %s du %d/%d/%d ouvert :\n", tournoi->name, temps->tm_mday, temps->tm_mon + 1, temps->tm_year % 100);
  tournoi->fd = fd;
  return (fd);
}

void	my_help()
{
  my_printf("%Cquit%C to exit\n", GREEN, WHITE);
  my_printf("%Chistory%C to print history\n", GREEN, WHITE);
  my_printf("%Cend%C to close the actual task\n", GREEN, WHITE);
  my_printf("%Cadd <player>%C to add a player\n", GREEN, WHITE);
  my_printf("%Cremove <player>%C to remove a player\n", GREEN, WHITE);
  my_printf("%Cteam <player>%C to chose player's team\n", GREEN, WHITE);
  my_printf("%Cstart <player1> <player2>%C to start a match\n", GREEN, WHITE);
  my_printf("%Cclose%C to close the competition\n", GREEN, WHITE);
  /* my_printf("%Crand%C to random\n", GREEN, WHITE); */
  my_printf("%Cclear%C to clear the screen\n", GREEN, WHITE);
  my_printf("%Cshow <what>%C to show what (\"players\", \"characters\", \"matchs\", \"scores\")\n", GREEN, WHITE);
  my_printf("%Callow <character> <value>%C to allow or not a character\n", GREEN, WHITE);
  my_printf("%Cteamsize <size>%C to change maxsize of team. default: 6\n", GREEN, WHITE);
  my_printf("%Cexport <file>%C to save players and teams in <file>\n", GREEN, WHITE);
  my_printf("%Cload <file>%C to load players and teams from <file>\n", GREEN, WHITE);
}

int		add_player(char *str, t_tournoi *tournoi)
{
  char		**wtab;
  t_user	*user;
  int		id = 0;

  wtab = my_str_to_wordtab(str);
  if (!wtab[1])
    {
      my_putwarn("usage: add <player>.");
      return (-1);
    }
  user = tournoi->player;
  if (user != NULL) {
    id++;
    while (user->next) {
      if (!my_strcmp(user->name, wtab[1]))
	{
	  my_printf("%Cthis player already exist.\n", RED);
	  return (-1);
	}
      user = user->next;
      id++;
    }
    if (!my_strcmp(user->name, wtab[1]))
      {
	my_printf("%Cthis player already exist.\n", RED);
	return (-1);
      }
    if (id > 7)
      {
    	my_printf("%Csorry, actually more than 8 players makes the app bug, working on a patch.\n");
    	return (-1);
      }
    user->next = xmalloc(sizeof(*user->next));
    user->next->prev = user;
    user = user->next;
    user->next = NULL;
  }
  else {
    tournoi->player = xmalloc(sizeof(*tournoi->player));
    user = tournoi->player;
    user->prev = NULL;
    user->next = NULL;
  }
  user->pers = NULL;
  if (tournoi->team_max == 0)
    user->pers = tournoi->pers;
  user->win = 0;
  user->lose = 0;
  user->matchwin = 0;
  user->matchlose = 0;
  user->name = my_strcreat(wtab[1]);
  user->id = id;
  wtab = my_freetab((void **) wtab);
  return (0);
}

/* void    aff_border() */
/* { */
/*   int	width; */

/*   width = tgetnum("co"); */
/*   my_printf("%C+", BOLD); */
/*   width -= 2; */
/*   while (width > 0) */
/*     { */
/*       if (width > 10) */
/*         my_printf("%C%ms", BOLD, 10, "----------"); */
/*       else */
/*         my_printf("%C%ms", BOLD, width, "----------"); */
/*       width -= 10; */
/*     } */
/*   my_printf("%C+\n", BOLD); */
/* } */

void		aff_ligne(t_perso *pers, t_perso *select, int posx, int posy, int line)
{
  int	width;

  width = tgetnum("co");
  my_printf("%C|", BOLD);

  if (line == posy && posx == 0)
    my_printf("%C%C~>", BLUE, BOLD);
  else
    my_printf("  ");

  if (pers) {
    if (pers->allowed == 0)
      my_printf("%C%C%ms", BOLD, BOLDGREY, (width / 2) - 3, pers->name);
    else
      my_printf("%C%ms", BOLD, (width / 2) - 3, pers->name);
  }
  else
    my_printf("% ", width / 2 - 2);

  my_printf("%C|", BOLD);
  if (line == posy && posx == 1)
    my_printf("%C%C~>", BLUE, BOLD);
  else
    my_printf("  ");

  if (select)
    {
      if (width % 2)
	my_printf("%C%ms|\n", BOLD, (width / 2) - 3, select->name);
      else
	my_printf("%C%ms|\n", BOLD, (width / 2) - 4, select->name);
    }
  else
    {
      if (width % 2)
	my_printf("% %C|\n", width / 2 - 2, BOLD);
      else
	my_printf("% %C|\n", width / 2 - 3, BOLD);
    }
}

t_perso		*chose_perso(t_perso *pers, int posx, int posy, t_perso *select)
{
  t_perso	*curs;
  t_perso	*tmp;

  if (posx == 0)
    {
      curs = pers;
      while (posy && curs)
	{
	  curs = curs->next;
	  posy--;
	}
      if (!curs || curs->allowed != 1)
	return select;
      tmp = select;
      if (tmp)
	{
	  if (!my_strcmp(tmp->name, curs->name))
	    return select;
	  while (tmp->next)
	    {
	      tmp = tmp->next;
	      if (!my_strcmp(tmp->name, curs->name))
		return select;
	    }
	  tmp->next = xmalloc(sizeof(*tmp));
	  tmp->next->prev = tmp;
	  tmp = tmp->next;
	}
      else
	{
	  tmp = xmalloc(sizeof(*tmp));
	  tmp->prev = NULL;
	}
      tmp->next = NULL;
      tmp->name = my_strcreat(curs->name);
      if (tmp->prev)
	tmp->nb = tmp->prev->nb + 1;
      else
	tmp->nb = 1;
      if (tmp->prev)
	return select;
      else
	return tmp;
    }
  if (posx == 1)
    {
      curs = select;
      while (posy && curs)
	{
	  curs = curs->next;
	  posy--;
	}
      if (curs)
	{
	  if (curs->prev)
	    {
	      curs->prev->next = curs->next;
	      if (curs->next)
		curs->next->prev = curs->prev;
	    }
	  else
	    {
	      select = curs->next;
	      if (select)
		select->prev = NULL;
	    }
	  curs->name = xfree(curs->name);
	  curs = xfree(curs);
	}
      return select;
    }
  return NULL;
}

void	resize_func(int sig)
{
  (void)sig;
  if (teamin == 1)
    aff_perso(resize.team_max, resize.pers, resize.user);
  /* else */
  /*   my_printf("plop\n"); */
  return;
}

void		aff_perso(int team_max, t_perso *pers, t_user *user)
{
  t_perso	*perso;
  t_perso	*tmp;
  int		ligne;
  int		posx = 0;
  int		posy = 0;
  char		s[10];
  struct termios term;
  struct termios termsave;
  int		count1 = 0;
  int		count2 = 0;
  int		width;
  int		height;
  int		start;
  int		n;

  teamin = 1;

  resize.pers = pers;
  resize.team_max = team_max;
  resize.user = user;
  resize.end = 0;
  start = 0;
  tcgetattr(0, &term);
  tcgetattr(0, &termsave);
  term.c_cc[VTIME] = 0;
  term.c_cc[VMIN] = 1;
  term.c_lflag &= ~(ECHO|ICANON);
  tcsetattr(0, 0, &term);

  while (!resize.end)
    {
      signal(SIGWINCH, &resize_func);
      if (!resize.end)
	{
	  n = 0;
	  count1 = 0;
	  count2 = 0;
	  my_clear();
	  width = tgetnum("co");
	  height = tgetnum("li");
	  my_printf("%CSelect your team %s :\n'c' pour choisir,'q' pour quiter\n", BOLD, user->name);
	  perso = pers;
	  aff_border();
	  if (width % 2)
	    my_printf("%C|  %ms|  %ms|\n", BOLD, (width / 2) - 3, "Disponibles", (width / 2) - 3, "Selectiones");
	  else
	    my_printf("%C|  %ms|  %ms|\n", BOLD, (width / 2) - 3, "Disponibles", (width / 2) - 4, "Selectiones");
	  aff_border();
	  tmp = user->pers;
	  ligne = 0;
	  while (n < start)
	    {
	      n++;
	      if (perso)
		perso = perso->next;
	      if (tmp)
		tmp = tmp->next;
	    }
	  while (ligne < height - 7)
	    {
	      aff_ligne(perso, tmp, posx, posy, ligne);
	      if (perso)
		{
		  perso = perso->next;
		  count1++;
		}
	      if (tmp)
		{
		  tmp = tmp->next;
		  count2++;
		}
	      ligne++;
	    }
	  aff_border();
	  usleep(65000);
	  count1--;
	  if (count1 < 0)
	    count1 = 0;
	  count2--;
	  if (count2 < 0)
	    count2 = 0;
	  xread(0, s, 10);
	  if (s[0] == 27 && s[1] == 91 && s[2] == 'A')
	    {
	      if (posy == 0 && start > 0 && posx == 0)
		start--;
	      if (posy > 0)
		posy--;
	    }
	  if (s[0] == 27 && s[1] == 91 && s[2] == 'B')
	    if (posy < height || (perso))
	      {
		if (posy == height - 8 && posx == 0)
		  {
		    if (perso)
		      start++;
		  }
		else
		  {
		    if (posx == 0 && posy < count1)
		      posy++;
		    if (posx == 1 && posy < count2)
		      posy++;
		  }
	      }
	  if (s[0] == 27 && s[1] == 91 && s[2] == 'C')
	    if (posx < 1)
	      {
		posx++;
		if (posy > count2)
		  posy = count2;
	      }
	  if (s[0] == 27 && s[1] == 91 && s[2] == 'D')
	    if (posx > 0)
	      {
		posx--;
		if (posy > count1)
		  posy = count1;
	      }
	  if (s[0] == 'c')
	    {
	      if (posx == 0 && count2 < (team_max - 1))
		user->pers = chose_perso(pers, posx, posy + start, user->pers);
	      if (posx == 1)
		user->pers = chose_perso(pers, posx, posy + start, user->pers);
	    }
	  if (s[0] == 'q')
	    resize.end = 1;
	}
    }
  tcsetattr(0, 0, &termsave);
  teamin = 0;
}

void		set_team(char *str, t_tournoi *tournoi)
{
  t_user	*user;
  char		**wtab;
  char		buf[10];
  struct termios term;
  struct termios termsave;

  if (tournoi->team_max == 0)
    {
      my_putwarn("with teamsize = 0 there is no need of team, all players are able to chose all characters");
      return;
    }
  tcgetattr(0, &termsave);
  wtab = my_str_to_wordtab(str);
  if (!wtab[1])
    {
      my_putwarn("usage: team <player>.");
      return;
    }
  user = tournoi->player;
  while (user != NULL && my_strcmp(user->name, wtab[1]))
    user = user->next;
  if (user != NULL)
    aff_perso(tournoi->team_max, tournoi->pers, user);
  else
    {
      my_printf("%Cno player named %s add him Y/n\n", RED, wtab[1]);
      tcgetattr(0, &term);
      tcgetattr(0, &termsave);
      term.c_cc[VTIME] = 0;
      term.c_cc[VMIN] = 1;
      term.c_lflag &= ~(ECHO|ICANON);
      tcsetattr(0, 0, &term);
      xread(0, buf, 10);
      if (buf[0] == 'Y') {
	add_player(str, tournoi);
	set_team(str, tournoi);
      }
      tcsetattr(0, 0, &termsave);
    }
  wtab = my_freetab((void **) wtab);
  tcsetattr(0, 0, &termsave);
  my_clear();
}

void		allow(char *str, t_tournoi *tournoi)
{
  t_perso	*tmp;
  char		**tablo;

  tmp = tournoi->pers;
  tablo = my_str_to_wordtab(str);
  if (!tablo[1] || !tablo[2])
    {
      my_putwarn("usage: allow <character> <0 or 1>.");
      return;
    }
  while (tmp && my_strcmp(tmp->name, tablo[1]))
    tmp = tmp->next;
  if (tmp)
    tmp->allowed = my_get_nbr(tablo[2]);
  tablo = my_freetab((void **)tablo);
}

void		teamsize(char *str, t_tournoi *tournoi)
{
  char		**tablo;

  tablo = my_str_to_wordtab(str);
  if (!tablo[1])
    {
      my_putwarn("usage: teamsize <size>.");
      return;
    }
  if ((!tournoi->team_max && my_get_nbr(tablo[1])) || (!my_get_nbr(tablo[1]) && tournoi->team_max))
    {
      if (tournoi->player)
	{
	  my_putwarn("set or unset teamsize to 0 is dangerous if there is already players. This change many things and the dev had the FLEMME to did all check to make this work well... please set or unset teamsize to 0 before adding players");
	  return;
	}
    }
  tournoi->team_max = my_get_nbr(tablo[1]);
  my_printf("teamsize set at %d\n", tournoi->team_max);
  tablo = my_freetab((void **)tablo);
}

void		aff_scores(t_tournoi *tournoi)
{
  t_user	*plop;
  t_user	*player;
  t_user	*fst;
  t_match	*match;
  int		a;
  int		res = 1;
  t_user	*higher;

  player = tournoi->player;
  plop = xmalloc(sizeof(*plop));
  fst = NULL;
  while (player)
    {
      *plop = *player;
      player = player->next;
      plop->prev = fst;
      if (player)
	{
	  plop->next = xmalloc(sizeof(*plop->next));
	  fst = plop;
	  plop = plop->next;
	}
    }
  while (plop->prev)
    plop = plop->prev;
  player = plop;
  my_printf("+");
  while (player)
    {
      my_printf("--------------------------+");
      player = player->next;
    }
  my_printf("\n|");
  player = plop;
  while (player)
    {
      my_printf(" %ms|", 25, player->name);
      player = player->next;
    }
  my_printf("\n+");
  player = plop;
  while (player)
    {
      my_printf("--------------------+-----+");
      player = player->next;
    }
  my_printf("\n|");
  match = tournoi->matchs;
  while (match)
    {
      player = plop;
      while (player)
	{
	  if (!my_strcmp(match->player1->name, player->name))
	    {
	      my_printf(" %ms|  %d  |", 19, match->pers1->name, match->round1);
	    }
	  else if (!my_strcmp(match->player2->name, player->name))
	    {
	      my_printf(" %ms|  %d  |", 19, match->pers2->name, match->round2);
	    }
	  else
	    {
	      my_printf(" % |     |", 20); 
	    }
	  player = player->next;
	}
      if (match->next)
	{
	  my_printf("\n|");
	}
      match = match->next;
    }
  my_printf("\n+");
  player = plop;
  while (player)
    {
      my_printf("--------------------+-----+");
      player = player->next;
    }
  my_printf("\n|");
  player = plop;
  while (player)
    {
      if (player->lose)
	player->score = (player->win * 100) / (player->win + player->lose);
      else
	player->score = 100;
      a = 3;
      if (player->score >= 10)
	a--;
      if (player->score == 100)
	a--;
      my_printf(" reussite% +% %d%% +", 12, a, player->score);
      player = player->next;
    }
  my_printf("\n+");
  player = plop;
  while (player)
    {
      my_printf("--------------------+-----+");
      player = player->next;
    }
  my_printf("\n");
  fst = plop;
  while (fst)
    {
      player = fst;
      higher = fst;
      while (player)
	{
	  if (player->matchwin > higher->matchwin)
	    higher = player;
	  if (player->matchwin == higher->matchwin && player->score > higher->score)
	    higher = player;
	  player = player->next;
	}
      my_printf("%s arrive en place numero %d avec %d victoire(s), %d defaite(s) et %d%% de reussite\n", higher->name, res, higher->matchwin, higher->matchlose, higher->score);
      if (higher->next)
      	higher->next->prev = higher->prev;
      if (higher->prev)
      	higher->prev->next = higher->next;
      if (higher == fst)
      	fst = higher->next;
      higher = xfree(higher);
      res++;
    }
}

void		show(char *str, t_tournoi *tournoi)
{
  t_perso	*pers;
  t_match	*match;
  t_user	*user;
  t_user	*curs;
  /* t_poll	*poll; */
  char		**tablo;
  int		deja_vu;

  tablo = my_str_to_wordtab(str);
  if (!tablo[1])
    {
      my_putwarn("usage: show <players, characters or matchs>.");
      return;
    }
  match = tournoi->matchs;
  /* poll = tournoi->poll; */
  pers = tournoi->pers;
  user = tournoi->player;
  if (!my_strcmp(tablo[1], "characters"))
    {
      while (pers)
	{
	  if (pers->allowed)
	    my_printf("%s\n", pers->name);
	  else
	    my_printf("%C%s\n", BOLDGREY, pers->name);
	  pers = pers->next;
	}
    }
  if (!my_strcmp(tablo[1], "players"))
    {
      while (user)
	{
	  my_printf("%s :\n", user->name);
	  pers = user->pers;
	  while (pers)
	    {
	      my_printf("  %C->%C %s\n", GREEN, WHITE, pers->name);
	      pers = pers->next;
	    }
	  user = user->next;
	}
    }
  if (!my_strcmp(tablo[1], "matchs"))
    {
      /* while (poll) */
      /* 	{ */
	  /* match = poll->matchs; */
	  while (match)
	    {
	      my_printf("%C%s vs %s\n", BOLD, match->player1->name, match->player2->name);
	      match = match->next;
	    }
	  match = tournoi->matchs;
	  /* match = poll->matchs; */
	  curs = tournoi->player;
	  /* curs = poll->player; */
	  my_printf("%C+--------------------+", BOLD);
	  while (curs)
	    {
	      my_printf("%C-------------------+", BOLD);
	      curs = curs->next;
	    }
	  curs = tournoi->player;
	  /* curs = poll->player; */
	  my_printf("\n%C| % |", BOLD, 20); 
	  while (curs)
	    {
	      my_printf("%C %s% |", BOLD, curs->name, 19 - my_strlen(curs->name));
	      curs = curs->next;
	    }
	  curs = tournoi->player;
	  /* curs = poll->player; */
	  my_printf("%C\n+--------------------+", BOLD);
	  while (curs)
	    {
	      my_printf("%C-------------------+", BOLD);
	      curs = curs->next;
	    }
	  while (user)
	    {
	      my_printf("\n%C| %s% |", BOLD, user->name, 20 - my_strlen(user->name));
	      curs = tournoi->player;
	      /* curs = poll->player; */
	      while (curs)
		{
		  int ok = 0;
		  match = tournoi->matchs;
		  /* match = poll->matchs; */
		  deja_vu = 0;
		  if (user == curs)
		    my_printf("%C///////////////////%C|", BOLD, WHITE);
		  else
		    {
		      while (match)
			{
			  if (match && !my_strcmp(match->player1->name, user->name) && !my_strcmp(match->player2->name, curs->name) && deja_vu == 0)
			    {
			      my_printf("%C%C///////////////////%C|", BOLD, GREEN, WHITE);
			      ok = 1;
			      deja_vu = 1;
			    }
			  else if (match && !my_strcmp(match->player2->name, user->name) && !my_strcmp(match->player1->name, curs->name) && deja_vu == 0)
			    {
			      my_printf("%C%C///////////////////%C|", BOLD, GREEN, WHITE);
			      ok = 1;
			      deja_vu = 1;
			    }
			  match = match->next;
			}
		      if (ok == 0)
			my_printf("%C % |", BOLD, 19); 
		    }
		  curs = curs->next;
		}
	      curs = tournoi->player;
	      /* curs = poll->player; */
	      my_printf("\n%C+--------------------+", BOLD);
	      while (curs)
		{
		  my_printf("%C-------------------+", BOLD);
		  curs = curs->next;
		}
	      user = user->next;
	    }
	  my_printf("\n");
	/*   poll = poll->next; */
	/* } */
    }
  if (!my_strcmp(tablo[1], "scores"))
    {
      aff_scores(tournoi);
    }
  tablo = my_freetab((void **)tablo);
}

void		remove_player(char *str, t_tournoi *tournoi)
{
  t_user	*player;
  t_perso	*pers;
  t_perso	*tmp;
  char		**tablo;

  tablo = my_str_to_wordtab(str);
  if (!tablo[1])
    {
      my_putwarn("usage: remove <player>.");
      return;
    }
  player = tournoi->player;
  while (player && my_strcmp(player->name, tablo[1]))
    {
      player = player->next;
    }
  if (player->lose != 0 || player->win != 0)
    {
      my_putwarn("this player has start the contest, he must finish it.");
      return;
    }
  if (player)
    {
      if (player->next)
	player->next->prev = player->prev;
      if (player->prev)
	player->prev->next = player->next;
      else
	tournoi->player = player->next;
      player->name = xfree(player->name);
      pers = player->pers;
      while (pers && tournoi->team_max > 0)
	{
	  tmp = pers->next;
	  pers->name = xfree(pers->name);
	  pers = xfree(pers);
	  pers = tmp;
	}
      player = xfree(player);
    }
  tablo = my_freetab((void **)tablo);
}

t_perso		*chose_perso_for_match(int posy, t_perso *pers)
{
  while (posy && pers)
    {
      pers = pers->next;
      posy--;
    }
  return pers;
}

t_perso		*select_perso_for_match(t_user *player, int size)
{
  t_perso	*perso;
  t_perso	*tmp;
  int		ligne;
  int		posx = 0;
  int		posy = 0;
  char		s[10];
  int		end = 0;
  struct termios term;
  struct termios termsave;
  int		count1 = 0;
  int		count2 = 0;
  int		width;
  int		start;
  int		n;

  tcgetattr(0, &term);
  tcgetattr(0, &termsave);
  term.c_cc[VTIME] = 0;
  term.c_cc[VMIN] = 1;
  term.c_lflag &= ~(ECHO|ICANON);
  tcsetattr(0, 0, &term);

  tmp = NULL;
  start = 0;
  if (size == 0)
    size = tgetnum("li") - 8;
  while (!end)
    {
      count2 = 0;
      my_clear();
      width = tgetnum("co");
      my_printf("%CSelect your character %s :\n'c' pour choisir, 'v' pour valider\n", BOLD, player->name);
      perso = player->pers;
      aff_border();
	  my_printf("%C|  %ms|  %ms|\n", BOLD, (width / 2) - 3, "Disponibles", (width / 2) - 3, "Selectiones");
      aff_border();
      ligne = 0;
      n = 0;
      while (n < start)
	{
	  n++;
	  if (perso)
	    perso = perso->next;
	}
      while (ligne < size)
	{
	  if (!count2)
	    {
	      if (perso)
		perso->allowed = 1;
	      aff_ligne(perso, tmp, posx, posy, ligne);
	    }
	  else
	    aff_ligne(perso, NULL, posx, posy, ligne);
	  if (perso)
	    {
	      perso = perso->next;
	      count1++;
	    }
	  if (tmp && !count2)
	    count2++;
	  ligne++;
	}
      aff_border();
      usleep(65000);
      count1--;
      if (count1 < 0)
	count1 = 0;
      xread(0, s, 10);
      if (s[0] == 27 && s[1] == 91 && s[2] == 'A')
	{
	  if (posy == 0 && start > 0)
	    start--;
	  if (posy > 0)
	    posy--;
	}
      if (s[0] == 27 && s[1] == 91 && s[2] == 'B')
	if (posy < size || (perso))
	  {
	    if (posy == size - 1)
	      {
		if (perso)
		  start++;
	      }
	    else
	      {
		if (posy < count1)
		  posy++;
	      }
	  }
      if (s[0] == 'c')
	tmp = chose_perso_for_match(posy + start, player->pers);
      if (s[0] == 'q')
	return (NULL);
      if (s[0] == 'v')
	{
	  if (tmp)
	    {
	      end = 1;
	      my_clear();
	      my_printf("%s choisit %s pour ce match\n", player->name, tmp->name);
	    }
	  else
	    my_putwarn("you must choose.");
	}
    }
  tcsetattr(0, 0, &termsave);
  return tmp;
}

t_match		*add_match(t_user *player1, t_user *player2, t_tournoi *tournoi)
{
  t_match	*match;
  char		*s;
  int		round = 1;
  int		*last_winner;

  match = xmalloc(sizeof(*match));
  match->player1 = player1;
  match->player2 = player2;
  match->round1 = 0;
  match->round2 = 0;
  my_printf("match entre %s et %s\n", player1->name, player2->name);

  match->pers1 = select_perso_for_match(player1, tournoi->team_max);
  match->pers2 = select_perso_for_match(player2, tournoi->team_max);
  if (!match->pers1 || !match->pers2)
    {
      match = xfree(match);
      my_printf("%Cmatch canceled\n", RED);
      return (NULL);
    }

  last_winner = xmalloc((tournoi->rounds * 2) * sizeof(*last_winner));
  my_printf("le match entre %s et %s peut commencer\n", player1->name, player2->name);
  while (match->round1 < tournoi->rounds && match->round2 < tournoi->rounds)
    {
      my_printf("vainqueur du round %d :\n", round);
      s = line_edit(0, NULL);
      if (!my_strcmp(s, player1->name))
	{
	  last_winner[round - 1] = 1;
	  match->round1++;
	  player1->win++;
	  player2->lose++;
	  round++;
	  s = xfree(s);
	}
      else if (!my_strcmp(s, player2->name))
	{
	  last_winner[round - 1] = 2;
	  match->round2++;
	  player2->win++;
	  player1->lose++;
	  round++;
	  s = xfree(s);
	}
      else if (!my_strcmp(s, "cancel") && round - 1 > 0)
	{
	  if (last_winner[round - 2] == 1)
	    {
	      match->round1--;
	      player1->win--;
	      player2->lose--;
	      round--;
	    }
	  else if (last_winner[round - 2] == 2)
	    {
	      match->round2--;
	      player2->win--;
	      player1->lose--;
	      round--;
	    }
	  s = xfree(s);
	}
      else if (!my_strcmp(s, "end"))
	{
	  s = xfree(s);
	  return (match);
	}
      else if (!my_strncmp(s, "forfait ", 8))
	{
	  if (!my_strcmp(s + 8, player1->name))
	    {
	      player2->matchwin++;
	      player1->matchlose++;
	      my_printf("%s remporte le match par forfait\n", player2->name);
	    }
	  else if (!my_strcmp(s + 8, player2->name))
	    {
	      player1->matchwin++;
	      player2->matchlose++;
	      my_printf("%s remporte le match par forfait\n", player1->name);
	    }
	  s = xfree(s);
	  return (match);
	}
      else
	{
	  my_putwarn("%s is not a player in this match", s);
	  s = xfree(s);
	}
    }
  if (match->round1 == tournoi->rounds)
    {
      my_printf("%s remporte le match %d a %d\n", player1->name, match->round1, match->round2);
      player1->matchwin++;
      player2->matchlose++;
    }
  if (match->round2 == tournoi->rounds)
    {
      my_printf("%s remporte le match %d a %d\n", player2->name, match->round2, match->round1);
      player2->matchwin++;
      player1->matchlose++;
    }

  return match;
}

void		start(char *str, t_tournoi *tournoi)
{
  t_match	*tmp;
  t_user	*player1;
  t_user	*player2;
  char		**wtab;

  wtab = my_str_to_wordtab(str);
  if (!wtab[1] || !wtab[2])
    {
      my_putwarn("usage: start <player1> <player2>.");
      return;
    }
  player1 = tournoi->player;
  while (player1 && my_strcmp(player1->name, wtab[1]))
    player1 = player1->next;
  player2 = tournoi->player;
  while (player2 && my_strcmp(player2->name, wtab[2]))
    player2 = player2->next;
  if (player1 == player2)
    {
      my_putwarn("%s can't fight himself.");
      return;
    }
  if (player1 && player2)
    {
      if (!player1->pers)
	my_putwarn("not enough character to player1.");
      else if (!player2->pers)
	my_putwarn("not enough character to player2.");
      else
	{
	  tmp = tournoi->matchs;
	  if (!tmp)
	    {
	      tournoi->matchs = add_match(player1, player2, tournoi);
	      if (tournoi->matchs)
		{
		  tournoi->matchs->prev = NULL;
		  tournoi->matchs->next = NULL;
		}
	    }
	  else
	    {
	      while (tmp->next)
		tmp = tmp->next;
	      tmp->next = add_match(player1, player2, tournoi);
	      if (tmp->next)
		{
		  tmp->next->prev = tmp;
		  tmp->next->next = NULL;
		}
	    }
	}
    }
  else
    my_putwarn("not enough players.");
}

void		aff_end(t_tournoi *tournoi)
{
  t_user	*player;
  t_match	*match;
  int		a;

  player = tournoi->player;
  my_printf("+");
  my_printf("%F+", tournoi->fd);
  while (player)
    {
      my_printf("--------------------------+");
      my_printf("%F--------------------------+", tournoi->fd);
      player = player->next;
    }
  my_printf("\n|");
  my_printf("%F\n|", tournoi->fd);
  player = tournoi->player;
  while (player)
    {
      my_printf(" %ms|", 25, player->name);
      my_printf("%F %ms|", tournoi->fd, 25, player->name);
      player = player->next;
    }
  my_printf("\n+");
  my_printf("%F\n+", tournoi->fd);
  player = tournoi->player;
  while (player)
    {
      my_printf("--------------------+-----+");
      my_printf("%F--------------------+-----+", tournoi->fd);
      player = player->next;
    }
  my_printf("\n|");
  my_printf("%F\n|", tournoi->fd);
  match = tournoi->matchs;
  while (match)
    {
      player = tournoi->player;
      while (player)
	{
	  if (!my_strcmp(match->player1->name, player->name))
	    {
	      my_printf(" %ms|  %d  |", 19, match->pers1->name, match->round1);
	      my_printf("%F %ms|  %d  |", tournoi->fd, 19, match->pers1->name, match->round1);
	    }
	  else if (!my_strcmp(match->player2->name, player->name))
	    {
	      my_printf(" %ms|  %d  |", 19, match->pers2->name, match->round2);
	      my_printf("%F %ms|  %d  |", tournoi->fd, 19, match->pers2->name, match->round2);
	    }
	  else
	    {
	      my_printf(" % |     |", 20); 
	      my_printf("%F % |     |", tournoi->fd, 20); 
	    }
	  player = player->next;
	}
      if (match->next)
	{
	  my_printf("\n|");
	  my_printf("%F\n|", tournoi->fd);
	}
      match = match->next;
    }
  my_printf("\n+");
  my_printf("%F\n+", tournoi->fd);
  player = tournoi->player;
  while (player)
    {
      my_printf("--------------------+-----+");
      my_printf("%F--------------------+-----+", tournoi->fd);
      player = player->next;
    }
  my_printf("\n|");
  my_printf("%F\n|", tournoi->fd);
  player = tournoi->player;
  while (player)
    {
      if (player->lose)
	player->score = (player->win * 100) / (player->win + player->lose);
      else
	player->score = 100;
      a = 3;
      if (player->score >= 10)
	a--;
      if (player->score == 100)
	a--;
      my_printf(" reussite% +% %d%% +", 12, a, player->score);
      my_printf("%F reussite% +% %d%% +", tournoi->fd, 12, a, player->score);
      player = player->next;
    }
  my_printf("\n+");
  my_printf("%F\n+", tournoi->fd);
  player = tournoi->player;
  while (player)
    {
      my_printf("--------------------+-----+");
      my_printf("%F--------------------+-----+", tournoi->fd);
      player = player->next;
    }
  my_printf("\n");
  my_printf("%F\n", tournoi->fd);
}

void		end(t_tournoi *tournoi)
{
  t_user	*player;
  int		res = 1;
  t_user	*higher;
  char		*s;

  my_printf("%FTournoi de %s du %d/%d/%d a %d:%d :\n", tournoi->fd, tournoi->name, tournoi->debut->tm_mday, tournoi->debut->tm_mon, tournoi->debut->tm_year % 100, tournoi->debut->tm_hour, tournoi->debut->tm_min);
  aff_end(tournoi);

  while (tournoi->player)
    {
      player = tournoi->player;
      higher = tournoi->player;
      while (player)
	{
	  if (player->matchwin > higher->matchwin)
	    higher = player;
	  if (player->matchwin == higher->matchwin && player->score > higher->score)
	    higher = player;
	  player = player->next;
	}
      my_printf("%s arrive en place numero %d avec %d victoire(s), %d defaite(s) et %d%% de reussite\n", higher->name, res, higher->matchwin, higher->matchlose, higher->score);
      my_printf("%F%s arrive en place numero %d avec %d victoires, %d defaites et %d%% de reussite\n", tournoi->fd, higher->name, res++, higher->matchwin, higher->matchlose, higher->score);
      higher->lose = 0;
      higher->win = 0;
      s = my_strcat("remove ", higher->name);
      remove_player(s, tournoi);
      s = xfree(s);
    }
  my_printf("%F\n", tournoi->fd);
  return;
}

void		export(char *str, t_tournoi *tournoi)
{
  int		fd;
  char		**tablo;
  t_user	*user;
  t_perso	*pers;

  tablo = my_str_to_wordtab(str);
  if (!tablo[1])
    {
      my_putwarn("usage: export <file>.");
      return;
    }
  if ((fd = open(tablo[1], O_RDWR)) == -1)
    fd = open(tablo[1], O_CREAT | O_RDWR, 00666);
  if (fd == -1)
    {
      my_putwarn("cannot create %s.", tablo[1]);
      return;
    }

  user = tournoi->player;
  while (user)
    {
      my_printf("%F%s :\n", fd, user->name);
      pers = user->pers;
      while (pers)
	{
	  my_printf("%F  %C->%C %s\n", fd, GREEN, WHITE, pers->name);
	  pers = pers->next;
	}
      user = user->next;
    }
  
  close(fd);
  tablo = my_freetab((void **)tablo);  
}

void		load(char *str, t_tournoi *tournoi)
{
  int		fd;
  char		**tablo;
  char		*s;
  char		*tmp;
  t_user	*user;
  t_perso	*temp;
  t_perso	*pers = NULL;
  t_perso	*search;
  int		err = -1;

  tablo = my_str_to_wordtab(str);
  if (!tablo[1])
    {
      my_putwarn("usage: load <file>.");
      return;
    }
  if ((fd = open(tablo[1], O_RDWR)) == -1)
    {
      my_putwarn("load: %s no such file or directory.", tablo[1]);
      return;
    }
  tablo = my_freetab((void **)tablo);  

  user = tournoi->player;
  s = get_next_line(fd);
  while (s)
    {
      if (my_strncmp(s, "  [32m->[0m ", my_strlen("  [32m->[0m ")))
	{
	  tmp = my_strcat("add ", s);
	  err = add_player(tmp, tournoi);
	  tmp = xfree(tmp);

	  user = tournoi->player;
	  while (user && user->next)
	    user = user->next;
	}
      else if (err != -1)
      	{
	  search = tournoi->pers;
	  while (search && my_strcmp(s + my_strlen("  [32m->[0m "), search->name))
	    search = search->next;
	  if (search)
	    {
	      if (!user->pers)
		{
		  user->pers = xmalloc(sizeof(*user->pers));
		  pers = user->pers;
		  pers->prev = NULL;
		  pers->next = NULL;
		}
	      else
	      	{
	      	  pers = user->pers;
	      	  while (pers->next)
	      	    pers = pers->next;
	      	  temp = xmalloc(sizeof(*pers->next));
	      	  temp->prev = pers;
	      	  pers->next = temp;
	      	  temp->next = NULL;
		  pers = temp;
	      	}
	      pers->name = my_strcreat(search->name);
	    }
      	}
      s = xfree(s);
      s = get_next_line(fd);
    }

  close(fd);
}

void	list_file(char *str)
{
  char	**tablo;
  char	*path;

  tablo = my_str_to_wordtab(str);
  if (!tablo[1])
    path = my_strcreat(".");
  else
    path = my_strcreat(tablo[1]);
  tablo = my_freetab((void **)tablo);
  my_ls(path, PRINT, NULL);
  path = xfree(path);
}

int		my_cmdanalyse(char *str, t_tournoi *tournoi)
{
  if (!my_strcmp(str, "quit")) {
    str = xfree(str);
    return 42;
  }
  else if (!my_strncmp(str, "add ", 4))
    add_player(str, tournoi);
  else if (!my_strcmp(str, "history"))
    dump_history();
  else if (!my_strncmp(str, "remove ", 7))
    remove_player(str, tournoi);
  else if (!my_strncmp(str, "team ", 5))
    set_team(str, tournoi);
  else if (!my_strcmp(str, "help"))
    my_help();
  else if (!my_strcmp(str, "clear"))
    my_clear();
  else if (!my_strncmp(str, "allow ", 6))
    allow(str, tournoi);
  else if (!my_strncmp(str, "teamsize ", 9))
    teamsize(str, tournoi);
  else if (!my_strncmp(str, "show ", 5))
    show(str, tournoi);
  else if (!my_strncmp(str, "export ", 7))
    export(str, tournoi);
  else if (!my_strncmp(str, "load ", 5))
    load(str, tournoi);
  else if (!my_strncmp(str, "start ", 6))
    start(str, tournoi);
  else if (!my_strncmp(str, "ls ", 3))
    list_file(str);
  else if (!my_strcmp(str, "end"))
    {
      end(tournoi);
      str = xfree(str);
      return 42;
    }
  else if (my_strlen(str))
    my_printf("%Cinvalid command: %s\n", RED, str);
  str = xfree(str);
  return 0;
}

t_perso		*add_perso(char *name, int allowed)
{
  t_perso	*tmp;

  tmp = xmalloc(sizeof(*tmp));
  tmp->name = my_strcreat(name);
  tmp->allowed = allowed;
  tmp->prev = NULL;
  tmp->next = NULL;
  return tmp;
}

void		remplis_perso(t_tournoi *tournoi, int fd_perso)
{
  t_perso	*tmp;
  char		*s;
  int		allow;

  if (!tournoi->pers)
    {
      s = get_next_line(fd_perso);
      allow = my_get_nbr(s + my_strlen(s) - 1);
      s[my_strlen(s) -2] = '\0';
      tournoi->pers = add_perso(s, allow);
      s = xfree(s);
    }
  tmp = tournoi->pers;
  s = get_next_line(fd_perso);
  while (s)
    {
      allow = my_get_nbr(s + my_strlen(s) - 1);
      s[my_strlen(s) -2] = '\0';
      tmp->next = add_perso(s, allow);
      s = xfree(s);
      tmp->next->prev = tmp;
      tmp = tmp->next;
      s = get_next_line(fd_perso);
    }
}

void		free_perso(t_tournoi *tournoi)
{
  t_perso	*tmp;
  t_perso	*plop;

  tmp = tournoi->pers;
  while (tmp)
    {
      plop = tmp->next;
      tmp = xfree(tmp);
      tmp = plop;
    }
}

void		tmp_save(t_tournoi *tournoi)
{
  t_user	*plop;
  t_user	*player;
  t_user	*fst;
  t_match	*match;
  int		a;
  int		res = 1;
  t_user	*higher;
  int		fd;

  if (!tournoi->player)
    return;
  /* my_printf("saving...\n"); */
  fd = open("tmp", O_RDWR, 0666);
  if (fd == -1)
    fd = open("tmp", O_RDWR | O_CREAT, 0666);
  player = tournoi->player;
  plop = xmalloc(sizeof(*plop));
  fst = NULL;
  while (player)
    {
      *plop = *player;
      player = player->next;
      plop->prev = fst;
      if (player)
	{
	  plop->next = xmalloc(sizeof(*plop->next));
	  fst = plop;
	  plop = plop->next;
	}
    }
  while (plop->prev)
    plop = plop->prev;
  player = plop;
  my_printf("%F+", fd);
  while (player)
    {
      my_printf("%F--------------------------+", fd);
      player = player->next;
    }
  my_printf("%F\n|", fd);
  player = plop;
  while (player)
    {
      my_printf("%F %ms|", fd, 25, player->name);
      player = player->next;
    }
  my_printf("%F\n+", fd);
  player = plop;
  while (player)
    {
      my_printf("%F--------------------+-----+", fd);
      player = player->next;
    }
  my_printf("%F\n|", fd);
  match = tournoi->matchs;
  while (match)
    {
      player = plop;
      while (player)
	{
	  if (!my_strcmp(match->player1->name, player->name))
	    {
	      my_printf("%F %ms|  %d  |", fd, 19, match->pers1->name, match->round1);
	    }
	  else if (!my_strcmp(match->player2->name, player->name))
	    {
	      my_printf("%F %ms|  %d  |", fd, 19, match->pers2->name, match->round2);
	    }
	  else
	    {
	      my_printf("%F % |     |", fd, 20); 
	    }
	  player = player->next;
	}
      if (match->next)
	{
	  my_printf("%F\n|", fd);
	}
      match = match->next;
    }
  my_printf("%F\n+", fd);
  player = plop;
  while (player)
    {
      my_printf("%F--------------------+-----+", fd);
      player = player->next;
    }
  my_printf("%F\n|", fd);
  player = plop;
  while (player)
    {
      if (player->lose)
	player->score = (player->win * 100) / (player->win + player->lose);
      else
	player->score = 100;
      a = 3;
      if (player->score >= 10)
	a--;
      if (player->score == 100)
	a--;
      my_printf("%F reussite% +% %d%% +", fd, 12, a, player->score);
      player = player->next;
    }
  my_printf("%F\n+", fd);
  player = plop;
  while (player)
    {
      my_printf("%F--------------------+-----+", fd);
      player = player->next;
    }
  my_printf("%F\n", fd);
  fst = plop;
  while (fst)
    {
      player = fst;
      higher = fst;
      while (player)
	{
	  if (player->matchwin > higher->matchwin)
	    higher = player;
	  if (player->matchwin == higher->matchwin && player->score > higher->score)
	    higher = player;
	  player = player->next;
	}
      my_printf("%F%s arrive en place numero %d avec %d victoire(s), %d defaite(s) et %d%% de reussite\n", fd, higher->name, res, higher->matchwin, higher->matchlose, higher->score);
      if (higher->next)
      	higher->next->prev = higher->prev;
      if (higher->prev)
      	higher->prev->next = higher->next;
      if (higher == fst)
      	fst = higher->next;
      higher = xfree(higher);
      res++;
    }
  close (fd);
  /* my_printf("saved\n"); */
}

void	look_for_args(int ac, char **av)
{
  int	n;

  n = 1;
  while (n < ac)
    {
      if (!my_strncmp("--", av[n], 2))
	{
	  my_printf("%C%Coption %s\n", BOLD, GREEN, av[n]);
	  if (!my_strcmp("--nosave", av[n]))
	    g_save = 0;
	}
      n++;
    }
}

void		add_player_in_poll(t_poll *poll, t_user *player)
{
  t_user	*tmp;

  if (poll->players)
    {
      tmp = poll->players;
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = xmalloc(sizeof(*tmp->next));
      tmp->next->prev = tmp;
      tmp->next->next = NULL;
      tmp = tmp->next;
      tmp->id = player->id;
      tmp->name = my_strcreat(player->name);
      tmp->win = player->win;
      tmp->lose = player->lose;
      tmp->matchwin = player->matchwin;
      tmp->matchlose = player->matchlose;
      tmp->score = player->score;
      tmp->lastused = player->lastused;
    }
  else
    {
      poll->players = xmalloc(sizeof(*poll->players));
      tmp = poll->players;
      tmp->prev = NULL;
      tmp->next = NULL;
      tmp->id = player->id;
      tmp->name = my_strcreat(player->name);
      tmp->win = player->win;
      tmp->lose = player->lose;
      tmp->matchwin = player->matchwin;
      tmp->matchlose = player->matchlose;
      tmp->score = player->score;
      tmp->lastused = player->lastused;
    }
}

void		add_poll(t_tournoi *tournoi)
{
  t_poll	*tmp;

  if (tournoi->poll)
    {
      tmp = tournoi->poll;
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = xmalloc(sizeof(*tmp->next));
      tmp->next->nb = tmp->nb + 1;
      tmp->next->prev = tmp;
      tmp->next->next = NULL;
      tmp = tmp->next;
      tmp->matchs = NULL;
      tmp->players = NULL;
    }
  else
    {
      tournoi->poll = xmalloc(sizeof(*tournoi->poll));
      tmp = tournoi->poll;
      tmp->nb = 1;
      tmp->prev = NULL;
      tmp->next = NULL;
      tmp->matchs = NULL;
      tmp->players = NULL;
    }
}

void		open_tournoi(int ac, char **av)
{
  int		fd;
  char		*s;
  char		*prompt;
  char		*game;
  t_tournoi	*tournoi;
  int		quit;
  int		n;

  look_for_args(ac, av);
  tournoi = xmalloc(sizeof(*tournoi));
  tournoi->team_max = 6;
  tournoi->rounds = 3;
  tournoi->type = GRID;
  tournoi->poll = NULL;
  tournoi->player = NULL;
  tournoi->pers = NULL;
  tournoi->matchs = NULL;
  prompt = my_sprintf("%C%C~> ", BLUE, BOLD);
  n = 1;
  fd = -42;
  while (n < ac)
    {
      if (my_strncmp("--", av[n], 2) && fd == -42)
	{
	  game = my_epurstr(av[n]);
	  fd = ouverture(game, prompt, tournoi);
	}
      n++;
    }
  if (fd == -42)
    {
      my_printf("%Cplease enter a game\n", RED);
      s = line_edit(0, prompt);
      game = my_epurstr(s);
      s = xfree(s);
      fd = ouverture(game, prompt, tournoi);
      if (fd == -1)
	return;
    }
  s = NULL;
  quit = 0;
  while (quit != 42)
    {
      s = line_edit(0, prompt);
      my_printf("\n");
      /* my_printf("\"%C%s%C\"\n", GREEN, s, WHITE); */
      quit = my_cmdanalyse(my_epurstr(s), tournoi);
      s = xfree(s);
      if (g_save)
	tmp_save(tournoi);
    }
  free_perso(tournoi);
  tournoi = xfree(tournoi);
  prompt = xfree(prompt);
  close(fd);
}

int	main(int ac, char **av)
{
  open_tournoi(ac, av);
  free_history();
  return (0);
}
