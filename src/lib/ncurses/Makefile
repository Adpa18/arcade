BASE		=   ../../../

SRC			=	Ncurses.cpp	\
				Window.cpp	\

DEP_SRC		=	$(BASE)src/AComponent.cpp		\
						$(BASE)src/GameComponent.cpp	\
						$(BASE)src/UIComponent.cpp	\
						$(BASE)src/AudioComponent.cpp		\
						$(BASE)src/UIAdvanceComponent.cpp		\

CC			=	g++ -std=gnu++11

RM			=	rm -rf

NAME		=	$(BASE)lib/lib_arcade_ncurses.so

CPPFLAGS	=	-g -W -Wall -Wextra -Werror -fPIC

CPPFLAGS	+=	-I$(BASE)inc/lib/ncurses/ -I$(BASE)inc/

CPPFLAGS	+=	-I/usr/include/ncurses6/ncurses -I/usr/include/ncurses6

LIBS 		=	-lncurses -ltinfo -lncurses -ltinfo -L/usr/lib64/ncurses6

LDFLAGS		=	-shared

OBJDIR		=	$(BASE)obj

OBJ			=	$(SRC:%cpp=%o)

DEP			=	$(DEP_SRC:%cpp=%o)

%.o : %.cpp
	@echo -e "Compiling $<"
	@$(CC) -c $(CPPFLAGS) $< -o $@

all		:	$(NAME)

$(NAME)	:	$(OBJ) $(DEP)
	@$(CC) $(LDFLAGS) $(OBJ) $(DEP) -o $(NAME) $(LIBS)
	@echo -e "\033[33mlib_arcade_ncurses.so Compiled\033[00m"

clean	:
	$(RM) $(OBJ)

fclean	:	clean
	$(RM) $(NAME)

re		:	fclean all

.PHONY  : all clean fclean re
