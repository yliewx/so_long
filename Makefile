# declare makefile variables
NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# libft path and flags
LIBFT = libft.a
LIB_DIR = ./libft
LIB_FLAGS = -L $(LIB_DIR) -lft

# mlx path and flags
ifeq ($(shell uname), Linux)
	MLX_DIR = ./mlx_linux
	MLX_NAME = libmlx_Linux.a
	MLX_LIB = $(addprefix $(MLX_DIR)/, $(MLX_NAME))
	MLX_INC = -I/usr/include -I $(MLX_DIR)
	MLX_FLAGS = -L $(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11
else
	MLX_DIR = ./mlx_macos
	MLX_NAME = libmlx.dylib
	MLX_LIB = $(addprefix $(MLX_DIR)/, $(MLX_NAME))
	MLX_INC = -I/opt/X11/include -I $(MLX_DIR)
	MLX_FLAGS = -L $(MLX_DIR) -lmlx -L/usr/X11/lib -lXext -lX11 \
	-framework OpenGL -framework AppKit
endif

# so_long targets
TARGET = init_game.c init_map.c verify_map.c \
	init_sprites.c render_sprites.c render_wall.c sprite_utils.c \
	movement.c exit_utils.c message.c
SRCS = $(addprefix srcs/, $(TARGET))
BONUS_TARGET = init_game_bonus.c init_map_bonus.c verify_map_bonus.c \
	init_sprites_bonus.c render_sprites_bonus.c \
	render_wall_bonus.c sprite_utils_bonus.c \
	movement_bonus.c animation_bonus.c enemy_bonus.c \
	exit_utils_bonus.c message_bonus.c
BONUS_SRCS = $(addprefix srcs_bonus/, $(BONUS_TARGET))

# colours
GREEN = \033[0;32m
B_GREEN = \033[1;32m
BROWN = \033[0;33m
B_BROWN = \033[1;33m
END = \033[0m

# RULES
# all = create library from sub-make

all: $(MLX_LIB) $(LIBFT) mandatory

mandatory: $(SRCS) $(MLX_LIB) $(LIBFT)
	@echo "\n$(B_BROWN)[ COMPILING: $(NAME) ]$(END)"
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME) $(LIB_FLAGS) $(MLX_FLAGS) $(MLX_INC)
	@echo "$(B_GREEN)$(NAME) compiled.$(END)"

bonus: $(BONUS_SRCS) $(MLX_LIB) $(LIBFT)
	@echo "\n$(B_BROWN)[ COMPILING: $(NAME) bonus ]$(END)"
	@$(CC) $(CFLAGS) $(BONUS_SRCS) -o $(NAME) $(LIB_FLAGS) $(MLX_FLAGS) $(MLX_INC)
	@echo "$(B_GREEN)$(NAME) bonus compiled.$(END)"

$(LIBFT):
	@echo "\n$(B_BROWN)[ COMPILING: $(LIBFT) ]$(END)"
	@make -s -C $(LIB_DIR)

$(MLX_LIB):
	@echo "\n$(B_BROWN)[ COMPILING: $(MLX_LIB) ]$(END)"
	@make -s -C $(MLX_DIR)
	@cp $(MLX_LIB) ./
	@echo "$(B_GREEN)$(MLX_LIB) compiled.$(END)"

# remove temporary generated files
clean:
	@make clean -s -C $(LIB_DIR)
	@make clean -s -C $(MLX_DIR)

# remove library and executable file
fclean: clean
	@$(RM) $(NAME) && $(RM) $(MLX_NAME)
	@cd $(LIB_DIR) && $(RM) $(LIBFT)
	@echo "$(B_GREEN)Removed $(NAME), $(MLX_NAME) and $(LIBFT).$(END)"

re: fclean all

# declare phony
.PHONY: all bonus clean fclean mandatory re
