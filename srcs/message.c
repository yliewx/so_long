/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:43:36 by yliew             #+#    #+#             */
/*   Updated: 2023/11/28 20:43:47 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	print_victory(t_game *game)
{
	ft_printf(GREEN
		":'######::::::'###::::'##::::'##:'########:\n"\
	"'##... ##::::'## ##::: ###::'###: ##.....::\n"\
	" ##:::..::::'##:. ##:: ####'####: ##:::::::\n"\
	" ##::'####:'##:::. ##: ## ### ##: ######:::\n"\
	" ##::: ##:: #########: ##. #: ##: ##...::::\n"\
	" ##::: ##:: ##.... ##: ##:.:: ##: ##:::::::\n"\
	". ######::: ##:::: ##: ##:::: ##: ########:\n"\
	":......::::..:::::..::..:::::..::........::\n"\
	":'######::'##:::::::'########::::'###::::'########::'####:\n"\
	"'##... ##: ##::::::: ##.....::::'## ##::: ##.... ##: ####:\n"\
	" ##:::..:: ##::::::: ##::::::::'##:. ##:: ##:::: ##: ####:\n"\
	" ##::::::: ##::::::: ######:::'##:::. ##: ########::: ##::\n"\
	" ##::::::: ##::::::: ##...:::: #########: ##.. ##::::..:::\n"\
	" ##::: ##: ##::::::: ##::::::: ##.... ##: ##::. ##::'####:\n"\
	". ######:: ########: ########: ##:::: ##: ##:::. ##: ####:\n"\
	":......:::........::........::..:::::..::..:::::..::....::\n"RESET);
	end("You win!\n", game, 0);
}

void	print_msg(char *message, int fd)
{
	char	*colour;

	if (fd == 2)
		colour = RED;
	else
		colour = GREEN;
	ft_putstr_fd(colour, fd);
	ft_putstr_fd(message, fd);
	ft_putstr_fd(RESET, fd);
}

void	print_extra_msg(t_game *game)
{
	static int	i;

	if (i >= 0 && i < 6)
		ft_printf(RED"You still have %i eggs to collect!\n"RESET,
			game->map.coins - game->player.coins);
	else if (i >= 6 && i < 20)
		ft_printf(RED"Your eggventure isn't over yet!\n"RESET);
	else if (i >= 20 && i < 41)
		ft_printf(RED"You should be searching for eggs, "\
			"not Easter eggs. (%i)\n", i + 1);
	else if (i == 41)
		ft_printf(GREEN"\nYou've knocked on this door a grand total "\
			"of 42 times. Congratulations!\nUnfortunately, "\
			"42 is not the answer to this game.\n\n");
	else if (i > 41)
		ft_printf(RED"You still have %i eggs to collect!\n"RESET,
			game->map.coins - game->player.coins);
	i++;
}
