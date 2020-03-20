/*
** libmy.h for libmy in /home/valentin/Projets_persos/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Tue Feb 22 11:14:04 2011 valentin combes
** Last update Sat May 12 14:03:38 2012 valentin combes
*/

#ifndef	__LIBMY_H__
# define __LIBMY_H__

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdarg.h>
# include <dirent.h>

# include <pwd.h>
# include <grp.h>
# include <time.h>

# include <curses.h>
# include <term.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>

#define	COMP		1

# define WHITE		0
# define BLACK		30
# define RED		31
# define GREEN		32
# define YELLOW		33
# define BLUE		34
# define CYAN		36
# define GREY		37
# define BOLDGREY	130

# define BOLD		1
# define UNDERLINE	4
# define BLINK		5
# define HIGHLIGHT	7

# define STRING		0
# define LIST		1
# define PRINT		2

# define BUFSIZE	1024
# define INTERRUPT	'\n'

typedef	struct		s_history
{
  int			tmp;
  char			*line;
  struct s_history	*prev;
  struct s_history	*next;
}			t_hist;

typedef	struct		s_lslist
{
  char			rights[11];
  int			nlink;
  char			*uname;
  char			*gname;
  int			size;
  char			*time;
  char			*name;
  struct s_lslist	*next;
  struct s_lslist	*prev;
}			t_ls;

typedef	struct		s_tab
{
  char			*title;
  void			*data;
  int			size;
}			t_tab;

/*	in my_put.c		*/
void	my_putchar(int, char);
void	my_put_nbr(int, int);
void	my_put_nbr_double(int, double);
void	my_put_nbr_base(int, int, char *);
void	my_putstr(int, char *);

/*	in my_strcat.c		*/
char	*my_strcat(char *, char *);
char	*my_strncat(char *, char *, int);
char	*my_strcreat(char *);
int	my_isalphanum(char);

/*	in my_strcpy.c		*/
void	my_strcpy(char *, char *);
void	my_strncpy(char *, char *, int);
void	my_epurcpy(char *, char *);
char	*my_epurstr(char *);

/*	in my_strcmp.c		*/
int	my_strcmp(char *, char *);
int	my_strncmp(char *, char *, int);
int	my_strstr(char *, char *);

/*	in my_get_nbr.c		*/
int	my_strlen(char *);
double	my_get_nbr(char *);
int	my_get_nbr_hex(char *);
int	my_basecmp(char, char *);
double	my_get_nbr_base(char *, char *);

/*	in xmalloc.c		*/
void	*xmalloc(size_t);
void	*xfree(void *);
void	*my_freetab(void **);
void	my_swap(int *, int *);
int	my_tablen(char **);

/*	in get_next_line.c	*/
int	my_linelen(char *);
char	*my_lineconcat(char *, char *, int *);
void	cpy_line(int, char *, char *, int *);
char	*init_line(char *, int *);
char	*get_next_line(int);

/*	in my_str_to_wordtab.c	*/
int	count_word(char *);
int	my_wordlen(char *, int);
void	my_wordcpy(char *, char **, int);
char	**my_str_to_wordtab(char *);
void	my_puttab(int, char **);

/*	in xwrite.c		*/
void	xwrite(int, void *, int);
void	xread(int, char *, int);
void	my_putstrspecial(int, char *);
void	my_put_space(int, int);
void	my_analyse(char *, int, va_list, int);

/*	in my_printf.c		*/
void	my_put_nbr_hex(int, int);
void	my_put_nbr_oct(int, int);
void	my_put_nbr_bin(int, int);
void	my_putnumber(int, int, char);
void	my_printf(char *, ...);

/*	in my_putwarn.c		*/
void	my_put_color(int, int);
void	my_end_color(int, int, int);
void	change_fd(int *, int, int, int);
int	my_putwarn(char *, ...);
void	my_puterror(char *, ...);

/*	in my_puttime.c		*/
void	my_puttime(int, int, int, int);
void	my_putnstr(int, int, char *);
void		my_putnnbr(int, int, int);

/*	in my_ls.c	*/
char	*add_to_line(char *, char *);
int	get_max_len_size(t_ls *);
int	get_max_len_nlink(t_ls *);
t_ls	*open_path(char *);
void	free_t_ls(t_ls *);

/*	in my_ls_rights.c	*/
char	det_type(struct stat);
int	det_user_rights(struct stat, t_ls *);
int	det_group_rights(struct stat, t_ls *);
int	det_other_rights(struct stat, t_ls *);
void	get_type_and_rights(struct stat, t_ls *);

/*	in my_ls_class.c	*/
char	*complete_nb(char *, int);
char	*my_nbr_to_nstr(int, int);
int	my_lscmp(char *, char *);
t_ls	*file_class_comp(t_ls **);
t_ls	*file_class(t_ls *);

/*	in my_ls_getnames.c	*/
char	*get_name(char *);
char	*get_grname(struct stat);
char	*get_uname(struct stat);
char	*get_time(time_t);
int	get_ls_char_val(char);

/*	in concat_ls.c	*/
char	*my_nbr_to_fullstr(int);
char	*my_nbr_to_str(int);
char	*addlsline(t_ls *, char *, int, int);
char	*concatls(t_ls *, char **);

/*	in commands.c	*/
void	look_for_variable(int, char *, va_list, int *);
t_ls	*fill_ls(char *, struct dirent *, struct stat, t_ls *);
void	print_ls(t_ls *, int, int);
void	my_ls_print(t_ls *, char **);
void	*my_ls(char *, int, char **);

/*	in line_aff.c	*/
void	non_canon_mode();
void	canon_mode();
void	aff_buffer(char *, char *, int, int);
void    my_clear();

/*	in line_history.c	*/
t_hist	*go_up_in_history(t_hist *, char *, int *, int *);
t_hist	*go_down_in_history(t_hist *, char *, int *, int *);
void	add_in_history(char *, int);
void	clean_tmp_history();
void	dump_history();
void	free_history();

/*	in line_edit.c	*/
void	longest_cut(char *, char *);
void	line_search(char *, int *, int *);
char	*line_edit(int, char *);

/*	in my_sprintf.c	*/
char	*my_fanalyse(char *, int, va_list, char *, int *);
char	*scolor_in_str(char *, int);
char	*my_sprintf(char *, ...);

/*	in tab_aff.c	*/
void	tab_aff(char *, ...);

/*	in charizard.c	*/
void	aff_charizard();

#endif
