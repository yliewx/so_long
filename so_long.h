/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:46:22 by yliew             #+#    #+#             */
/*   Updated: 2023/10/21 16:51:49 by yliew            ###   ########.fr       */
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

# define FLOOR "assets/PixelTexturePack/xpm/GRAYROCKS.xpm"

/*structs*/

typedef struct s_sprite
{
	void	*img_ptr;
	int	x;
	int	y;
}	t_sprite;

typedef struct s_map
{
	int	fd;
	char	**arr;
}	t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	map;
	t_sprite	floor;
}	t_data;

#endif
