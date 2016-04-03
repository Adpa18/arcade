SUBDIRS	=	snake 		\
			Pacman 		\
			qix			\
			centipede	\
			solar_fox	\

all		:
	@echo -e "\033[32m=> Compiling Games\033[00m"
	@for dir in $(SUBDIRS); do \
		echo -e "\t\033[32mCompiling $$dir\033[00m"; \
		make -C $$dir; \
	done

clean	:
	@echo -e "\033[35m=> Removing Games Objects\033[00m"
	@for dir in $(SUBDIRS); do \
		echo -e "\t\033[31mRemoving Objects from $$dir\033[0m"; \
		make -C $$dir clean; \
	done

fclean	:
	@echo -e "\033[35m=> Removing Games\033[00m"
	@for dir in $(SUBDIRS); do \
		echo -e "\t\033[31mRemoving $$dir\033[0m"; \
		make -C $$dir fclean; \
	done

re		: fclean all

.PHONY	: all clean fclean re
