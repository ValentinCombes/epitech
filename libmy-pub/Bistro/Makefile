##
## Makefile for makefile in /home/barre-_t//hl/piscine/eval_expr
## 
## Made by thibault barre-villeneuve
## Login   <barre-_t@epitech.net>
## 
## Started on  Wed Oct 20 22:51:59 2010 thibault barre-villeneuve
## Last update Tue Feb  5 03:36:15 2013 
##

NAME	=	calc

SRC	=	main.c			\
		gestion_op.c		\
		my_op.c			\
		my_op_particular.c	\
		analyse_string.c	\
		syntaxe.c		\
		parenteses.c		\
		str.c			\
		my_itoa.c		\
		eval_expr.c		\
		my_abs.c		\
		inf_add.c		\
		inf_sous.c		\
		inf_mult.c		\
		for_div.c		\
		inf_div.c		

OBJ	=	$(SRC:.c=.o)

TEMP	=	*~ \#*\#

CC	=	cc -o

RM	=	rm -rf

LIB	=	-L . -lmy


all	:
	$(CC) $(NAME) $(SRC) $(LIB)

clean	:
	$(RM) $(NAME)
	$(RM) *.o
	$(RM) $(TEMP)
