/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:37:53 by yliew             #+#    #+#             */
/*   Updated: 2023/11/23 21:32:23 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	free_map_grid(t_map map, char ***grid)
{
	int	j;

	j = map.rows - 1;
	while (j >= 0)
	{
		free((*grid)[j]);
		j--;
	}
	free(*grid);
}

void	free_sprites(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->display.ptr);
	mlx_destroy_image(game->mlx_ptr, game->wall.up_l.ptr);
	mlx_destroy_image(game->mlx_ptr, game->wall.up_m.ptr);
	mlx_destroy_image(game->mlx_ptr, game->wall.up_r.ptr);
	mlx_destroy_image(game->mlx_ptr, game->wall.down_l.ptr);
	mlx_destroy_image(game->mlx_ptr, game->wall.down_m.ptr);
	mlx_destroy_image(game->mlx_ptr, game->wall.down_r.ptr);
	mlx_destroy_image(game->mlx_ptr, game->wall.side_l.ptr);
	mlx_destroy_image(game->mlx_ptr, game->wall.side_m.ptr);
	mlx_destroy_image(game->mlx_ptr, game->wall.side_r.ptr);
	mlx_destroy_image(game->mlx_ptr, game->wall.blank.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_floor.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_exit_0.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_exit_1.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_coin.ptr);
}

void	free_frames(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->l.idle_0.ptr);
	mlx_destroy_image(game->mlx_ptr, game->l.idle_1.ptr);
	mlx_destroy_image(game->mlx_ptr, game->l.walk_0.ptr);
	mlx_destroy_image(game->mlx_ptr, game->l.walk_1.ptr);
	mlx_destroy_image(game->mlx_ptr, game->l.walk_2.ptr);
	mlx_destroy_image(game->mlx_ptr, game->l.walk_3.ptr);
	mlx_destroy_image(game->mlx_ptr, game->r.idle_0.ptr);
	mlx_destroy_image(game->mlx_ptr, game->r.idle_1.ptr);
	mlx_destroy_image(game->mlx_ptr, game->r.walk_0.ptr);
	mlx_destroy_image(game->mlx_ptr, game->r.walk_1.ptr);
	mlx_destroy_image(game->mlx_ptr, game->r.walk_2.ptr);
	mlx_destroy_image(game->mlx_ptr, game->r.walk_3.ptr);
	mlx_destroy_image(game->mlx_ptr, game->en.walk_0.ptr);
	mlx_destroy_image(game->mlx_ptr, game->en.walk_1.ptr);
	mlx_destroy_image(game->mlx_ptr, game->en.walk_2.ptr);
	mlx_destroy_image(game->mlx_ptr, game->en.walk_3.ptr);
	mlx_destroy_image(game->mlx_ptr, game->en.walk_4.ptr);
	mlx_destroy_image(game->mlx_ptr, game->en.walk_5.ptr);
	mlx_destroy_image(game->mlx_ptr, game->en.walk_6.ptr);
	mlx_destroy_image(game->mlx_ptr, game->en.walk_7.ptr);
}

int	x_close_window(t_game *game)
{
	end("Quitting game.\n", game, 0);
	return (0);
}

void	end(char *message, t_game *game, int exit_code)
{
	if (exit_code != 0)
	{
		print_msg("Error\n", 2);
		print_msg(message, 2);
	}
	else
		print_msg(message, 1);
	if (game->map.grid)
	{
		free_map_grid(game->map, &game->map.grid);
		free(game->map.full_line);
	}
	if (game->map.valid_path)
	{
		free_sprites(game);
		free_frames(game);
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		if (OS_LINUX)
			mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	exit(exit_code);
}
