/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:46:22 by yliew             #+#    #+#             */
/*   Updated: 2023/11/16 14:02:38 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <time.h>

/*platform-specific definitions*/

# ifdef __linux__
#  include "../mlx_linux/mlx.h"
#  define OS_LINUX 1
#  define W_KEY 119
#  define S_KEY 115
#  define A_KEY 97
#  define D_KEY 100
#  define UP_KEY 65362
#  define DOWN_KEY 65364
#  define LEFT_KEY 65361
#  define RIGHT_KEY 65363
#  define ESC 65307
# elif __APPLE__
#  include "../mlx_macos/mlx.h"
#  define OS_LINUX 0
#  define W_KEY 13
#  define S_KEY 1
#  define A_KEY 0
#  define D_KEY 2
#  define UP_KEY 126
#  define DOWN_KEY 125
#  define LEFT_KEY 123
#  define RIGHT_KEY 124
#  define ESC 53
# endif

/*image paths*/

# define WALL_UP_L_XPM "./assets/wall/up/up_L.xpm"
# define WALL_UP_M_XPM "./assets/wall/up/up_mid.xpm"
# define WALL_UP_R_XPM "./assets/wall/up/up_R.xpm"
# define WALL_DOWN_L_XPM "./assets/wall/down/down_L.xpm"
# define WALL_DOWN_M_XPM "./assets/wall/down/down_mid.xpm"
# define WALL_DOWN_R_XPM "./assets/wall/down/down_R.xpm"
# define WALL_SIDE_L_XPM "./assets/wall/side/side_L.xpm"
# define WALL_SIDE_M_XPM "./assets/wall/side/side.xpm"
# define WALL_SIDE_R_XPM "./assets/wall/side/side_R.xpm"
# define WALL_XPM "./assets/wall/blank.xpm"

# define IDLE_0_L_XPM "./assets/ducky/idle/idle_0_L.xpm"
# define IDLE_1_L_XPM "./assets/ducky/idle/idle_1_L.xpm"
# define IDLE_0_R_XPM "./assets/ducky/idle/idle_0_R.xpm"
# define IDLE_1_R_XPM "./assets/ducky/idle/idle_1_R.xpm"

# define WALK_0_L_XPM "./assets/ducky/walk/walk_0_L.xpm"
# define WALK_1_L_XPM "./assets/ducky/walk/walk_1_L.xpm"
# define WALK_2_L_XPM "./assets/ducky/walk/walk_2_L.xpm"
# define WALK_3_L_XPM "./assets/ducky/walk/walk_3_L.xpm"

# define WALK_0_R_XPM "./assets/ducky/walk/walk_0_R.xpm"
# define WALK_1_R_XPM "./assets/ducky/walk/walk_1_R.xpm"
# define WALK_2_R_XPM "./assets/ducky/walk/walk_2_R.xpm"
# define WALK_3_R_XPM "./assets/ducky/walk/walk_3_R.xpm"

# define ENEMY_0_XPM "./assets/enemy/0.xpm"
# define ENEMY_1_XPM "./assets/enemy/1.xpm"
# define ENEMY_2_XPM "./assets/enemy/2.xpm"
# define ENEMY_3_XPM "./assets/enemy/3.xpm"
# define ENEMY_4_XPM "./assets/enemy/4.xpm"
# define ENEMY_5_XPM "./assets/enemy/5.xpm"
# define ENEMY_6_XPM "./assets/enemy/6.xpm"
# define ENEMY_7_XPM "./assets/enemy/7.xpm"

# define FLOOR_XPM "./assets/floor/floor.xpm"
# define COIN_XPM "./assets/coin/egg_24.xpm"
# define EXIT_0_XPM "./assets/door/closed.xpm"
# define EXIT_1_XPM "./assets/door/open.xpm"
# define IMG_SIZE 48

/*text colour*/

# define BROWN "\033[1;33m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define RESET "\033[0m"

/*others*/

# define ON_EXPOSE 12
# define ON_DESTROY 17

/*player directions*/

