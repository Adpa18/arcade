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

CPPFLAGS= -W -Wall -Wextra -Werror -I./inc/

OBJ=  $(SRC:.cpp=.o)


all: $(NAME)
	$(MAKE) -C ./src/lib/ MAKEFLAGS=

$(NAME):   $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
	
clean:
	$(RM) $(OBJ)
	$(MAKE) clean -C ./src/lib/ MAKEFLAGS=

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C ./src/lib/ MAKEFLAGS=

re: fclean all
