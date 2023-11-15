/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:26:09 by yliew             #+#    #+#             */
/*   Updated: 2023/11/15 18:04:19 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	set_map_params(t_map *map, char *line)
{
	printf("%s\n", line);
	while (map->grid[map->rows])
		map->rows++;
	map->columns = ft_strlen(map->grid[0]);
}

void	init_components(t_data *game, t_map *map)
{
	int	i;
	int	j;

	j = 0;
	while (map->grid[j])
	{
		i = 0;
		while (map->grid[j][i])
		{
			if (!ft_strchr("01CEP\n", map->grid[j][i]))
				end("Invalid char: Must be 01CEP.\n", game, 1);
			else if (map->grid[j][i] == 'P')
			{
				map->start++;
				game->player.x = i;
				game->player.y = j;
			}
			else if (map->grid[j][i] == 'E')
				map->exit++;
			else if (map->grid[j][i] == 'C')
				map->coins++;
			i++;
		}
		j++;
	}
}

void	check_valid_map(t_data *game, t_map *map, char *line)
{
	char	**temp_grid;

	check_empty_lines(game, line);
	check_rectangle(game, map);
	check_closed(game, map);
	init_components(game, map);
	check_components(game, map);
	temp_grid = ft_split(line, '\n');
	check_valid_path(game, &temp_grid, game->player.x, game->player.y);
	if (!game->map.valid_path)
	{
		free_map_grid(game->map, &temp_grid);
		end("Invalid map: No valid path found.\n", game, 1);
	}
}

void	open_map(t_data *game, char *map_path)
{
	char	*current_line;
	char	*temp;

	game->map.fd = open(map_path, O_RDONLY);
	if (game->map.fd == -1)
		end("Could not open file.\n", game, 1);
	game->map.full_line = ft_calloc(1, 1);
	if (!game->map.full_line)
		end("Error allocating memory for map.\n", game, 1);
	while (1)
	{
		current_line = get_next_line(game->map.fd);
		if (!current_line)
			break ;
		temp = game->map.full_line;
		game->map.full_line = ft_strjoin(temp, current_line);
		free(temp);
		free(current_line);
	}
	if (!game->map.full_line[0])
	{
		free(game->map.full_line);
		end("Invalid map: Map is empty.\n", game, 1);
	}
	game->map.grid = ft_split(game->map.full_line, '\n');
	set_map_params(&(game->map), game->map.full_line);
}