enum e_direction
{
	up,
	down,
	left,
	right,
};

/*structs*/

typedef struct s_img
{
	void	*ptr;
	void	*addr;
	int		x;
	int		y;
	int		bpp;
	int		line_size;
	int		endian;
}	t_img;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_data
{
	t_pos	current;
	t_pos	prev;
	int		coins;
	int		movements;
	int		direction;
	bool	idle;
}	t_data;

typedef struct s_map
{
	char	**grid;
	char	*full_line;
	int		fd;
	int		rows;
	int		columns;
	int		start;
	int		coins;
	int		enemies;
	int		exit;
	bool	exit_found;
	bool	valid_path;
}	t_map;

typedef struct s_wall
{
	t_img	up_l;
	t_img	up_m;
	t_img	up_r;
	t_img	down_l;
	t_img	down_m;
	t_img	down_r;
	t_img	side_l;
	t_img	side_m;
	t_img	side_r;
	t_img	blank;
}	t_wall;

typedef struct s_frames
{
	t_img	idle_0;
	t_img	idle_1;
	t_img	walk_0;
	t_img	walk_1;
	t_img	walk_2;
	t_img	walk_3;
	t_img	walk_4;
	t_img	walk_5;
	t_img	walk_6;
	t_img	walk_7;
}	t_frames;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		map;
	t_data		player;
	t_data		enemy;
	t_wall		wall;
	t_frames	l;
	t_frames	r;
	t_frames	en;
	t_img		display;
	t_img		img_floor;
	t_img		img_coin;
	t_img		img_exit_0;
	t_img		img_exit_1;
	int			screen_x;
	int			screen_y;
}	t_game;

/*init_game.c*/
void	init_variables(t_game *game);
void	init_sprites(t_game *game);

/*init_map.c*/
void	open_map(t_game *game, char *map_path);
void	check_valid_map(t_game *game, t_map *map, char *line);
void	init_components(t_game *game, t_map *map, int i, int j);
void	set_pos(t_pos *subject, int x, int y);
void	set_map_params(t_map *map);

/*sprite_utils.c*/
void	check_sprite(t_game *game, int c, int x, int y);
void	get_sprite_info(t_img *sprite);
void	render_sprite(t_img *base, t_img *sprite, int x, int y);
void	render_offset(t_game *game, t_img *sprite, int x, int y);

/*render_sprite.c*/
void	new_sprite(t_game *game, t_img *sprite, char *path);
void	render_map(t_game *game, t_map *map);
void	render_to_window(t_game *game, t_img *image, int x, int y);

/*render_wall.c*/
void	check_outer_wall(t_game *game, char **grid, int x, int y);
void	check_inner_wall(t_game *game, char **grid, int x, int y);

/*verify_map.c*/
void	check_rectangle(t_game *game, t_map *map);
void	check_closed(t_game *game, t_map *map);
void	check_empty_lines(t_game *game, char *line);
void	check_components(t_game *game, t_map *map);
void	check_valid_path(t_game *game, char ***grid, int x, int y);

/*movement.c*/
int		key_handler(int keysym, t_game *game);
void	update_move_count(t_game *game);

/*animation_bonus.c*/
int		update_handler(t_game *game);
void	player_action(t_game *game);
int		player_idle(t_game *game, t_pos current);
void	player_walk(t_game *game, t_pos prev, t_pos new);

/*message_bonus.c*/
void	print_victory(t_game *game);
void	print_defeat(t_game *game);
void	print_msg(char *message, int fd);
void	print_extra_msg(t_game *game);

/*exit_utils.c*/
void	end(char *message, t_game *game, int exit_code);
void	free_map_grid(t_map map, char ***grid);
int		x_close_window(t_game *game);

/*enemy_bonus.c*/
void	check_enemy(t_game *game, t_data *enemy, char **grid, int *dir);
void	enemy_up(t_game *game, char **grid, int x, int y);
void	enemy_down(t_game *game, char **grid, int x, int y);
void	enemy_action(t_game *game, t_frames *enemy, int x, int y);

#endif
