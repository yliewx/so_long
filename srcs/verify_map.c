/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:35:32 by yliew             #+#    #+#             */
/*   Updated: 2023/11/12 16:43:47 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	check_rectangle(t_data *game, t_map *map)
{
	int	i;

	i = 0;
	while (map->arr[i] && map->arr[i + 1])
	{
		if (ft_strlen(map->arr[i]) != ft_strlen(map->arr[i + 1]))
			end("Invalid map: Must be rectangular.\n", game, 1);
		i++;
	}
}

void	check_closed(t_data *game, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	map->columns = ft_strlen(map->arr[i]);
	while (map->arr[j])
	{
		if (map->arr[j][0] != '1' ||
			map->arr[j][map->columns - 1] != '1')
			end("Invalid map: Sides not closed.\n", game, 1);
		j++;
	}
	j--;
	while (map->arr[0][i] && map->arr[j][i])
	{
		if (map->arr[0][i] != '1')
			end("Invalid map: First row not closed.\n", game, 1);
		if (map->arr[j][i] != '1')
			end("Invalid map: Last row not closed.\n", game, 1);
		i++;
	}
}

/*start from original position P
if: y - 1 >= 0, x - 1 >= 0
y + 1 < game->map.rows
x + 1 < game->map.columns
- check if map[y-1][x] is accessible (0CEP) and return the result
- if 0CP, return 1 and call check_valid_path on that position
- if 1, return 0 (inaccessible)
- if E, solution has been found*/
/*int	check_valid_path(t_data *game, char **map, int x, int y)
{
	if (game->map.valid_path != 0)
		return (1);
	if (y - 1 >= 0 || x - 1 >= 0
		|| y + 1 < game->map.rows || x + 1 < game->map.columns)
	{
		check_valid_path(game, map, x, y - 1);
	}
}
*/
void	init_components(t_data *game, t_map *map)
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
				game->c.start++;
				map->player_x = i;
				map->player_y = j;
			}
			else if (map->arr[j][i] == 'E')
				game->c.exit++;
			else if (map->arr[j][i] == 'C')
				game->c.coins++;
			i++;
		}
		j++;
	}
}

void	check_empty_lines(t_data *game, char *line)
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
