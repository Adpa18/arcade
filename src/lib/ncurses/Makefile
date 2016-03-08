SRC=			Window.cpp \

BASE=     ../../../

CC=				g++

RM=				rm -rf

NAME=			$(BASE)lib/lib_arcade_ncurses.so

CPPFLAGS= -W -Wall -Wextra -Werror -fPIC -I$(BASE)inc/lib/ncurses/ -I$(BASE)inc/

LDFLAGS=  -shared

OBJ=       $(SRC:.cpp=.o)


all: $(NAME)

$(NAME):   $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY  : all clean fclean re
