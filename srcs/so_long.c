/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:46:30 by yliew             #+#    #+#             */
/*   Updated: 2023/11/10 12:12:11 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	test_keypress(int keysym, t_data *data)
{
	printf("Key pressed: %i\n%p\n", keysym, data->win_ptr);
	if (keysym == W_KEY || keysym == UP_KEY)
		printf("up!\n");
	if (keysym == ESC)
		end("Quitting game.\n", data, 0);
	return (0);
}

void	set_variables(t_data *game)
{
	game->start_pos = 0;
	game->coins = 0;
	game->exit = 0;
}

//change to take 1 arg: map description file ending with .ber
int	main(int argc, char **argv)
{
	t_data	game;

	if (argc != 2)
	{
		ft_putstr_fd("Please enter 1 argument.\n", 2);
		return (0);
	}
	//initialise mlx
	game.mlx_ptr = mlx_init();
	//initialise window
	game.win_ptr = mlx_new_window(game.mlx_ptr, 500, 500, "test title");
	set_variables(&game);
	//check map
	open_map(&game, argv[1]);
	//register key hook
	mlx_key_hook(game.win_ptr, test_keypress, &game);
	//loop over mlx pointer
	mlx_loop(game.mlx_ptr);
	printf("%p, %p, end test\n", game.mlx_ptr, game.win_ptr);
	return (0);
}
