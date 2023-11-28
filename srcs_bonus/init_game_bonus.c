/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:46:30 by yliew             #+#    #+#             */
/*   Updated: 2023/11/23 17:57:48 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	init_variables(t_game *game)
{
	game->map.rows = 0;
	game->map.columns = 0;
	game->map.start = 0;
	game->map.coins = 0;
	game->map.enemies = 0;
	game->map.exit = 0;
	game->map.exit_found = false;
	game->map.valid_path = false;
	game->map.grid = NULL;
	game->player.coins = 0;
	game->player.movements = 0;
	game->player.direction = left;
	game->player.idle = true;
	game->enemy.direction = up;
}

void	init_window(t_game *game)
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
	game->display.ptr = mlx_new_image(game->mlx_ptr, window_x, window_y);
	game->display.x = window_x;
	game->display.y = window_y;
	get_sprite_info(&game->display);
}

int	update_handler(t_game *game)
{
	if (game->map.enemies > 0)
		check_enemy(game, &game->enemy, game->map.grid,
			&game->enemy.direction);
	render_map(game, &game->map);
	player_action(game);
	render_to_window(game, &game->display, 0, 0);
	update_move_count(game);
	return (0);
}

void	init_game(char **argv)
{
	t_game	game;

	init_variables(&game);
	open_map(&game, argv[1]);
	set_map_params(&game.map);
	check_valid_map(&game, &game.map, game.map.full_line);
	game.mlx_ptr = mlx_init();
	init_sprites(&game);
	init_window(&game);
	mlx_key_hook(game.win_ptr, key_handler, &game);
	mlx_hook(game.win_ptr, ON_DESTROY, 0, x_close_window, &game);
	mlx_loop_hook(game.mlx_ptr, update_handler, &game);
	mlx_loop(game.mlx_ptr);
}

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
