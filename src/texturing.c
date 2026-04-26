/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:39:51 by radib             #+#    #+#             */
/*   Updated: 2026/04/25 15:40:30 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	get_pixel_from_image(t_img *img, int x, int y)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(int *)pixel);
}

void	draw_wall_height_line(t_ray *r, t_img **img, t_cube *p, int x)
{
	float	proj_dist;
	int		wall_size;
	int		wall_end;
	float	y;
	int		color;

	proj_dist = (p->width / 2.0f) / tanf(deg_to_rad(p->fov / 2));
	wall_size = (int)(proj_dist / r->dist);
	wall_end = p->height - (p->height - wall_size) / 2;
	y = (p->height - wall_size) / 2;
	if (y < 0)
		y = 0;
	while (y < wall_end && y < p->height)
	{
		color = get_pixel_from_image(r->wall, 128 * r->wall_pixel, \
			(int)((128.00f / wall_size) * (y - (p->height - wall_size) / 2)));
		put_pixel_to_image(*img, x, (int)y, color);
		y++;
	}
}
