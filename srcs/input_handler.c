/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:28:34 by yliew             #+#    #+#             */
/*   Updated: 2023/11/12 19:05:01 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	is_accessible(t_map *map, int x, int y)
{
	if (y - 1 >= 0)
	{
		if (ft_strchr("0CEP", map->arr[y][x]))
			return (1);
	}
	printf("not accessible\n");
	return (0);
}

void	player_movement(t_map *map, int dir)
{
	int	current_x;
	int	current_y;

	current_x = map->player_x;
	current_y = map->player_y;
	if (dir == 1)
	{
		if (is_accessible(map, current_x, current_y - 1))
		{
			map->arr[current_y][current_x] = '0';
			map->player_y = current_y - 1;
			printf("moved up\n");
		}
	}
}

int	test_keypress(int keysym, t_data *game)
{
	printf("Key pressed: %i\n\n", keysym);
	if (keysym == W_KEY || keysym == UP_KEY)
		player_movement(&game->map, 1);
	else if (keysym == S_KEY || keysym == DOWN_KEY)
		player_movement(&game->map, 2);
	else if (keysym == A_KEY || keysym == LEFT_KEY)
		player_movement(&game->map, 3);
	else if (keysym == D_KEY || keysym == RIGHT_KEY)
		player_movement(&game->map, 4);
	else if (keysym == ESC)
		end("Quitting game.\n", game, 0);
	return (0);
}
