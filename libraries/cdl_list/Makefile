#Colors
DEFAULT = \033[0;39m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m

SOURCES_DIR = sources/
FILES =		cdl_listaddback.c \
			cdl_listaddfront.c \
			cdl_listclear.c \
			cdl_listdecr.c \
			cdl_listdelnode.c \
			cdl_listgetnode.c \
			cdl_listincr.c \
			cdl_listinit.c \
			cdl_nodenew.c
SOURCES = $(addprefix $(SOURCES_DIR), $(FILES))
OBJECTS_DIR = objects/
OBJECTS = $(addprefix $(OBJECTS_DIR), $(FILES:.c=.o))

CFLAGS = -g -Wall -Wextra -Werror
CC = gcc
NAME = cdl_list.a

all: $(OBJECTS_DIR) $(NAME) 

$(NAME): $(OBJECTS) 
	@echo "compiling: $(YELLOW)creating library$(DEFAULT)"
	@ar -rc $@ $^
	@echo "$(GREEN)$@ successfully compiled!$(DEFAULT)"

$(OBJECTS_DIR):
	@mkdir objects

$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.c
	@echo "compiling: $(YELLOW)$@$(DEFAULT)"
	@$(CC) -c $(CFLAGS) -o $@ $^

clean:
	@echo "cleaning:  $(RED)removing $(NAME) object files$(DEFAULT)"
	@rm -f $(OBJECTS)

rmlib:
	@echo "cleaning:  $(RED)removing $(NAME)$(DEFAULT)"
	@rm -f $(NAME)

fclean: clean rmlib
	

re: fclean all

.PHONY: all clean fclean re bonus
