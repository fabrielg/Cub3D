.PHONY: all clean fclean re

NAME			= cub3d
CC				= cc
CFLAGS			= -Wall -Wextra -Werror

LIBFT_DIR		= libft/
MINILIBX_DIR	= minilibx-linux/
LIBFT			= $(LIBFT_DIR)libft.a
MINILIBX		= $(MINILIBX_DIR)libmlx.a
INCLUDES		= -I includes/ -I $(LIBFT_DIR) -I $(MINILIBX_DIR)

CUB3D_DIR		= src/
CUB3D_BONUS_DIR	= src_bonus/

OBJ_DIR			= obj
OBJ_DIR_MANDA	= $(OBJ_DIR)/manda/
OBJ_DIR_BONUS	= $(OBJ_DIR)/bonus/
OBJ_DIR_TARGET	= $(OBJ_DIR_MANDA)



MAIN			= $(CUB3D_DIR)main.c
SRCS_COMMUN		=

SRCS			= $(MAIN) $(SRCS_COMMUN)

SRC_FILES		= $(notdir $(SRCS))
OBJS			= $(addprefix $(OBJ_DIR_TARGET),$(SRC_FILES:.c=.o))



all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBFT) $(MINILIBX) -lX11 -lXext -lm
	@echo "\033[32m[OK]\033[0m Build $(NAME)"

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MINILIBX):
	make -C $(MINILIBX_DIR)

$(OBJ_DIR_MANDA)%.o: $(CUB3D_DIR)%.c
	@mkdir -p $(OBJ_DIR_MANDA)
	$(CC) $(CFLAGS) $(INCLUDES) -O3 -c $< -o $@



clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MINILIBX_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all
