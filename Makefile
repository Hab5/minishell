.PHONY: all, $(NAME), clean, fclean, re

NAME = minishell

NOC=\033[0m
OKC=\033[32m
ERC=\033[31m
WAC=\033[33m

cc = gcc
C_FLAGS = -Wall -Wextra -Werror -g3
FRAM =

OBJ_PATH = ./obj/
LFT_PATH = ./libft/
INC_PATH = ./include/
SRC_PATH = ./srcs/

OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = minishell.h
SRC_NAME = builtins.c env.c exec.c get_next_line.c main.c parser.c utils.c

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
		@echo
		@make -C $(LFT_PATH)
		@$(CC) -o $(NAME) -L $(LFT_PATH) -lft $^ -o $@
		@echo "\033[32mMinishell ready.\033[0m"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		@mkdir -p $(OBJ_PATH) 2> /dev/null || true
		@$(CC) $(C_FLAGS) $(INC) -o $@ -c $<
		@echo -n =

clean:
		@make -C $(LFT_PATH) clean
		@rm -rf $(OBJ_PATH)
		@echo "\033[32mDeleting [./obj] directory.\033[0m"

fclean: clean
		@make -C $(LFT_PATH) fclean
		@rm -f $(NAME)
		@echo "\x1b[31mSUCESSFULLY CLEANED MINISHELL\x1b[31m"

re: fclean all
