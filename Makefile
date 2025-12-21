.PHONY: all clean fclean re

NAME			= cub3D
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -lm
LIBFT			= ./libft/libft.a
MINILIBX		= ./minilibx-linux/libmlx.a

CUB3D_DIR		= src/
CUB3D_BONUS_DIR	= src_bonus/

OBJ_DIR			= obj
OBJ_DIR_MANDA	= $(OBJ_DIR)/manda/
OBJ_DIR_BONUS	= $(OBJ_DIR)/bonus/
OBJ_DIR_TARGET	= $(OBJ_DIR_MANDA)



MAIN			= $(CUB3D_DIR)main.c
SRCS_COMMUN		= \
	$(CUB3D_DIR)parser/parser.c
INCLUDES = \
	-Iincludes\
	-Ilibft

SRCS			= $(MAIN) $(SRCS_COMMUN)

OBJS = $(SRCS:$(CUB3D_DIR)%.c=$(OBJ_DIR_TARGET)%.o)



all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBFT) $(MINILIBX) -lX11 -lXext -lm
	@echo "\033[32m[OK]\033[0m Build $(NAME)"

$(LIBFT):
	make -C ./libft/

$(MINILIBX):
	make -C ./minilibx-linux/

$(OBJ_DIR_TARGET)%.o: $(CUB3D_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@



clean:
	@make clean -C ./libft/
	@make clean -C ./minilibx-linux/
	rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C ./libft/
	rm -f $(NAME)

re: fclean all
