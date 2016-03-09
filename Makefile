SRC_DIR		=	src/

SRC=	$(SRC_DIR)Arcade.cpp								\
			$(SRC_DIR)Vector2.cpp								\
			$(SRC_DIR)AComponent.cpp						\
			$(SRC_DIR)GameComponent.cpp					\
			$(SRC_DIR)UIComponent.cpp						\

CC			=	g++

RM			=	rm -rf

NAME		=	arcade

CPPFLAGS	=	-g -W -Wall -Wextra -Werror -fPIC
CPPFLAGS	+=	-I./inc/

LFLAGS		=	-ldl

OBJ			=	$(SRC:%cpp=%o)

%.o : %.cpp
	@echo -e "Compiling $<"
	@$(CC) -c $(CPPFLAGS) $< -o $@

all		:	$(NAME)
	@echo -e "\033[32mCompiling Arcade\033[00m"
	@mkdir -p lib
	@mkdir -p games
	@make --no-print-directory -C $(SRC_DIR)lib
	@make --no-print-directory -C $(SRC_DIR)games
	@echo -e "\033[33mArcade Compiled\033[00m"

$(NAME)	:	$(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(LFLAGS)

clean	:
	@echo -e "\033[31mRemoving Objects\033[00m"s
	@$(RM) $(OBJ)
	@make clean -s -C $(SRC_DIR)lib
	@make clean -s -C $(SRC_DIR)games

fclean	:	clean
	@echo -e "\033[31mRemoving ${NAME}\033[00m"
	@$(RM) $(NAME)
	@make fclean -s -C $(SRC_DIR)lib
	@make fclean -s -C $(SRC_DIR)games

re		: fclean all

.PHONY	: all clean fclean re
