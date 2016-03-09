SRC=			Ncurses.cpp \
					Window.cpp	\
					../../../src/Vector2.cpp

DEP_SRC=			../../../src/Vector2.cpp

BASE=     ../../../

CC=				g++

RM=				rm -rf

NAME=			$(BASE)lib/lib_arcade_ncurses.so

CPPFLAGS= -W -Wall -Wextra -Werror -fPIC -I$(BASE)inc/lib/ncurses/ -I$(BASE)inc/ -I/usr/include/ncurses6/ncurses -I/usr/include/ncurses6

LDFLAGS=  -shared

OBJ=       $(SRC:.cpp=.o)

DEP=       $(DEP_SRC:.cpp=.o)


all: $(NAME)

$(NAME):   $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(NAME) -lncurses -ltinfo -lncurses -ltinfo -L/usr/lib64/ncurses6

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY  : all clean fclean re
