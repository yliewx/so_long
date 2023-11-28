/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:13:32 by yliew             #+#    #+#             */
/*   Updated: 2023/11/23 21:11:24 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	walk_left(t_game *game, t_frames *l, t_pos prev, t_pos new)
{
	static int	i;

	if (i == 0)
		render_offset(game, &l->walk_0, prev.x - 3, prev.y - 8);
	else if (i == 1)
		render_offset(game, &l->walk_1, prev.x - 6, prev.y - 4);
	else if (i == 2)
		render_offset(game, &l->walk_2, prev.x - 9, prev.y - 10);
	else if (i == 3)
		render_offset(game, &l->walk_3, prev.x - 12, prev.y - 18);
	else if (i == 4)
		render_offset(game, &l->walk_0, new.x + 12, new.y - 8);
	else if (i == 5)
		render_offset(game, &l->walk_1, new.x + 9, new.y + 6);
	else if (i == 6)
		render_offset(game, &l->walk_2, new.x + 6, new.y + 2);
	else if (i == 7)
		render_offset(game, &l->walk_3, new.x + 3, new.y - 4);
	else if (i > 7)
	{
		game->player.idle = true;
		i = -1;
	}
	i++;
}

void	walk_right(t_game *game, t_frames *r, t_pos prev, t_pos new)
{
	static int	i;

	if (i == 0)
		render_offset(game, &r->walk_0, prev.x + 3, prev.y - 8);
	else if (i == 1)
		render_offset(game, &r->walk_1, prev.x + 6, prev.y - 4);
	else if (i == 2)
		render_offset(game, &r->walk_2, prev.x + 9, prev.y - 10);
	else if (i == 3)
		render_offset(game, &r->walk_3, prev.x + 12, prev.y - 18);
	else if (i == 4)
		render_offset(game, &r->walk_0, new.x - 12, new.y - 8);
	else if (i == 5)
		render_offset(game, &r->walk_1, new.x - 9, new.y + 6);
	else if (i == 6)
		render_offset(game, &r->walk_2, new.x - 6, new.y + 2);
	else if (i == 7)
		render_offset(game, &r->walk_3, new.x - 3, new.y - 4);
	else if (i > 7)
	{
		game->player.idle = true;
		i = -1;
	}
	i++;
}

int	player_idle(t_game *game, t_pos current)
{
	static int	i;

	if (i >= 0 && i < 4)
	{
		if (game->player.direction == left)
			render_sprite(&game->display, &game->l.idle_0,
				current.x, current.y);
		else
			render_sprite(&game->display, &game->r.idle_0,
				current.x, current.y);
	}
	else if (i >= 4 && i < 8)
	{
		if (game->player.direction == left)
			render_sprite(&game->display, &game->l.idle_1,
				current.x, current.y);
		else
			render_sprite(&game->display, &game->r.idle_1,
				current.x, current.y);
		if (i == 7)
			i = -1;
	}
	i++;
	return (0);
}

void	player_walk(t_game *game, t_pos prev, t_pos new)
{
	prev.x *= IMG_SIZE;
	prev.y *= IMG_SIZE;
	new.x *= IMG_SIZE;
	new.y *= IMG_SIZE;
	if (game->player.direction == left)
		walk_left(game, &game->l, prev, new);
	else
		walk_right(game, &game->r, prev, new);
}

void	player_action(t_game *game)
{
	if (game->player.idle)
		player_idle(game, game->player.current);
	else if (!game->player.idle)
		player_walk(game, game->player.prev, game->player.current);
}
