/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:46:30 by yliew             #+#    #+#             */
/*   Updated: 2023/11/16 16:57:49 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_variables(t_data *game)
{
	game->map.rows = 0;
	game->map.columns = 0;
	game->map.start = 0;
	game->map.coins = 0;
	game->map.exit = 0;
	game->map.valid_path = false;
	game->map.grid = NULL;
	game->player.direction = left;
	game->current.coins = 0;
	game->current.movements = 0;
	game->current.exit_found = false;
}

void	init_window(t_data *game)
{
	int	window_x;
	int	window_y;

	window_x = IMG_SIZE * game->map.columns;
	window_y = IMG_SIZE * game->map.rows;
	mlx_get_screen_size(game->mlx_ptr, &game->screen_x, &game->screen_y);
	if (window_x > game->screen_x || window_y > game->screen_y)
		end("Map size is too large.\n", game, 1);
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			window_x, window_y, "so_long");
}

void	init_sprites(t_data *game)
{
	new_sprite(game, &game->img_wall, WALL_XPM);
	new_sprite(game, &game->img_floor, FLOOR_XPM);
	new_sprite(game, &game->img_exit, EXIT_XPM);
	new_sprite(game, &game->base_player_L, FLOOR_XPM);
	new_sprite(game, &game->base_player_R, FLOOR_XPM);
	new_sprite(game, &game->img_player_L, PLAYER_IDLE_L_XPM);
	new_sprite(game, &game->img_player_R, PLAYER_IDLE_R_XPM);
	put_sprite_to_base(&game->base_player_L, &game->img_player_L, 0, 0);
	put_sprite_to_base(&game->base_player_R, &game->img_player_R, 0, 0);
	new_sprite(game, &game->base_coin, FLOOR_XPM);
	new_sprite(game, &game->img_coin, COIN_XPM);
	put_sprite_to_base(&game->base_coin, &game->img_coin, 16, 24);
}

//move "game.map.valid_path = 1" to the relevant function later
void	init_game(char **argv)
{
	t_data	game;

	init_variables(&game);
	open_map(&game, argv[1]);
	set_map_params(&game.map, game.map.full_line);
	check_valid_map(&game, &game.map, game.map.full_line);
	game.map.valid_path = 1;
	game.mlx_ptr = mlx_init();
	init_sprites(&game);
	init_window(&game);
	render_map(&game, &game.map);
	mlx_key_hook(game.win_ptr, check_keypress, &game);
	mlx_hook(game.win_ptr, 17, 0, close_game, &game);
	mlx_loop(game.mlx_ptr);
}

//take 1 arg: map description file ending with .ber
int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		print_msg("Please enter 1 argument.\n", 2);
		return (0);
	}
	else if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4))
	{
		print_msg("File must end with .ber extension.\n", 2);
		return (0);
	}
	init_game(argv);
	return (0);
}
