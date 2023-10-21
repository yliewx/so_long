/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:32:44 by yliew             #+#    #+#             */
/*   Updated: 2023/09/06 10:38:08 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
/*
int	main(void)
{
	char	*test[8] = {"a", "A", "0", "7", "-", "Ë", "»", ""};
	int	i = 0;

	while (i < 8)
	{
		printf("%s: %i\n", test[i], ft_isascii((int)(*test[i])));
		i++;
	}
	return (0);
}
*/
