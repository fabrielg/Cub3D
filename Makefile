.PHONY: all clean fclean re

NAME = Cube3D
NAME_BONUS = Cube3D_bonus
CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror
MLXFLAGS = -lXext -lX11 -lm -Lminilibx-linux -lmlx_Linux

LIB = ./libft/libft.a
MLX = ./minilibx-linux/libmlx_Linux.a

SRC = \
	main.c \
	parser/parser.c \
	parser/checker.c \
	parser/debug.c

SRC_BONUS = \
	main_bonus.c

INCLUDES = -Iincludes/ -Iminilibx/ -Ilibft

SRC_DIR = src/
BONUS_DIR = src_bonus/
OBJ_DIR = obj/

OBJ			= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ_BONUS	= $(addprefix $(OBJ_DIR), $(SRC_BONUS:.c=.o))

# ========================= RULES ========================= #

all: $(NAME) $(OBJ_DIR)

bonus: $(NAME_BONUS) $(OBJ_DIR)

#Construction des libs
$(LIB):
	make -C libft/

$(MLX):
	make -C minilibx-linux/

#Création du dossier OBJ_DIR
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

#Compilation des fichiers .c en .o
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)%.o: $(BONUS_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#Création du programme
$(NAME): $(MLX) $(LIB) $(OBJ_DIR) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(MLX) -Llibft -lXext -lX11 -lft -lm
	@echo "\033[32m[OK]\033[0m Build $(NAME)"

$(NAME_BONUS): $(MLX) $(LIB) $(OBJ_DIR) $(OBJ)
	$(CC) -o $(NAME_BONUS) $(OBJ) $(MLX) -Llibft -lXext -lX11 -lft -lm
	@echo "\033[32m[OK]\033[0m Build $(NAME_BONUS)"

# ========================= CLEAN ========================= #

clean:
	rm -rf $(OBJ_DIR)
	make clean -C libft
	make clean -C minilibx-linux

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	make fclean -C libft

re: fclean all
