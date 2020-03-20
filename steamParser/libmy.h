/*
** libmy.h for libmy in /home/valentin/Projets_persos/libmy
** 
** Made by valentin combes
** Login   <combes_v@epitech.net>
** 
** Started on  Tue Feb 22 11:14:04 2011 valentin combes
** Last update Tue Feb  5 06:48:09 2013 
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

# define COMP		1

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
int	my_strscmp(char *s1, char *s2);
char	*my_strscreat(char *str);

/*	in my_strcpy.c		*/
void	my_strcpy(char *, char *);
void	my_strncpy(char *, char *, int);
void	my_epurcpy(char *, char *);
char	*my_epurstr(char *);

/*	in my_strcmp.c		*/
int	my_strcmp(char *, char *);
int	my_strncmp(char *, char *, int);
int	my_strsncmp(char *s1, char *s2, int size);
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
void	my_putnnbr(int, int, int);
void	my_manalyse(char *, int, va_list, int);

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
char	*concatls(t_ls *, char *);

/*	in commands.c	*/
void	look_for_variable(int, char *, va_list, int *);
t_ls	*fill_ls(char *, struct dirent *, struct stat, t_ls *);
void	print_ls(t_ls *, int, int);
void	my_ls_print(t_ls *, char *, char *);
void	*my_ls(char *, int, char *);

/*	in line_aff.c	*/
void	non_canon_mode();
void	canon_mode();
int	my_promptlen(char *prompt);
void	aff_buffer(char *, char *, int, int);
void    my_clear();

/*	in line_history.c	*/
void	add_in_history(char *, int);
void	clean_tmp_history();
t_hist	*get_history_pointer();
void	free_history();

/*	in line_history2.c	*/
t_hist	*go_up_in_history(t_hist *, char *, int *, int *);
t_hist	*go_down_in_history(t_hist *, char *, int *, int *);
void	dump_history();

/*	in line_search.c	*/
void	line_search(char *, int *, int *);
void	add_in_search(char *);
void	remove_from_search(char *);

/*	in line_edit.c	*/
void	longest_cut(char *, char *);
char	*line_edit(int, char *);

/*	in my_sprintf.c	*/
char	*my_fanalyse(char *, int, va_list, char *, int *);
char	*scolor_in_str(char *, int);
char	*my_sprintf(char *, ...);

/*	in tab_aff_utils.c	*/
void    aff_border();
void	tab_void_line(int, int, int);
void	aff_strline(int, int, int, char *);
void	aff_nbrline(int, int, int, int);

/*	in tab_aff.c	*/
void	aff_tab_head(char *, t_tab **, int, int);
void	aff_line_of_tab(char *, t_tab **, int, int);
void	aff_the_tab(char *, t_tab **, int);
void	tab_aff(char *, ...);

#define	OP_OPEN_PARENT_IDX	0
#define	OP_CLOSE_PARENT_IDX	1
#define	OP_PLUS_IDX		2
#define	OP_SUB_IDX		3
#define	OP_NEG_IDX		3
#define OP_MULT_IDX		4
#define OP_DIV_IDX		5
#define OP_MOD_IDX		6
#define OP_POW_IDX		7

#define	SYNTAXE_ERROR_MSG	"syntax error"

typedef struct	s_limits
{
  int		left;
  int		right;
}		t_limits;

typedef struct	s_div
{
  char		*nb1;
  char		*nb2;
  char		*base;
  char		*tmp;
  int		i;
}		t_div;

typedef struct	s_mul
{
  char	*base;
  int	size_base;
  int	p1;
  int	p2;
  int	len_1;
  int	len_2;
  int	nb1;
  int	nb2;
}		t_mul;

/*	in bistro.c	*/
int	find_pos(char *base, char c);
int	analyse(char *str, char *ops, char *base, int *level_paren);
int	syntax_error_paren(char *str, char *ops, char *base);
int	syntax_error_character(char *str, char *base, char *ops);
int	syntax_error(char *str, char *base, char * ops);
int	str_contain_operator(char *str, char *ops);
int	max_level_paren(char *str, char *ops);
char	*my_remove(char *str, int min, int max, char *ops);
void	replace_borne(char *str1, t_limits *lim, char *ops);
int	find_size_replace(char *str1, char *str2, int left, int right);
char	*my_replace(char *str1, char *str2, t_limits lim, char *ops);
int	c_contain_operator(char c, int ordre, int counter, char *ops);
char	*my_do_op(char *str, int *counter, char *base, char *ops);
char	*my_eval_expr(char *str, char *base, char *ops);
char	*eval_paren(char *str, char *ops, char *base);
char	*eval_expr(char *base, char *ops, char *str, unsigned int size);
char	*my_revstr(char *str);
char	*bistro(char *);
char	*epur_nbr_begin(char *nbr, t_limits limite, int position, char *ops);

/*	in analyse_string.c	*/
char	*epur_nbr_end(char *str, t_limits limite, int pos_op, char *ops);
char	*remove_leading_zero(char **str, char *base, char *ops);
t_limits	pos_number(char *str, int pos, char *base, char *ops);
int	is_bigger(char *nb1, char *nb2, char *base);
char	*inf_sous_order(char *nb1, char *nb2, char *base, char *ops);

/*	in for_div.c	*/
int	my_strdivcmp(char *str1, char *str2);
char	*my_strdivcpy(char *str1, int n, int i, int s);
char	*my_strdivcpy2(char *str1, char *str2);
char	*malloc_resultat(char *resultat, char *str1, char *str2);

/*	in inf_add.c	*/
int	define_pos2(int cnt, char *base, char *nb2);
void	define_pos_add_and_ret(int *pos_add, char *base, int *ret);
void	swap_char(char **res, char **nb1, char **nb2);
char	*inf_add(char *nb1, char *nb2, char *base);

/*	in inf_div.c	*/
char	*calc_one(t_div *ptr, char a, char *n, char *resultat);
char	*calc_two(t_div *ptr, char a, char *resultat, char n);
struct s_div	*init_struct_div(char *st1, char *st2, char *base, t_div *ptr);
char	*inf_div(char *st1, char *st2, char *base);

/*	in inf_modulo.c	*/
char	*inf_modulo(char *nb1, char *nb2, char *base, char *ops);

/*	in inf_mult.c	*/
int	char_to_int(char *base, char c);
char	*initialise_res_and_r(char *res, int **r, int size);
char	*finish(t_mul *ptr, char *res, int *r, int len_2);
struct	s_mul *init_struct(t_mul *ptr, char *base, char *n1, char *n2);
char	*inf_mult(char *nb1, char *nb2, char *base);

/*	in inf_sous.c	*/
char	def_pos2(char *base, char *str2, int pos);
int	modif(char *str1, char *str2, char **resultat);
char	*inf_sous(char *str1, char *str2, char *base);

/*	in my_op.c	*/
char	*my_mult(char *str, int counter, char *base, char *ops);
char	*my_add(char *str, int counter, char *base, char *ops);
char	*my_sous(char *str, int counter, char *base, char *ops);
char	*my_modulo(char *str, int counter, char *base, char *ops);
char	*my_div(char *str, int counter, char *base, char *ops);

/*	in my_op_particular.c	*/
char	*my_add_particular(char *nb1, char *nb2, char *base, char *ops);
char	*my_sous_particular(char *nb1, char *nb2, char *base, char *ops);
char	*my_mult_particular(char *str1, char *str2, char *base, char *ops);
char	*my_div_particular(char *str1, char *str2, char *base, char *ops);

/*	in my_abs.c	*/
void	add_sign(char **str, char sign);
void	my_abs(char **str, int sens, char *ops);


#endif
