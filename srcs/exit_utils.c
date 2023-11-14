/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:37:53 by yliew             #+#    #+#             */
/*   Updated: 2023/11/12 17:02:07 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	print_msg(char *message, int fd)
{
	ft_putstr_fd(RED, fd);
	ft_putstr_fd(message, fd);
	ft_putstr_fd(RESET, fd);
}

void	free_map_grid(t_map map, char **grid)
{
	int	j;

	j = map.rows - 1;
	printf("\trows: %i, columns: %i\n", map.rows, map.columns);
	while (j >= 0)
	{
		free(grid[j]);
		printf("\tfreed grid[%i]\n", j);
		j--;
	}
	printf("done freeing\n");
}

void	end(char *message, t_data *game, int exit_code)
{
	if (exit_code != 0)
		print_msg("Error\n", 2);
	if (message)
		print_msg(message, 2);
	if (game->map.grid)
	{
		free_map_grid(game->map, game->map.grid);
		free(game->map.full_line);
	}
	if (game->map.valid_path)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		free(game->mlx_ptr);
	}
	exit(exit_code);
}
