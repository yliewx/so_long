/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:13:32 by yliew             #+#    #+#             */
/*   Updated: 2023/11/21 17:42:03 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	check_outer_wall(t_game *game, char **grid, int x, int y)
{
	if (y - 1 < 0)
	{
		if (x == 0)
			render_sprite(&game->display, &game->wall.down_l, x, y);
		else if (x == game->map.columns - 1)
			render_sprite(&game->display, &game->wall.down_r, x, y);
		else
			render_sprite(&game->display, &game->wall.down_m, x, y);
	}
	else if (y + 1 >= game->map.rows)
	{
		if (x == 0)
			render_sprite(&game->display, &game->wall.up_l, x, y);
		else if (x == game->map.columns - 1)
			render_sprite(&game->display, &game->wall.up_r, x, y);
		else
			render_sprite(&game->display, &game->wall.up_m, x, y);
	}
	else if ((x - 1 < 0 && grid[y][x + 1] != '1')
			|| (x + 1 >= game->map.columns && grid[y][x - 1] != '1'))
		render_sprite(&game->display, &game->wall.side_m, x, y);
	else if (x + 1 < 0 || x + 1 >= game->map.columns)
		render_sprite(&game->display, &game->wall.blank, x, y);
}

void	check_inner_sides(t_game *game, char **grid, int x, int y)
{
	if (grid[y][x - 1] != '1' && grid[y][x + 1] == '1')
		render_sprite(&game->display, &game->wall.side_l, x, y);
	else if (grid[y][x + 1] != '1' && grid[y][x - 1] == '1')
		render_sprite(&game->display, &game->wall.side_r, x, y);
}

void	check_inner_wall(t_game *game, char **grid, int x, int y)
{
	if (y - 1 < 0 || y + 1 >= game->map.rows
		|| x - 1 < 0 || x + 1 >= game->map.columns)
		return ;
	else if (grid[y - 1][x] != '1')
	{
		if (grid[y][x - 1] != '1')
			render_sprite(&game->display, &game->wall.up_l, x, y);
		else if (grid[y][x + 1] != '1')
			render_sprite(&game->display, &game->wall.up_r, x, y);
		else
			render_sprite(&game->display, &game->wall.up_m, x, y);
	}
	else if (grid[y + 1][x] != '1')
	{
		if (grid[y][x - 1] != '1')
			render_sprite(&game->display, &game->wall.down_l, x, y);
		else if (grid[y][x + 1] != '1')
			render_sprite(&game->display, &game->wall.down_r, x, y);
		else
			render_sprite(&game->display, &game->wall.down_m, x, y);
	}
	else if (grid[y][x - 1] != '1' || grid[y][x + 1] != '1')
		check_inner_sides(game, grid, x, y);
	else
		render_sprite(&game->display, &game->wall.blank, x, y);
}
