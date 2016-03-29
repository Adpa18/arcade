BASE		=   ../../../

SRC			=	OpenGL.cpp	\

DEP_SRC		=	$(BASE)src/AComponent.cpp		\
						$(BASE)src/GameComponent.cpp	\
						$(BASE)src/BackgroundComponent.cpp	\
						$(BASE)src/UIComponent.cpp		\

CC			=	g++ -std=gnu++11

RM			=	rm -rf

NAME		=	$(BASE)lib/lib_arcade_openGL.so

CPPFLAGS	=	-W -Wall -Wextra -Werror -fPIC -w -g

CPPFLAGS	+=	-I$(BASE)inc/lib/openGL/ -I$(BASE)inc/

CPPFLAGS	+= 	-I$(BASE)library/sdl2/include -I$(BASE)library/openGL/include

CPPFLAGS	+=	-D_REENTRANT

LIBS 		=	-lSDL2 -lSDL2_image -lSDL2_ttf -lpthread -lGL -lGLU

LIBS 		+= 	-L$(BASE)library/sdl2 -L$(BASE)library/openGL

LDFLAGS		=	-shared -z defs

OBJDIR		=	$(BASE)obj

OBJ			=	$(SRC:%cpp=%o)

DEP			=	$(DEP_SRC:%cpp=%o)

%.o : %.cpp
	@echo -e "Compiling $<"
	@$(CC) -c $(CPPFLAGS) $< -o $@

all		:	$(NAME)

$(NAME)	:	$(OBJ) $(DEP)
	@$(CC) $(LDFLAGS) $(OBJ) $(DEP) -o $(NAME) $(LIBS)
	@echo -e "\033[33mlib_arcade_openGL.so Compiled\033[00m"

clean	:
	$(RM) $(OBJ)

fclean	:	clean
	$(RM) $(NAME)

re		:	fclean all

.PHONY  : all clean fclean re
