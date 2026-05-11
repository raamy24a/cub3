/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:41 by radib             #+#    #+#             */
/*   Updated: 2026/05/11 11:11:07 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render_floor_and_roof(int color, t_cube **c)
{
	int		x;
	int		y;

	y = 0;
	while (y < (*c)->height / 2)
	{
		x = 0;
		while (x < (*c)->width)
		{
			put_pixel_to_image((*c)->roof_and_ground, x, y, color);
			x++;
		}
		y++;
	}
	while (y < (*c)->height)
	{
		x = 0;
		while (x < (*c)->width)
		{
			put_pixel_to_image((*c)->roof_and_ground, x, y, color);
			x++;
		}
		y++;
	}
}
