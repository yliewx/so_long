/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:46:30 by yliew             #+#    #+#             */
/*   Updated: 2023/10/21 17:55:57 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_game(char *message, t_data *data, int exit_code)
{
	if (message)
		ft_putstr_fd(message, 2);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	exit(exit_code);
}

int	test_keypress(int keysym, t_data *data)
{
	printf("Key pressed: %i\n%p\n", keysym, data->win_ptr);
	if (keysym == W_KEY || keysym == UP_KEY)
		printf("up!\n");
	if (keysym == ESC)
		exit_game("Exiting game.\n", data, 0);
	return (0);
}

int	is_rectangle(t_map *map)
{
	int	i;

	i = 0;
	while (map->arr[i] && map->arr[i + 1])
	{
		if (ft_strlen(map->arr[i]) != ft_strlen(map->arr[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

int	check_map(t_data *game, t_map *map, char *line)
{
	if (!ft_strchr(line, 'E'))
		exit_game("Invalid map: No exit found.\n", game, 1);
	else if (!ft_strchr(line, 'C'))
		exit_game("Invalid map: No collectible found.\n", game, 1);
	else if (!ft_strchr(line, 'P'))
		exit_game("Invalid map: No start pos found.\n", game, 1);
	map->arr = ft_split(line, '\n');
	if (!is_rectangle(map))
		exit_game("Invalid map: Must be rectangular.\n", game, 1);
	return (1);
}

void	open_map(t_data *game, char *map_path)
{
	t_map	new_map;
	char	*current_line;
	char	*total_lines;
	char	*temp;
	int	i = 0;

	new_map.fd = open(map_path, O_RDONLY);
	if (new_map.fd == -1)
		exit_game("Could not open file.\n", game, 1);
	total_lines = ft_calloc(1, 1);
	if (!total_lines)
		exit_game("Error allocating memory for map.\n", game, 1);
	while (1)
	{
		current_line = get_next_line(new_map.fd);
		if (!current_line)
			break ;
		temp = total_lines;
		total_lines = ft_strjoin(temp, current_line);
		free(temp);
	}
	if (check_map(game, &new_map, total_lines))
		printf("valid map\n");
	game->map = new_map;
	while (i < 3)
	{
		printf("%s\n", game->map.arr[i]);
		i++;
	}
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
	//check map
	open_map(&game, argv[1]);
	//register key hook
	mlx_key_hook(game.win_ptr, test_keypress, &game);
	//loop over mlx pointer
	mlx_loop(game.mlx_ptr);
	printf("%p, %p, end test\n", game.mlx_ptr, game.win_ptr);
	return (0);
}
