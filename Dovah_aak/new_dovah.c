#include "dovah.h"

SDL_Surface	*new_surface(char *name)
{
  SDL_Surface	*new;

  new = IMG_Load(name);
  if (!new)
    my_putwarn("fail on IMG_Load : %s.", SDL_GetError());
  return (new);
}

int	my_strncmp_no_case(char *s1, char *s2, int size)
{
  int	n;
  int	diff;

  n = 0;
  diff = s1[n] - s2[n];
  if (diff)
    {
      if (s1[n] == '\0' && s2[n] != '\0')
	return (s2[n]);
      if (s2[n] == '\0' && s1[n] != '\0')
	return (s1[n]);

      if (s1[n] <= 'z' && s1[n] >= 'a' && s2[n] <= 'Z' && s2[n] >= 'A')
	diff = (s1[n] - ('a' - 'A')) - s2[n];
      else if (s2[n] <= 'z' && s2[n] >= 'a' && s1[n] <= 'Z' && s1[n] >= 'A')
	diff = (s1[n] - ('A' - 'a')) - s2[n];
    }
  n++;
  while (s1[n] != '\0' && diff == 0 && n < size)
    {
      if (s1[n] == '\0' && s2[n] != '\0')
	return (s2[n]);
      if (s2[n] == '\0' && s1[n] != '\0')
      	return (s1[n]);

      diff = s1[n] - s2[n];
      if (diff)
	{
	  if (s1[n] <= 'z' && s1[n] >= 'a' && s2[n] <= 'Z' && s2[n] >= 'A')
	    diff = (s1[n] - ('a' - 'A')) - s2[n];
	  else if (s2[n] <= 'z' && s2[n] >= 'a' && s1[n] <= 'Z' && s1[n] >= 'A')
	    diff = (s1[n] - ('A' - 'a')) - s2[n];
	}
     n++;
    }
  return (diff);
}

void		new_sign(t_aff *aff, char *name)
{
  t_sign	*tmp;
  t_sign	*tmp2;
  char		*file_name;
  char		*path;

  file_name = my_strcat(name, ".png");
  path = my_strcat("textures/", file_name);
  tmp = xmalloc(sizeof(*tmp));
  tmp->alph = my_strcreat(name);
  tmp->sprite = new_surface(path);
  tmp->next = NULL;
  tmp->prev = NULL;
  file_name = xfree(file_name);
  path = xfree(path);
  if (aff->sign == NULL)
    aff->sign = tmp;
  else
    {
      tmp2 = aff->sign;
      while (tmp2->next)
	tmp2 = tmp2->next;
      tmp2->next = tmp;
      tmp->prev = tmp2;
    }
}

void	my_sdl_init(t_aff *aff)
{
  if (SDL_Init(SDL_INIT_VIDEO))
    my_puterror("fail on SDL_Init : %s.", SDL_GetError());

  new_sign(aff, "aa");
  new_sign(aff, "ah");
  new_sign(aff, "ei");
  new_sign(aff, "ey");
  new_sign(aff, "ii");
  new_sign(aff, "ir");
  new_sign(aff, "oo");
  new_sign(aff, "ur");
  new_sign(aff, "uu");
  new_sign(aff, "A");
  new_sign(aff, "B");
  new_sign(aff, "D");
  new_sign(aff, "E");
  new_sign(aff, "F");
  new_sign(aff, "G");
  new_sign(aff, "H");
  new_sign(aff, "I");
  new_sign(aff, "J");
  new_sign(aff, "K");
  new_sign(aff, "L");
  new_sign(aff, "M");
  new_sign(aff, "N");
  new_sign(aff, "O");
  new_sign(aff, "P");
  new_sign(aff, "Q");
  new_sign(aff, "R");
  new_sign(aff, "S");
  new_sign(aff, "T");
  new_sign(aff, "U");
  new_sign(aff, "V");
  new_sign(aff, "W");
  new_sign(aff, "X");
  new_sign(aff, "Y");
  new_sign(aff, "Z");

  TTF_Init();
  aff->police = TTF_OpenFont("ressources/comicbd.ttf", 15);
}

