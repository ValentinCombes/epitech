NAME=	reveil

SRC=	main.c		

OBJ=	$(SRC:.c=.o)

all:	$(OBJ)
	cc -o $(NAME) $(SRC) -L. -lmy -W -Wall -Wextra -ansi -pedantic -lcurses -D_XOPEN_SOURCE=600

clean:	
	rm -rvf $(OBJ)
	rm -rvf *~
	rm -rvf \#*#

fclean:	clean
	rm -rvf $(NAME)

re:	fclean all
