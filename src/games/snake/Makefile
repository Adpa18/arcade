SRC			=	Snake.cpp \

BASE		=	../../../

CC			=	g++ -std=gnu++11

RM			=	rm -rf

NAME		=	$(BASE)games/lib_arcade_snake.so

CPPFLAGS	=	-W -Wall -Wextra -Werror -fPIC

CPPFLAGS	+= 	-I$(BASE)inc/games/snake/ -I$(BASE)inc/

LDFLAGS		=	-shared

OBJ			=	$(SRC:%cpp=%o)

%.o : %.cpp
	@echo -e "Compiling $<"
	@$(CC) -c $(CPPFLAGS) $< -o $@

all		:	$(NAME)

$(NAME)	:	$(OBJ)
	@$(CC) $(LDFLAGS) $(OBJ) -o $(NAME)
	@echo -e "\033[33mlib_arcade_snake.so Compiled\033[00m"

clean	:
	$(RM) $(OBJ)

fclean	:	clean
	$(RM) $(NAME)

re		:	fclean all

.PHONY	: all clean fclean re
