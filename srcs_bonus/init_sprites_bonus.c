/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:35:32 by yliew             #+#    #+#             */
/*   Updated: 2023/11/21 18:06:30 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

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

void	init_left_frames(t_game *game, t_frames *l)
{
	new_sprite(game, &l->idle_0, IDLE_0_L_XPM);
	new_sprite(game, &l->idle_1, IDLE_1_L_XPM);
	new_sprite(game, &l->walk_0, WALK_0_L_XPM);
	new_sprite(game, &l->walk_1, WALK_1_L_XPM);
	new_sprite(game, &l->walk_2, WALK_2_L_XPM);
	new_sprite(game, &l->walk_3, WALK_3_L_XPM);
}

void	init_right_frames(t_game *game, t_frames *r)
{
	new_sprite(game, &r->idle_0, IDLE_0_R_XPM);
	new_sprite(game, &r->idle_1, IDLE_1_R_XPM);
	new_sprite(game, &r->walk_0, WALK_0_R_XPM);
	new_sprite(game, &r->walk_1, WALK_1_R_XPM);
	new_sprite(game, &r->walk_2, WALK_2_R_XPM);
	new_sprite(game, &r->walk_3, WALK_3_R_XPM);
}

void	init_enemy_frames(t_game *game, t_frames *enemy)
{
	new_sprite(game, &enemy->walk_0, ENEMY_0_XPM);
	new_sprite(game, &enemy->walk_1, ENEMY_1_XPM);
	new_sprite(game, &enemy->walk_2, ENEMY_2_XPM);
	new_sprite(game, &enemy->walk_3, ENEMY_3_XPM);
	new_sprite(game, &enemy->walk_4, ENEMY_4_XPM);
	new_sprite(game, &enemy->walk_5, ENEMY_5_XPM);
	new_sprite(game, &enemy->walk_6, ENEMY_6_XPM);
	new_sprite(game, &enemy->walk_7, ENEMY_7_XPM);
}

void	init_sprites(t_game *game)
{
	init_wall_sprites(game);
	init_left_frames(game, &game->l);
	init_right_frames(game, &game->r);
	init_enemy_frames(game, &game->en);
	new_sprite(game, &game->img_floor, FLOOR_XPM);
	new_sprite(game, &game->img_exit_0, EXIT_0_XPM);
	new_sprite(game, &game->img_exit_1, EXIT_1_XPM);
	new_sprite(game, &game->img_coin, COIN_XPM);
}
