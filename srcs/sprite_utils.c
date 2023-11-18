/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:07:03 by yliew             #+#    #+#             */
/*   Updated: 2023/11/18 18:51:56 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	get_sprite_info(t_img *sprite)
{
	sprite->addr = mlx_get_data_addr(sprite->ptr, &sprite->bpp,
			&sprite->line_size, &sprite->endian);
}

unsigned int	get_pixel(t_img *sprite, int x, int y)
{
	return (*(unsigned int *)(sprite->addr + y * sprite->line_size
		+ x * (sprite->bpp / 8)));
}

/*don't copy the pixel if the colour is black ("transparent" bg)
or blue (funny xpm conversion issue)*/
void	put_pixel_to_base(t_img *base, int x, int y, int colour)
{
	char	*pos;

	if (colour == (int)0xFF000000 || colour == (int)0x0000A4FF)
		return ;
	if (y >= 0 && x >= 0 && y < base->y && x < base->x)
	{
		pos = base->addr + (y * base->line_size + x * (base->bpp / 8));
		*(unsigned int *)pos = colour;
	}
}

/*copy pixels from the player sprite to the base floor sprite
the parameters x and y refer to the x/y offset from pos 0,0 of the base*/
void	put_sprite_to_base(t_img *base, t_img *sprite, int x, int y)
{
	unsigned int	current_pixel;
	int				i;
	int				j;

	j = 0;
	while (j < sprite->y)
	{
		i = 0;
		while (i < sprite->x)
		{
			current_pixel = get_pixel(sprite, i, j);
			put_pixel_to_base(base, i + x, j + y, current_pixel);
			i++;
		}
		j++;
	}
}
