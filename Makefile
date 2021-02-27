MLX = -lmlx -lm -lX11 -lXext -lbsd

NAME = cub3D

SRCS = cub3d.c \
		utils/bitmap.c \
		utils/calculations.c \
		utils/ceiling_floor.c \
		utils/check_content.c \
		utils/ft_is_whitespace.c \
		utils/get_next_line.c \
		utils/putstr_info_cmd.c \
		utils/shapes.c \
		srcs/init_game.c \
		srcs/description/color_from_string.c \
		srcs/description/map_from_string.c \
		srcs/description/path_from_string.c \
		srcs/description/treat_description.c \
		srcs/description/window_size_from_string.c \
		srcs/engine/draw_sprite.c \
		srcs/engine/image.c \
		srcs/engine/minimap.c \
		srcs/engine/player.c \
		srcs/engine/raycasting_one.c \
		srcs/engine/raycasting_two.c \
		srcs/engine/sprite.c \
		srcs/engine/textures.c \
		srcs/managers/key_manager.c \
		srcs/managers/loop_manager.c \
		srcs/managers/window_manager.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	@echo "\033[33m[Remove last version...]\033[0m"
	@rm -rf cub3D
	@echo "\033[33m[Libft compilation...]\033[0m"
	@$(MAKE) bonus -C ./libft
	@echo "\033[33m[cub3D compilation...]\033[0m"
	@clang -g $(OBJS) -I./includes -I./usr/include -Wall -Wextra -Werror $(MLX) ./libft/libft.a -o $(NAME)
	@echo "\033[33m[Done !]\033[0m"

all: $(NAME)

clean:
	rm -rf $(OBJS)
	$(MAKE) clean -C ./libft

fclean: clean
	rm -rf $(NAME)
	rm -rf cub3D.bmp
	$(MAKE) fclean -C ./libft

re: fclean all

bonus: all