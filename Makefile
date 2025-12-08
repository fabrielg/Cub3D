.PHONY: all clean fclean re bonus

NAME			= cub3d.exe
CC				= cc
CFLAGS			= -Wall -Wextra -Werror

CUB3D_DIR		= cub3d/
CUB3D_BONUS_DIR	= cub3d_bonus/

OBJ_DIR			= obj
OBJ_DIR_MANDA	= $(OBJ_DIR)/manda
OBJ_DIR_BONUS	= $(OBJ_DIR)/bonus
OBJ_DIR_TARGET	= $(OBJ_DIR_MANDA)



MAIN			= $(CUB3D_DIR)main.c
SRCS_COMMUN		=

SRCS			= $(MAIN) $(SRCS_COMMUN)

SRC_FILES		= $(notdir $(SRCS))
OBJS			= $(addprefix $(OBJ_DIR_TARGET)/,$(SRC_FILES:.c=.o))



all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[32m[OK]\033[0m Build $(NAME)"

$(OBJ_DIR_MANDA)/%.o: $(CUB3D_DIR)%.c
	@mkdir -p $(OBJ_DIR_MANDA)
	$(CC) $(CFLAGS) -c $< -o $@



bonus:
	@$(MAKE) \
		MAIN="$(CUB3D_BONUS_DIR)main.c" \
		SRCS="$(CUB3D_BONUS_DIR)main.c $(SRCS_COMMUN)" \
		OBJ_DIR_TARGET="$(OBJ_DIR_BONUS)" \
		re

$(OBJ_DIR_BONUS)/%.o: $(CUB3D_BONUS_DIR)%.c
	@mkdir -p $(OBJ_DIR_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@



clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
