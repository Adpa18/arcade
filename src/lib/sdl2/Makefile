BASE		=   ../../../

SRC			=	Sdl2.cpp	\

DEP_SRC		=	$(BASE)src/AComponent.cpp		\
				$(BASE)src/AGame.cpp			\
				$(BASE)src/GameComponent.cpp	\
				$(BASE)src/TextComponent.cpp	\
				$(BASE)src/UIComponent.cpp		\
				$(BASE)src/Vector2.cpp			\


CC			=	g++ -std=gnu++11

RM			=	rm -rf

NAME		=	$(BASE)lib/lib_arcade_sld2.so

CPPFLAGS	=	-W -Wall -Wextra -Werror -fPIC -w -g

CPPFLAGS	+=	-I$(BASE)inc/lib/sdl2/ -I$(BASE)inc/

CPPFLAGS	+= -D_REENTRANT

LIBS 		=	-lSDL2 -lSDL2_image -lSDL2_ttf -lpthread

LDFLAGS		=	-shared

OBJDIR		=	$(BASE)obj

OBJ			=	$(SRC:%cpp=%o)

DEP			=	$(DEP_SRC:%cpp=%o)

%.o : %.cpp
	@echo -e "Compiling $<"
	@$(CC) -c $(CPPFLAGS) $< -o $@

all		:	$(NAME)

$(NAME)	:	$(OBJ)
	@$(CC) $(LDFLAGS) $(OBJ) -o $(NAME) $(LIBS)
	@echo -e "\033[33mlib_arcade_sdl2.so Compiled\033[00m"

clean	:
	$(RM) $(OBJ)

fclean	:	clean
	$(RM) $(NAME)

re		:	fclean all

.PHONY  : all clean fclean re
