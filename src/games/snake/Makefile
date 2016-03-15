BASE		=   ../../../

SRC			=	Snake.cpp	\

DEP_SRC		=	$(BASE)src/AComponent.cpp		\
				$(BASE)src/AGame.cpp			\
				$(BASE)src/GameComponent.cpp	\
				$(BASE)src/TextComponent.cpp	\
				$(BASE)src/UIComponent.cpp		\
				$(BASE)src/Vector2.cpp			\

CC			=	g++ -std=gnu++11

RM			=	rm -rf

NAME		=	$(BASE)games/lib_arcade_snake.so

CPPFLAGS	=	-W -Wall -Wextra -Werror -fPIC -g

CPPFLAGS	+= 	-I$(BASE)inc/games/snake/ -I$(BASE)inc/

LDFLAGS		=	-shared

OBJ			=	$(SRC:%cpp=%o)

DEP			=	$(DEP_SRC:%cpp=%o)

%.o : %.cpp
	@echo -e "Compiling $<"
	@$(CC) -c $(CPPFLAGS) $< -o $@

all		:	$(NAME)

$(NAME)	:	$(OBJ) $(DEP)
	@$(CC) $(LDFLAGS) $(OBJ) $(DEP) -o $(NAME)
	@echo -e "\033[33mlib_arcade_snake.so Compiled\033[00m"

clean	:
	$(RM) $(OBJ)

fclean	:	clean
	$(RM) $(NAME)

re		:	fclean all

.PHONY	: all clean fclean re
