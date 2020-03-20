##
## Makefile for rt in /home/combes_v//Proj/rt
## 
## Made by valentin combes
## Login   <combes_v@epitech.net>
## 
## Started on  Tue Mar 29 09:36:59 2011 valentin combes
## Last update Tue Apr 23 09:06:09 2013 
##

NAME=	libmy.a

SRC=	my_put.c		\
	my_strcat.c		\
	my_strcpy.c		\
	my_strcmp.c		\
	my_get_nbr.c		\
	xmalloc.c		\
	get_next_line.c		\
	my_str_to_wordtab.c	\
	xwrite.c		\
	my_printf.c		\
	my_putwarn.c		\
	my_puttime.c		\
	my_ls_class.c		\
	my_ls_getnames.c	\
	my_ls_rights.c		\
	concat_ls.c		\
	my_ls.c			\
	commands.c		\
	line_aff.c		\
	line_history.c		\
	line_history2.c		\
	line_search.c		\
	line_edit.c		\
	my_sprintf.c		\
	tab_aff.c		\
	tab_aff_utils.c		

MAIN=	main_test.c

OBJ=	$(SRC:.c=.o)

CFLAGS=	-W -Wall -Wextra

LIBS=	-lcurses

all:	$(OBJ)
	ar -r $(NAME) $(OBJ)
	ranlib $(NAME)

tf:	
	cc -o test $(MAIN) charizard.c -L. -lmy $(LIBS) -W -Wall -Wextra -ansi -pedantic -std=gnu99

clean:	
	rm -rvf $(OBJ)
	rm -rvf $(OBJ2)
	rm -rvf *~

fclean:	clean
	rm -rvf $(NAME)
	rm -rvf test

re:	fclean all
