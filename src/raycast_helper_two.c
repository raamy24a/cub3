/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helper_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:49 by radib             #+#    #+#             */
/*   Updated: 2026/04/26 14:35:54 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	pos_cor(float pos, int mult)
{
	if (mult == -1 && fmodf(pos, 1.0f) == 0)
		return (1);
	return (0);
}

void	wall_hit(int wall, t_ray **r, t_cube *c, float wall_pixel)
{
	(*r)->wall_pixel = wall_pixel;
	if (wall == wall_north)
	{
		(*r)->wall = c->wall_n;
	}
	if (wall == wall_east)
	{
		(*r)->wall = c->wall_e;
	}
	if (wall == wall_south)
	{
		(*r)->wall = c->wall_s;
	}
	if (wall == wall_west)
	{
		(*r)->wall = c->wall_w;
	}
}

void	init_ray(t_ray *ray, char dir, t_cube **c)
{
	ray->rpos_x = (*c)->pos_x;
	ray->rpos_y = (*c)->pos_y;
	if (dir == 0)
	{
		ray->x_mult = 1;
		ray->y_mult = -1;
	}
	if (dir == 1)
	{
		ray->x_mult = 1;
		ray->y_mult = 1;
	}
	if (dir == 2)
	{
		ray->x_mult = -1;
		ray->y_mult = 1;
	}
	if (dir == 3)
	{
		ray->x_mult = -1;
		ray->y_mult = -1;
	}
}
