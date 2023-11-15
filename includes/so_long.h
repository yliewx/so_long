/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:46:22 by yliew             #+#    #+#             */
/*   Updated: 2023/11/15 16:11:34 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

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

/*platform-specific definitions*/

# ifdef __linux__
#  include "../mlx_linux/mlx.h"
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

# define WALL_XPM "./assets/xpm/ICEYROCKS.xpm"
# define FLOOR_XPM "./assets/xpm/SNOW.xpm"
# define PLAYER_XPM "./assets/ducky/idle/idle_0_L.xpm"
# define COIN_XPM "./assets/xpm/TALLGRASS.xpm"
# define EXIT_XPM "./assets/xpm/FLATSTONES.xpm"
# define IMG_SIZE 48

/*text colour*/

# define BROWN "\033[1;33m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define RESET "\033[0m"

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
	int	x;
	int	y;
}	t_img;

typedef struct s_player
{
	int	direction;
	int	x;
	int	y;
}	t_player;

typedef struct s_map
{
	char	**grid;
	char	*full_line;
	int	fd;
	int	rows;
	int	columns;
	int	start;
	int	coins;
	int	exit;
	bool	valid_path;
}	t_map;

typedef struct s_count
{
	int	coins;
	int	movements;
	bool	exit_found;
}	t_count;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	map;
	t_player	player;
	t_count	current;
	t_img	img_wall;
	t_img	img_floor;
	t_img	img_player;
	t_img	img_coin;
	t_img	img_exit;
	int	screen_x;
	int	screen_y;
}	t_data;

/*init_game.c*/
void	init_variables(t_data *game);

/*init_map.c*/
void	open_map(t_data *game, char *map_path);
void	check_valid_map(t_data *game, t_map *map, char *line);
void	init_components(t_data *game, t_map *map);

/*graphics.c*/
void	new_sprite(t_data *game, t_img *sprite, char *path);
void	check_sprite(t_data *game, int c, int x, int y);
void	render_sprite(t_data *game, t_img *sprite, int x, int y);
void	render_map(t_data *game, t_map *map);

/*exit_utils.c*/
void	end(char *message, t_data *game, int exit_code);
void	free_map_grid(t_map map, char ***grid);
void	print_msg(char *message, int fd);

/*verify_map.c*/
void	check_rectangle(t_data *game, t_map *map);
void	check_closed(t_data *game, t_map *map);
void	check_empty_lines(t_data *game, char *line);
void	check_components(t_data *game, t_map *map);
void	check_valid_path(t_data *game, char ***grid, int x, int y);

/*input_handler.c*/
int	test_keypress(int keysym, t_data *data);

#endif
