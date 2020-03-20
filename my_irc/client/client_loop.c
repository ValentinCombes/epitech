/*
** client_loop.c for my_irc in /home/combes_v//Proj/my_irc/client
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Sun Apr 22 21:13:27 2012 valentin combes
** Last update Sun Apr 22 22:56:12 2012 valentin combes
*/

#include	"libmy.h"
#include	"client.h"
#include	"rbuffer.h"
#include	"aff.h"

void	init_loop(t_loop *loop)
{
  loop->rc = 0;
  loop->wc = 0;
  loop->src = 0;
  loop->swc = 0;
  loop->quit = 1;
}

int	look_for_command(char *msg, t_cli *cli, t_aff *list)
{
  my_printf("%s\n", msg);
  if (!my_strcmp(msg, "/quit"))
    return (0);
  if (!my_strncmp(msg, "/nick ", 6))
    cli->nick = get_nick(msg, list, cli->nick);
  return (1);
}

int	client_loop(char *buf, int *rc, int *wc, t_cli *cli)
{
  int	quit;
  char	*msg;
  char	*serv_answer;

  msg = NULL;
  serv_answer = NULL;
  msg = line_edit(0, "~> ");
  non_canon_mode();
  quit = 1;
  if (msg && strlen(msg))
    {
      my_printf("%F%s\n", cli->s, msg);
      while (!serv_answer)
	serv_answer = rotative_buffer(buf, rc, wc, cli->s);
      quit = look_for_command(msg, cli, g_list);
      serv_answer = xfree(serv_answer);
      if (msg[0] != '/')
	aff(cli->nick, msg, g_list);
      msg = xfree(msg);
    }
  return (quit);
}

int	client_recieve_loop(char *buf, int *rc, int *wc, t_cli *cli)
{
  char	*msg;
  char	*name;

  name = NULL;
  while (!name)
    name = rotative_buffer(buf, wc, rc, cli->s);
  write(cli->s, "ok\n", 3);
  msg = NULL;
  while (!msg)
    msg = rotative_buffer(buf, wc, rc, cli->s);
  if (!my_strcmp(msg, "/quit"))
    return (0);
  if (msg[0] != '/')
    aff(name, msg, g_list);
  msg = xfree(msg);
  return (1);
}
