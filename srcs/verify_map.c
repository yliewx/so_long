/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:35:32 by yliew             #+#    #+#             */
/*   Updated: 2023/11/10 13:39:15 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	is_rectangle(t_map *map)
{
	int	i;

	i = 0;
	while (map->arr[i] && map->arr[i + 1])
	{
		if (ft_strlen(map->arr[i]) != ft_strlen(map->arr[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

void	check_closed(t_data *game, t_map *map)
{
	int	i;
	int	j;
	int	last_column;

	i = 0;
	j = 0;
	last_column = ft_strlen(map->arr[i]) - 1;
	while (map->arr[j])
	{
		if (map->arr[j][0] != '1' || map->arr[j][last_column] != '1')
			end("Invalid map: Sides not closed.\n", game, 1);
		j++;
	}
	j--;
	while (map->arr[0][i] && map->arr[j][i])
	{
		if (map->arr[0][i] != '1')
			end("Invalid map: 1st row not closed.\n", game, 1);
		if (map->arr[j][i] != '1')
			end("Invalid map: Last row not closed.\n", game, 1);
		i++;
	}
}
/*
int	check_valid_path(t_data *game, t_map *map)
{
}
*/
void	check_components(t_data *game, t_map *map)
{
	int	i;
	int	j;

	j = 0;
	while (map->arr[j])
	{
		i = 0;
		while (map->arr[j][i])
		{
			if (!ft_strchr("01CEP\n", map->arr[j][i]))
				end("Invalid char: Must be 01CEP.\n", game, 1);
			else if (map->arr[j][i] == 'P')
			{
				game->start_pos++;
				game->player.x = i;
				game->player.y = j;
			}
			else if (map->arr[j][i] == 'C')
				game->coins++;
			else if (map->arr[j][i] == 'E')
				game->exit++;
			i++;
		}
		j++;
	}
	if (game->start_pos != 1)
		end("Invalid map: Multiple start pos.\n", game, 1);
	if (game->exit != 1)
		end("Invalid map: Multiple exits.\n", game, 1);
}

int	check_valid_map(t_data *game, t_map *map, char *line)
{
	if (!ft_strchr(line, 'E'))
		end("Invalid map: No exit found.\n", game, 1);
	else if (!ft_strchr(line, 'C'))
		end("Invalid map: No collectible found.\n", game, 1);
	else if (!ft_strchr(line, 'P'))
		end("Invalid map: No start pos found.\n", game, 1);
	if (!is_rectangle(map))
		end("Invalid map: Must be rectangular.\n", game, 1);
	check_closed(game, map);
	check_components(game, map);
	return (1);
}

void	open_map(t_data *game, char *map_path)
{
	t_map	new_map;
	char	*current_line;
	char	*total_lines;
	char	*temp;

	new_map.fd = open(map_path, O_RDONLY);
	if (new_map.fd == -1)
		end("Could not open file.\n", game, 1);
	total_lines = ft_calloc(1, 1);
	if (!total_lines)
		end("Error allocating memory for map.\n", game, 1);
	while (1)
	{
		current_line = get_next_line(new_map.fd);
		if (!current_line)
			break ;
		temp = total_lines;
		total_lines = ft_strjoin(temp, current_line);
		free(temp);
	}
	new_map.arr = ft_split(total_lines, '\n');
	if (check_valid_map(game, &new_map, total_lines))
		printf("valid map\ncoins: %i\n", game->coins);
	game->map = new_map;
}
