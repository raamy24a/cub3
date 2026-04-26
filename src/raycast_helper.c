/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:49 by radib             #+#    #+#             */
/*   Updated: 2026/04/25 15:41:59 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

float	round_or_minus(float number)
{
	if (!fmodf(number, 1.00f))
		return (number - 1);
	return (floor(number));
}

float	deg_to_rad(float deg)
{
	return (deg * M_PI / 180.0);
}

float	angle_calc(float angle, float calc)
{
	angle = angle + calc;
	if (angle < 0)
		angle = 360 - angle * -1;
	else if (angle >= 360)
		angle = fmodf(angle, 360.00);
	return (angle);
}

float	len_to_hit_grid_vertical(t_ray *raydata, int dir)
{
	if (dir == 1)
		return (1 - fmodf(raydata->rpos_x, 1.00));
	else if (fmodf(raydata->rpos_x, 1.00) == 0)
		return (1);
	return (fmodf(raydata->rpos_x, 1.00));
}

float	len_to_hit_grid_horizontal(t_ray *raydata, int dir)
{
	if (dir == 1)
		return (1 - fmodf(raydata->rpos_y, 1.00));
	else if (fmodf(raydata->rpos_y, 1.00) == 0)
		return (1);
	return (fmodf(raydata->rpos_y, 1.00));
}
