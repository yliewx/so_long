/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:26:09 by yliew             #+#    #+#             */
/*   Updated: 2023/11/12 16:43:21 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	set_map_params(t_map *map, char *line)
{
	printf("%s\n", line);
	while (map->arr[map->rows])
		map->rows++;
	map->columns = ft_strlen(map->arr[0]);
}

void	check_valid_map(t_data *game, t_map *map, char *line)
{
	check_empty_lines(game, line);
	check_rectangle(game, map);
	check_closed(game, map);
	init_components(game, map);
	if (game->c.start != 1)
		end("Invalid map: Must have 1 player.\n", game, 1);
	else if (game->c.exit != 1)
		end("Invalid map: Must have 1 exit.\n", game, 1);
	else if (game->c.coins == 0)
		end("Invalid map: No collectible found.\n", game, 1);
	//check_valid_path(game, map->arr, game->player.x, game->player.y);
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
	}
	if (!game->map.full_line[0])
		end("Invalid map: Map is empty.\n", game, 1);
	game->map.arr = ft_split(game->map.full_line, '\n');
	set_map_params(&(game->map), game->map.full_line);
}
