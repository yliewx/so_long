/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:13:32 by yliew             #+#    #+#             */
/*   Updated: 2023/11/18 18:52:46 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	new_sprite(t_data *game, t_img *sprite, char *path)
{
	sprite->ptr = mlx_xpm_file_to_image(game->mlx_ptr, path,
			&sprite->x, &sprite->y);
	get_sprite_info(sprite);
}

void	render_sprite(t_data *game, t_img *sprite, int x, int y)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		sprite->ptr, IMG_SIZE * x, IMG_SIZE * y);
}

void	check_sprite(t_data *game, int c, int x, int y)
{
	if (c == '1')
		render_sprite(game, &game->img_wall, x, y);
	else if (c == '0')
		render_sprite(game, &game->img_floor, x, y);
	else if (c == 'P')
	{
		if (game->player.direction == left)
			render_sprite(game, &game->base_player_L, x, y);
		else
			render_sprite(game, &game->base_player_R, x, y);
	}
	else if (c == 'C')
		render_sprite(game, &game->base_coin, x, y);
	else if (c == 'E')
		render_sprite(game, &game->img_exit, x, y);
}

void	render_map(t_data *game, t_map *map)
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
