/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:10:39 by yliew             #+#    #+#             */
/*   Updated: 2023/11/21 18:52:30 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	enemy_action(t_game *game, t_frames *enemy, int x, int y)
{
	static int	i;

	if (i >= 0 && i < 4)
		render_sprite(&game->display, &enemy->walk_0, x, y);
	else if (i >= 4 && i < 8)
		render_sprite(&game->display, &enemy->walk_1, x, y);
	else if (i >= 8 && i < 12)
		render_sprite(&game->display, &enemy->walk_2, x, y);
	else if (i >= 12 && i < 16)
		render_sprite(&game->display, &enemy->walk_3, x, y);
	else if (i >= 16 && i < 20)
		render_sprite(&game->display, &enemy->walk_4, x, y);
	else if (i >= 20 && i < 24)
		render_sprite(&game->display, &enemy->walk_5, x, y);
	else if (i >= 24 && i < 28)
		render_sprite(&game->display, &enemy->walk_6, x, y);
	else if (i >= 28 && i < 32)
	{
		render_sprite(&game->display, &enemy->walk_7, x, y);
		if (i == 31)
			i = -1;
	}
	i++;
}

void	update_enemy_pos(t_game *game, char **grid, t_pos prev, t_pos *new)
{
	if (ft_strchr("1EC", grid[new->y][new->x]))
	{
		set_pos(new, prev.x, prev.y);
		if (game->enemy.direction == up)
			game->enemy.direction = down;
		else
			game->enemy.direction = up;
		return ;
	}
	if (grid[new->y][new->x] == 'P')
		print_defeat(game);
	grid[prev.y][prev.x] = '0';
	grid[new->y][new->x] = 'X';
}

void	check_enemy(t_game *game, t_data *enemy, char **grid, int *dir)
{
	static int	counter;

	counter++;
	if (counter < 100)
		return ;
	set_pos(&enemy->prev, enemy->current.x, enemy->current.y);
	if (*dir == up)
		enemy->current.y -= 1;
	else
		enemy->current.y += 1;
	update_enemy_pos(game, grid, enemy->prev, &enemy->current);
	counter = -1;
}
