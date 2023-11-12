/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:46:22 by yliew             #+#    #+#             */
/*   Updated: 2023/11/12 18:18:12 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/includes/libft.h"
# include "libft/includes/ft_printf.h"
# include "libft/includes/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

/*define key press*/

# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define UP_KEY 65362
# define DOWN_KEY 65364
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define ESC 65307

/*image paths*/

# define WALL_XPM "./assets/xpm/GRAYROCKS.xpm"
# define FLOOR_XPM "./assets/xpm/DIRT.xpm"
# define PLAYER_XPM "./assets/xpm/BIGLEAVES.xpm"
# define COIN_XPM "./assets/xpm/TALLGRASS.xpm"
# define EXIT_XPM "./assets/xpm/FLATSTONES.xpm"
# define IMG_SIZE 32

/*text colour*/

# define B_BROWN "\033[1;33m"
# define RESET "\033[0m"

/*structs*/

typedef struct s_img
{
	void	*ptr;
	int	x;
	int	y;
}	t_img;

typedef struct s_map
{
	char	**arr;
	char	*full_line;
	int	fd;
	int	rows;
	int	columns;
	int	player_x;
	int	player_y;
	int	valid_path;
}	t_map;

typedef struct s_count
{
	int	start;
	int	coins;
	int	exit;
	int	movements;
}	t_count;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	map;
	t_img	img_wall;
	t_img	img_floor;
	t_img	img_player;
	t_img	img_coin;
	t_img	img_exit;
	t_count	c;
}	t_data;

/*init_game.c*/
void	init_variables(t_data *game);

/*init_map.c*/
void	open_map(t_data *game, char *map_path);
void	check_valid_map(t_data *game, t_map *map, char *line);

/*graphics.c*/
void	new_sprite(t_data *game, t_img *sprite, char *path);
void	render_sprite(t_data *game, t_img *sprite, int x, int y);
void	render_map(t_data *game, t_map *map);

/*exit_utils.c*/
void	end(char *message, t_data *game, int exit_code);
void	print_msg(char *message, int fd);

/*verify_map.c*/
void	check_rectangle(t_data *game, t_map *map);
void	check_closed(t_data *game, t_map *map);
void	init_components(t_data *game, t_map *map);
void	check_empty_lines(t_data *game, char *line);

/*input_handler.c*/
int	test_keypress(int keysym, t_data *data);

#endif
