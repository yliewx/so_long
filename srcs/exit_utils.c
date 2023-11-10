/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:37:53 by yliew             #+#    #+#             */
/*   Updated: 2023/11/10 12:11:41 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	end(char *message, t_data *data, int exit_code)
{
	if (exit_code != 0)
		ft_putstr_fd("Error\n", 2);
	if (message)
		ft_putstr_fd(message, 2);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	exit(exit_code);
}
