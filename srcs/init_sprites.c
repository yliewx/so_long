/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:35:32 by yliew             #+#    #+#             */
/*   Updated: 2023/11/21 12:30:20 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_wall_sprites(t_game *game)
{
	new_sprite(game, &game->wall.up_l, WALL_UP_L_XPM);
	new_sprite(game, &game->wall.up_m, WALL_UP_M_XPM);
	new_sprite(game, &game->wall.up_r, WALL_UP_R_XPM);
	new_sprite(game, &game->wall.down_l, WALL_DOWN_L_XPM);
	new_sprite(game, &game->wall.down_m, WALL_DOWN_M_XPM);
	new_sprite(game, &game->wall.down_r, WALL_DOWN_R_XPM);
	new_sprite(game, &game->wall.side_l, WALL_SIDE_L_XPM);
	new_sprite(game, &game->wall.side_m, WALL_SIDE_M_XPM);
	new_sprite(game, &game->wall.side_r, WALL_SIDE_R_XPM);
	new_sprite(game, &game->wall.blank, WALL_XPM);
}

void	init_sprites(t_game *game)
{
	init_wall_sprites(game);
	new_sprite(game, &game->img_player_l, IDLE_L_XPM);
	new_sprite(game, &game->img_player_r, IDLE_R_XPM);
	new_sprite(game, &game->img_coin, COIN_XPM);
	new_sprite(game, &game->img_floor, FLOOR_XPM);
	new_sprite(game, &game->img_exit_0, EXIT_0_XPM);
	new_sprite(game, &game->img_exit_1, EXIT_1_XPM);
}
