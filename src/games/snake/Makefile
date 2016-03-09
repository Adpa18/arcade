SRC=			Snake.cpp \

BASE=     ../../../

CC=				g++

RM=				rm -rf

NAME=			$(BASE)games/lib_arcade_snake.so

CPPFLAGS= -W -Wall -Wextra -Werror -fPIC -I$(BASE)inc/games/snake/ -I$(BASE)inc/

LDFLAGS=  -shared

OBJ=       $(SRC:.cpp=.o)


all: $(NAME)

$(NAME):   $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY  : all clean fclean re
