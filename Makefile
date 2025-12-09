.PHONY: all clean fclean re

NAME			= cub3d
CC				= cc
CFLAGS			= -Wall -Wextra -Werror
LIBFT			= ./libft/libft.a
MINILIBX		= ./minilibx-linux/libmlx.a

CUB3D_DIR		= src/
CUB3D_BONUS_DIR	= src_bonus/

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

$(NAME): $(LIBFT) $(MINILIBX) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MINILIBX) -lX11 -lXext -lm
	@echo "\033[32m[OK]\033[0m Build $(NAME)"

$(LIBFT):
	make -C ./libft/

$(MINILIBX):
	make -C ./minilibx-linux/

$(OBJ_DIR_MANDA)/%.o: $(CUB3D_DIR)%.c
	@mkdir -p $(OBJ_DIR_MANDA)
	$(CC) $(CFLAGS) -Imlx -O3 -c $< -o $@



clean:
	@make clean -C ./libft/
	@make clean -C ./minilibx-linux/
	rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C ./libft/
	rm -f $(NAME)

re: fclean all
