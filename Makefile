.PHONY: all clean fclean re bonus

NAME			= cub3d
NAME_BONUS		= cub3d_bonus
CC				= cc
CFLAGS			= -g3 -Wall -Wextra -Werror

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



MAIN			= $(CUB3D_DIR)main.c
SRCS_COMMUN_MANDA		= \
	$(CUB3D_DIR)mlx_utils/mlx_events.c \
	$(CUB3D_DIR)mlx_utils/mlx_utils.c \
	$(CUB3D_DIR)mlx_utils/mlx_draw_text.c \
	$(CUB3D_DIR)init/init_cub.c \
	$(CUB3D_DIR)init/init_window.c \
	$(CUB3D_DIR)minimap/minimap_cells.c \
	$(CUB3D_DIR)minimap/minimap_cursor.c \
	$(CUB3D_DIR)parser/check_texture_utils.c \
	$(CUB3D_DIR)parser/debug.c \
	$(CUB3D_DIR)parser/free_map.c \
	$(CUB3D_DIR)parser/check_extension.c \
	$(CUB3D_DIR)parser/grid_parser.c \
	$(CUB3D_DIR)parser/grid_checker.c \
	$(CUB3D_DIR)parser/header_parser_utils.c \
	$(CUB3D_DIR)parser/header_parser.c \
	$(CUB3D_DIR)parser/door_parser.c \
	$(CUB3D_DIR)parser/parser.c \
	$(CUB3D_DIR)player/interact.c \
	$(CUB3D_DIR)player/movement.c \
	$(CUB3D_DIR)player/player_init.c \
	$(CUB3D_DIR)render/dda_algo.c \
	$(CUB3D_DIR)render/draw.c \
	$(CUB3D_DIR)render/fps_routine.c \
	$(CUB3D_DIR)render/render_utils.c \
	$(CUB3D_DIR)render/render_texture_utils.c \
	$(CUB3D_DIR)render/render.c


MAIN_BONUS			= $(CUB3D_BONUS_DIR)main.c
SRCS_COMMUN_BONUS			= \
	$(CUB3D_BONUS_DIR)mlx_utils/mlx_events.c \
	$(CUB3D_BONUS_DIR)mlx_utils/mlx_utils.c \
	$(CUB3D_BONUS_DIR)mlx_utils/mlx_draw_text.c \
	$(CUB3D_BONUS_DIR)init/init_cub.c \
	$(CUB3D_BONUS_DIR)init/init_window.c \
	$(CUB3D_BONUS_DIR)minimap/minimap_cells.c \
	$(CUB3D_BONUS_DIR)minimap/minimap_cursor.c \
	$(CUB3D_BONUS_DIR)parser/check_texture_utils.c \
	$(CUB3D_BONUS_DIR)parser/debug.c \
	$(CUB3D_BONUS_DIR)parser/free_map.c \
	$(CUB3D_BONUS_DIR)parser/check_extension.c \
	$(CUB3D_BONUS_DIR)parser/grid_parser.c \
	$(CUB3D_BONUS_DIR)parser/grid_checker.c \
	$(CUB3D_BONUS_DIR)parser/header_parser_utils.c \
	$(CUB3D_BONUS_DIR)parser/header_parser.c \
	$(CUB3D_BONUS_DIR)parser/door_parser.c \
	$(CUB3D_BONUS_DIR)parser/parser.c \
	$(CUB3D_BONUS_DIR)player/interact.c \
	$(CUB3D_BONUS_DIR)player/movement.c \
	$(CUB3D_BONUS_DIR)player/player_init.c \
	$(CUB3D_BONUS_DIR)render/dda_algo.c \
	$(CUB3D_BONUS_DIR)render/draw.c \
	$(CUB3D_BONUS_DIR)render/fps_routine.c \
	$(CUB3D_BONUS_DIR)render/render_utils.c \
	$(CUB3D_BONUS_DIR)render/render_texture_utils.c \
	$(CUB3D_BONUS_DIR)render/render.c


SRCS			= $(MAIN) $(SRCS_COMMUN_MANDA)

OBJS			= $(SRCS:$(CUB3D_DIR)%.c=$(OBJ_DIR_MANDA)%.o)

SRCS_BONUS			= $(MAIN_BONUS) $(SRCS_COMMUN_BONUS)

OBJS_BONUS			= $(SRCS_BONUS:$(CUB3D_BONUS_DIR)%.c=$(OBJ_DIR_BONUS)%.o)



all: $(NAME)
bonus: $(NAME_BONUS)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBFT) $(MINILIBX) -lX11 -lXext -lm
	@echo "\033[32m[OK]\033[0m Build $(NAME)"

$(NAME_BONUS): $(LIBFT) $(MINILIBX) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBFT) $(MINILIBX) -lX11 -lXext -lm
	@echo "\033[32m[OK]\033[0m Build $(NAME_BONUS)"

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MINILIBX):
	make -C $(MINILIBX_DIR)

$(OBJ_DIR_MANDA)%.o: $(CUB3D_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -O3 -c $< -o $@

$(OBJ_DIR_BONUS)%.o: $(CUB3D_BONUS_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -O3 -c $< -o $@



clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MINILIBX_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all
