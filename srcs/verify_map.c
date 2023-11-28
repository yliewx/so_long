/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:35:32 by yliew             #+#    #+#             */
/*   Updated: 2023/11/14 17:17:14 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	check_empty_lines(t_game *game, char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\n')
		end("Invalid map: First line is empty.\n", game, 1);
	while (line[i])
	{
		if (line[i] == '\n' && line[i + 1] == '\n')
			end("Invalid map: Empty line found.\n", game, 1);
		i++;
	}
}

void	check_rectangle(t_game *game, t_map *map)
{
	int	i;

	i = 0;
	while (map->grid[i] && map->grid[i + 1])
	{
		if (ft_strlen(map->grid[i]) != ft_strlen(map->grid[i + 1]))
			end("Invalid map: Must be rectangular.\n", game, 1);
		i++;
	}
}

void	check_closed(t_game *game, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	map->columns = ft_strlen(map->grid[i]);
	while (map->grid[j])
	{
		if (map->grid[j][0] != '1' ||
			map->grid[j][map->columns - 1] != '1')
			end("Invalid map: Sides not closed.\n", game, 1);
		j++;
	}
	j--;
	while (map->grid[0][i] && map->grid[j][i])
	{
		if (map->grid[0][i] != '1')
			end("Invalid map: First row not closed.\n", game, 1);
		if (map->grid[j][i] != '1')
			end("Invalid map: Last row not closed.\n", game, 1);
		i++;
	}
}

void	check_components(t_game *game, t_map *map)
{
	if (map->start != 1)
		end("Invalid map: Must have 1 player.\n", game, 1);
	else if (map->exit != 1)
		end("Invalid map: Must have 1 exit.\n", game, 1);
	else if (map->coins == 0)
		end("Invalid map: No collectible found.\n", game, 1);
}

void	check_valid_path(t_game *game, char ***grid, int x, int y)
{
	if (y - 1 < 0 || x - 1 < 0 || y + 1 >= game->map.rows
		|| x + 1 >= game->map.columns || (*grid)[y][x] == '1')
		return ;
	if ((*grid)[y][x] == 'E')
		game->map.exit_found = true;
	if ((*grid)[y][x] == 'C')
		game->player.coins++;
	(*grid)[y][x] = '1';
	if (game->map.exit_found && game->map.coins == game->player.coins)
	{
		game->map.valid_path = true;
		game->map.exit_found = false;
		game->player.coins = 0;
		return ;
	}
	check_valid_path(game, grid, x, y - 1);
	check_valid_path(game, grid, x, y + 1);
	check_valid_path(game, grid, x - 1, y);
	check_valid_path(game, grid, x + 1, y);
}
