/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:46:30 by yliew             #+#    #+#             */
/*   Updated: 2023/11/12 18:50:45 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	init_variables(t_data *game)
{
	game->c.start = 0;
	game->c.coins = 0;
	game->c.exit = 0;
	game->c.movements = 0;
	game->map.rows = 0;
	game->map.columns = 0;
	game->map.valid_path = 0;
	game->map.arr = NULL;
}

void	init_sprites(t_data *game)
{
	new_sprite(game, &game->img_wall, WALL_XPM);
	new_sprite(game, &game->img_floor, FLOOR_XPM);
	new_sprite(game, &game->img_player, PLAYER_XPM);
	new_sprite(game, &game->img_coin, COIN_XPM);
	new_sprite(game, &game->img_exit, EXIT_XPM);
}

//check window screen size before creating window
void	init_game(char **argv)
{
	t_data	game;

	init_variables(&game);
	open_map(&game, argv[1]);
	check_valid_map(&game, &game.map, game.map.full_line);
	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr,
		IMG_SIZE * game.map.columns,
		IMG_SIZE * game.map.rows, "so_long");
	init_sprites(&game);
	render_map(&game, &game.map);
	//register key hook
	mlx_key_hook(game.win_ptr, test_keypress, &game);
	//loop over mlx pointer
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
