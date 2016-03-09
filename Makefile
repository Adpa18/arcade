SRC_DIR= ./src/

SRC=	$(SRC_DIR)Arcade.cpp								\
			$(SRC_DIR)Object.cpp								\
			$(SRC_DIR)Object2D.cpp							\
			$(SRC_DIR)Object3D.cpp							\
			$(SRC_DIR)ObjectTerm.cpp						\
			$(SRC_DIR)Vector2.cpp								\
			$(SRC_DIR)Vector3.cpp

CC=				g++

RM=				rm -rf

NAME= arcade

CPPFLAGS = -g -W -Wall -Wextra -Werror -fPIC
CPPFLAGS += -I./inc/

LFLAGS = -ldl

OBJ=  $(SRC:%cpp=%o)


all: $(NAME)
	$(MAKE) -C ./src/lib/ MAKEFLAGS=
	$(MAKE) -C ./src/games/ MAKEFLAGS=

$(NAME):   $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LFLAGS)

clean:
	$(RM) $(OBJ)
	$(MAKE) clean -C ./src/lib/ MAKEFLAGS=
	$(MAKE) clean -C ./src/games/ MAKEFLAGS=

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C ./src/lib/ MAKEFLAGS=
	$(MAKE) fclean -C ./src/games/ MAKEFLAGS=

re: fclean all
