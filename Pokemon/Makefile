NAME=	wop2d

SRC=	mySDL.cpp	\
	trainer.cpp	\
	map.cpp		\
	Game.cpp	\
	main.cpp

OBJ=	$(SRC:.cpp=.o)

all:	$(OBJ)
	g++ -o $(NAME) $(SRC) -W -lSDL -lSDL_image

clean:	
	rm -rvf *~
	rm -rvf $(OBJ)

fclean:	clean
	rm -rvf $(NAME)

re:	fclean all
