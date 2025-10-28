NAME		= philo
SRC_FILES	= main.c utils.c
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
	@rm -rf $(OBJ) $(BONUS_OBJ)

fclean: clean
	@rm -rf $(NAME) $(BONUS_NAME)

re: fclean all bonus

.PHONY: all clean fclean re