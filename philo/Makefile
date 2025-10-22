NAME		= philo
BONUS_NAME	= philo_bonus
SRC_FILES	= main.c
BONUS_FILES	= main_bonus.c
SRC_DIR		= src
BONUS_DIR	= $(SRC_DIR)/bonus
SRC			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
BONUS_SRC	= $(addprefix $(BONUS_DIR)/, $(BONUS_FILES))
OBJ_DIR		= $(SRC_DIR)/obj
B_OBJ_DIR	= $(BONUS_DIR)/obj
OBJ			= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
BONUS_OBJ	= $(patsubst $(BONUS_DIR)/%.c,$(B_OBJ_DIR)/%.o,$(BONUS_SRC))
CFLAGS		= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "Compilation successful. Created $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ)
	@$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(BONUS_NAME)
	@echo "Compilation successful. Created $(BONUS_NAME)"

$(B_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c | $(B_OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(B_OBJ_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJ) $(BONUS_OBJ)

fclean: clean
	@rm -rf $(NAME) $(BONUS_NAME)

re: fclean all bonus

.PHONY: all clean fclean re