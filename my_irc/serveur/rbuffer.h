/*
** rbuffer.h for my_irc in /home/combes_v//Proj/my_irc/aff
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Sat Apr 21 01:12:37 2012 valentin combes
** Last update Sat Apr 21 01:34:48 2012 valentin combes
*/

#ifndef __RBUFFER_H__
# define __RBUFFER_H__

char	*check_rbuffer(char *buf, int *wc, int *rc);
char	*rotative_buffer(char *buf, int *wc, int *rc, int fd);

#endif
