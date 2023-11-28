/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:13:32 by yliew             #+#    #+#             */
/*   Updated: 2023/11/21 17:42:03 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	render_to_window(t_game *game, t_img *image, int x, int y)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		image->ptr, IMG_SIZE * x, IMG_SIZE * y);
}

void	new_sprite(t_game *game, t_img *sprite, char *path)
{
	sprite->ptr = mlx_xpm_file_to_image(game->mlx_ptr, path,
			&sprite->x, &sprite->y);
	get_sprite_info(sprite);
}

void	check_sprite(t_game *game, int c, int x, int y)
{
	if (c == '1')
	{
		check_outer_wall(game, game->map.grid, x, y);
		check_inner_wall(game, game->map.grid, x, y);
	}
	else if (c == '0' || c == 'P')
		render_sprite(&game->display, &game->img_floor, x, y);
	else if (c == 'C')
	{
		render_sprite(&game->display, &game->img_floor, x, y);
		render_offset(game, &game->img_coin,
			IMG_SIZE * x + 16, IMG_SIZE * y + 24);
	}
	else if (c == 'X')
	{
		render_sprite(&game->display, &game->img_floor, x, y);
		enemy_action(game, &game->en, x, y);
	}
	else if (c == 'E' && game->player.coins != game->map.coins)
		render_sprite(&game->display, &game->img_exit_0, x, y);
	else if (c == 'E' && game->player.coins == game->map.coins)
		render_sprite(&game->display, &game->img_exit_1, x, y);
}

void	render_map(t_game *game, t_map *map)
{
	int	i;
	int	j;

	j = 0;
	while (map->grid[j])
	{
		i = 0;
		while (map->grid[j][i])
		{
			check_sprite(game, map->grid[j][i], i, j);
			i++;
		}
		j++;
	}
}
