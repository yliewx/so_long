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

void	update_move_count(t_game *game)
{
	game->player.movements++;
	ft_printf("Movements: %i\n", game->player.movements);
}

void	update_map(t_game *game, char **grid, t_pos prev, t_pos *new)
{
	if (grid[new->y][new->x] == 'C')
		game->player.coins++;
	if (grid[new->y][new->x] == 'E')
	{
		if (game->player.coins == game->map.coins)
		{
			update_move_count(game);
			print_victory(game);
		}
		else
		{
			print_extra_msg(game);
			set_pos(new, prev.x, prev.y);
			return ;
		}
	}
	grid[prev.y][prev.x] = '0';
	grid[new->y][new->x] = 'P';
	update_move_count(game);
	render_map(game, &game->map);
}

void	player_movement(t_game *game, t_map *map, t_pos *current, int dir)
{
	if (dir == up && is_accessible(map, current->x, current->y - 1))
	{
		current->y -= 1;
		update_map(game, map->grid, game->player.prev, current);
	}
	else if (dir == down && is_accessible(map, current->x, current->y + 1))
	{
		current->y += 1;
		update_map(game, map->grid, game->player.prev, current);
	}
	else if (dir == left && is_accessible(map, current->x - 1, current->y))
	{
		game->player.direction = left;
		current->x -= 1;
		update_map(game, map->grid, game->player.prev, current);
	}
	else if (dir == right && is_accessible(map, current->x + 1, current->y))
	{
		game->player.direction = right;
		current->x += 1;
		update_map(game, map->grid, game->player.prev, current);
	}
}

int	key_handler(int keysym, t_game *game)
{
	set_pos(&game->player.prev, game->player.current.x,
		game->player.current.y);
	if (keysym == W_KEY || keysym == UP_KEY)
		player_movement(game, &game->map, &game->player.current, up);
	else if (keysym == S_KEY || keysym == DOWN_KEY)
		player_movement(game, &game->map, &game->player.current, down);
	else if (keysym == A_KEY || keysym == LEFT_KEY)
		player_movement(game, &game->map, &game->player.current, left);
	else if (keysym == D_KEY || keysym == RIGHT_KEY)
		player_movement(game, &game->map, &game->player.current, right);
	else if (keysym == ESC)
		end("Quitting game.\n", game, 0);
	return (0);
}
