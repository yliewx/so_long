/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:37:53 by yliew             #+#    #+#             */
/*   Updated: 2023/11/15 18:08:10 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	print_msg(char *message, int fd)
{
	char	*colour;

	if (fd == 2)
		colour = RED;
	else
		colour = GREEN;
	ft_putstr_fd(colour, fd);
	ft_putstr_fd(message, fd);
	ft_putstr_fd(RESET, fd);
}

void	free_map_grid(t_map map, char ***grid)
{
	int	j;

	j = map.rows - 1;
	printf("\trows: %i, columns: %i\n", map.rows, map.columns);
	while (j >= 0)
	{
		free((*grid)[j]);
		printf("\tfreed grid[%i]\n", j);
		j--;
	}
	free(*grid);
	printf("done freeing\n");
}

void	free_sprites(t_data *game)
{
	mlx_destroy_image(game->mlx_ptr, game->img_wall.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_floor.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_player.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_coin.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_exit.ptr);
}

void	end(char *message, t_data *game, int exit_code)
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
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	exit(exit_code);
}
