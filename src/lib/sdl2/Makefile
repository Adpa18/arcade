BASE		=   ../../../

SRC			=	Sdl2.cpp	\

DEP_SRC		=	$(BASE)src/AComponent.cpp			\
				$(BASE)src/GameComponent.cpp		\
				$(BASE)src/BackgroundComponent.cpp	\
				$(BASE)src/UIComponent.cpp			\
				$(BASE)src/UIAdvanceComponent.cpp	\
				$(BASE)src/HighScoreComponent.cpp 	\
				$(BASE)src/LoadHighScore.cpp	 	\

CC			=	g++ -std=gnu++11

RM			=	rm -rf

NAME		=	$(BASE)lib/lib_arcade_sdl2.so

CPPFLAGS	=	-W -Wall -Wextra -Werror -fPIC -w

CPPFLAGS	+=	-I$(BASE)inc/lib/sdl2/ -I$(BASE)inc/

CPPFLAGS	+= 	-I$(BASE)library/sdl2/include -D_REENTRANT

LIBS 		=	-lSDL2 -lSDL2_image -lSDL2_ttf -lpthread

LIBS 		+= 	-L$(BASE)library/sdl2

LDFLAGS		=	-shared -z defs

OBJDIR		=	$(BASE)obj

OBJ			=	$(SRC:%cpp=%o)

DEP			=	$(DEP_SRC:%cpp=%o)

%.o : %.cpp
	@echo -e "Compiling $<"
	@$(CC) -c $(CPPFLAGS) $< -o $@

$(NAME)	:	$(OBJ) $(DEP)
	@$(CC) $(LDFLAGS) $(OBJ) $(DEP) -o $(NAME) $(LIBS)
	@echo -e "\033[33mlib_arcade_sdl2.so Compiled\033[00m"

all		:	$(NAME)

clean	:
	$(RM) $(OBJ)

fclean	:	clean
	$(RM) $(NAME)

re		:	fclean all

.PHONY  : all clean fclean re
