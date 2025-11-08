NAME		= philo_bonus
SRC_FILES	= main_bonus.c init_bonus.c utils_bonus.c checker_bonus.c \
				routine_bonus.c cleanup_bonus.c
SRC_DIR		= src
SRC			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ_DIR		= $(SRC_DIR)/obj
OBJ			= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
CFLAGS		= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "Compilation successful. Created $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re