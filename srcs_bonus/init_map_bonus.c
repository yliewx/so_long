/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:26:09 by yliew             #+#    #+#             */
/*   Updated: 2023/11/21 18:08:49 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	set_map_params(t_map *map)
{
	while (map->grid[map->rows])
		map->rows++;
	map->columns = ft_strlen(map->grid[0]);
}

void	set_pos(t_pos *subject, int x, int y)
{
	subject->x = x;
	subject->y = y;
}

void	init_components(t_game *game, t_map *map, int i, int j)
{
	while (map->grid[j])
	{
		i = 0;
		while (map->grid[j][i])
		{
			if (!ft_strchr("01CEPX\n", map->grid[j][i]))
				end("Invalid char: Must be 01CEPX.\n", game, 1);
			else if (map->grid[j][i] == 'P')
			{
				map->start++;
				set_pos(&game->player.current, i, j);
			}
			else if (map->grid[j][i] == 'E')
				map->exit++;
			else if (map->grid[j][i] == 'C')
				map->coins++;
			else if (map->grid[j][i] == 'X')
			{
				map->enemies++;
				set_pos(&game->enemy.current, i, j);
			}
			i++;
		}
		j++;
	}
}

void	check_valid_map(t_game *game, t_map *map, char *line)
{
	char	**temp_grid;

	check_empty_lines(game, line);
	check_rectangle(game, map);
	check_closed(game, map);
	init_components(game, map, 0, 0);
	check_components(game, map);
	temp_grid = ft_split(line, '\n');
	check_valid_path(game, &temp_grid,
		game->player.current.x, game->player.current.y);
	free_map_grid(game->map, &temp_grid);
	if (!game->map.valid_path)
		end("Invalid map: No valid path found.\n", game, 1);
}

void	open_map(t_game *game, char *map_path)
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
}