void	free_sprites(t_aff *aff)
{
  t_sign	*tmp;
  t_sign	*to_free;

  tmp = aff->sign;
  while (tmp)
    {
      to_free = tmp;
      tmp = tmp->next;
      SDL_FreeSurface(to_free->sprite);
      to_free->alph = xfree(to_free->alph);
      to_free = xfree(to_free);
    }
}

void		aff_sign(t_aff *aff, char *str, int *n, SDL_Rect *pos)
{
  t_sign	*tmp;
  int		stop;
  SDL_Surface	*text;
  SDL_Color	black;
  SDL_Color	white;

  black.r = 0;
  black.g = 0;
  black.b = 0;
  white.r = 255;
  white.g = 255;
  white.b = 255;

  tmp = aff->sign;
  stop = 0;

  if (str[*n] == ' ')
    {
      pos->x += 25;
      return;
    }
  while (tmp && !stop)
    {
      if (!my_strncmp(str + *n, tmp->alph, my_strlen(tmp->alph) - 1))
	{
	  SDL_BlitSurface(tmp->sprite, NULL, aff->screen, pos);
	  if (aff->police)
	    {
	      text = TTF_RenderText_Shaded(aff->police, tmp->alph, black, white);
	      pos->y += 27;
	      SDL_BlitSurface(text, NULL, aff->screen, pos);
	      pos->y -= 27;
	      SDL_FreeSurface(text);
	    }
	  (*n) += my_strlen(tmp->alph - 1);
	  stop = 1;
	  pos->x += 25;
	}
      tmp = tmp->next;
    }
}

void	init_SDLcolor(SDL_Color *black, SDL_Color *white)
{
  black->r = 0;
  black->g = 0;
  black->b = 0;
  white->r = 255;
  white->g = 255;
  white->b = 255;
}

void		does_it_match(t_aff *aff, char **tibo, char *s)
{
  SDL_Rect	pos;
  int		n;
  int		a;
  SDL_Surface	*texte;

  n = 0;
  if (my_strlen(s) < 1)
    return;
  while (tibo[n])
    {
      if (my_strlen(tibo[n]) == my_wordlen(s, 0) &&
	  !my_strncmp_no_case(s, tibo[n], my_strlen(tibo[n])))
	{
	  a = 0;
	  while (s[a] != ':')
	    a++;
	  a++;
	  while (s[a] == ' ')
	    a++;
	  pos.x = aff->positions[n].x;
	  pos.y = aff->positions[n].y + 50;
	  /* my_printf("for {%s} found {%s}\n", tibo[n], s + a); */
	  if (aff->police)
	    {
	      texte = TTF_RenderText_Shaded(aff->police, s + a,
					    aff->black, aff->white);
	      SDL_BlitSurface(texte, NULL, aff->screen, &pos);
	      SDL_FreeSurface(texte);
	    }
	  else
	    my_putwarn("no font loaded.");
	}
      n++;
    }
}

void		gogole_trad(t_aff *aff,char *str)
{
  int		fd;
  char		**tibo;
  char		*s;

  fd = open("ressources/dictionary", O_RDONLY);
  if (fd < 0)
    return;
  init_SDLcolor(&aff->black, &aff->white);
  tibo = my_str_to_wordtab(str);
  s = get_next_line(fd);
  while (s)
    {
      does_it_match(aff, tibo, s);
      s = xfree(s);
      s = get_next_line(fd);
    }
  my_freetab((void**)tibo);
  close(fd);
}

int	line_is_empty(char *s)
{
  int	n = 0;

  while (s[n] && s[n] != '\n')
    {
      if (s[n] != ' ' && s[n] != '\t')
	return (0);
      n++;
    }
  return (1);
}

void		look_what_we_got(char *str, t_aff *aff)
{
  SDL_Rect	pos;
  int		n;
  int		a;

  pos.x = 0;
  pos.y = 0;
  n = 0;

  a = 0;
  if (!line_is_empty(str))
    aff->positions[a++] = pos;
  while (str[n])
    {
      if (n > 0 && ((str[n - 1] == ' ') || (str[n - 1] == '\n')) && str[n] != '\n' && str[n] != ' ')
	aff->positions[a++] = pos;
      if (str[n] == '\n')
	{
	  pos.y += 75;
	  pos.x = 0;
	}
      aff_sign(aff, str, &n, &pos);
      n++;
    }
  gogole_trad(aff, str);
}

