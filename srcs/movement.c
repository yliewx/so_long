/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:28:34 by yliew             #+#    #+#             */
/*   Updated: 2023/11/18 18:57:46 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	is_accessible(t_map *map, int x, int y)
{
	if (y >= 0 || x >= 0 || y < map->rows || x < map->columns)
	{
		if (ft_strchr("0CEP", map->grid[y][x]))
			return (1);
	}
	return (0);
}

void	update_map(t_data *game, char **grid, t_player prev, t_player new)
{
	if (grid[new.y][new.x] == 'C')
		game->current.coins++;
	game->current.movements++;
	if (grid[new.y][new.x] == 'E')
	{
		if (game->current.coins == game->map.coins)
			end("Game cleared!\n", game, 0);
		else
		{
			print_msg("You still have coins to collect!\n", 2);
			game->player.x = prev.x;
			game->player.y = prev.y;
			return ;
		}
	}
	grid[prev.y][prev.x] = '0';
	grid[new.y][new.x] = 'P';
	check_sprite(game, grid[prev.y][prev.x], prev.x, prev.y);
	check_sprite(game, grid[new.y][new.x], new.x, new.y);
	ft_printf("Movements: %i\n", game->current.movements);
}

void	player_movement(t_data *game, t_map *map, t_player current, int dir)
{
	if (dir == up && is_accessible(map, current.x, current.y - 1))
	{
		game->player.y -= 1;
		update_map(game, map->grid, current, game->player);
	}
	else if (dir == down && is_accessible(map, current.x, current.y + 1))
	{
		game->player.y += 1;
		update_map(game, map->grid, current, game->player);
	}
	else if (dir == left && is_accessible(map, current.x - 1, current.y))
	{
		game->player.direction = left;
		game->player.x -= 1;
		update_map(game, map->grid, current, game->player);
	}
	else if (dir == right && is_accessible(map, current.x + 1, current.y))
	{
		game->player.direction = right;
		game->player.x += 1;
		update_map(game, map->grid, current, game->player);
	}
}

int	check_keypress(int keysym, t_data *game)
{
	t_player	current;

	current.x = game->player.x;
	current.y = game->player.y;
	if (keysym == W_KEY || keysym == UP_KEY)
		player_movement(game, &game->map, current, up);
	else if (keysym == S_KEY || keysym == DOWN_KEY)
		player_movement(game, &game->map, current, down);
	else if (keysym == A_KEY || keysym == LEFT_KEY)
		player_movement(game, &game->map, current, left);
	else if (keysym == D_KEY || keysym == RIGHT_KEY)
		player_movement(game, &game->map, current, right);
	else if (keysym == ESC)
		end("Quitting game.\n", game, 0);
	return (0);
}