int		format_str(t_aff *aff, char *str)
{
  int		n = 0;
  int		stop;
  int		count;
  t_sign	*tmp;
  int		word;

  word = 1;
  count = 0;
  while (str[n])
    {
      stop = 0;
      tmp = aff->sign;
      while (tmp && !stop)
	{
	  while (str[n + 1] == '\0' && strlen(tmp->alph) > 1)
	    tmp = tmp->next;
	  if (!my_strncmp(str + n, tmp->alph, strlen(tmp->alph)))
	    {
	      n += (strlen(tmp->alph) - 1);
	      stop = 1;
	      count++;
	    }
	  else if (!my_strncmp_no_case(str + n, tmp->alph, strlen(tmp->alph)))
	    {
	      strncpy(str + n, tmp->alph, strlen(tmp->alph));
	      n += (strlen(tmp->alph) - 1);
	      stop = 1;
	      count++;
	    }
	  else
	    tmp = tmp->next;
	}
      if (str[n] == ' ' || str[n] == '\n')
	{
	  word++;
	  count++;
	}
      n++;
    }
  aff->positions = xmalloc((word + 1) * sizeof(*aff->positions));
  return (count);
}

int	main(int ac, char **av)
{
  char	**line_str;
  char	*s;
  char	*str;
  char	*tmp;
  int	fd;
  int	nbline;
  int	bignbline;
  int	maxlen;
  int	n;
  int	a;
  int	quit;
  t_aff	aff;
  SDL_Event event;

  /* aff_charizard(); */
  aff.sign = NULL;
  my_sdl_init(&aff);
  if (ac == 1)
    {
      s = line_edit(0, "~> ");
      format_str(&aff, s);
    }
  else
    {
      fd = open(av[1], O_RDONLY);
      if (fd == -1)
	my_puterror("Error: %s no such file or directory.", av[1]);
      str = get_next_line(fd);
      nbline = 1;
      s = get_next_line(fd);
      while (s)
	{
	  nbline++;
	  
	  tmp = my_strcat(str, "\n");
	  str = xfree(str);
	  str = my_strcat(tmp, s);
	  tmp = xfree(tmp);
	  s = xfree(s);
	  s = get_next_line(fd);
	}
      s = my_epurstr(str);
      str = xfree(str);
      format_str(&aff, s);
      maxlen = 0;
      my_printf("%s\n", s);
      n = 0;
      a = 0;
      while (s[n])
	{
	  a++;
	  n++;
	  if (s[n] == '\n')
	    {
	      a--;
	      if (a > maxlen)
		maxlen = a;
	      a = 0;
	    }
	}
      if (a > maxlen)
	maxlen = a;
      a = 0;
      /* my_printf("on %d line, with a max length of %d char :\n%s\n", nbline, maxlen, s); */
    }
  line_str = xmalloc(nbline * sizeof(*line_str));
  n = 0;
  a = 0;
  line_str[a++] = s;
  while (s[n])
    {
      if (s[n] && n > 0 && s[n - 1] == '\n')
	line_str[a++] = &s[n];
      n++;
    }
  if (nbline > 11)
    {
      bignbline = nbline;
      nbline = 11;
    }
  aff.screen = SDL_SetVideoMode(maxlen * 25, nbline * 75, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  if (!aff.screen)
    my_puterror("fail on SDL_SetVideoMode : %s.", SDL_GetError());
  SDL_WM_SetCaption(av[1], NULL);
  SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

  quit = 0;
  n = 0;
  while (!quit)
    {
      SDL_FillRect(aff.screen, NULL, 0xFFFFFF);
      look_what_we_got(line_str[n], &aff);

      SDL_Flip(aff.screen);

      SDL_WaitEvent(&event);
      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
	quit = 1;
      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
	{
	  if (n > 0)
	    n--;
	}
      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
	{
	  if (n < bignbline - 11)
	    n++;
	}
    }

  line_str = xfree(line_str);
  free_sprites(&aff);
  SDL_Quit();
  return (0);
}
