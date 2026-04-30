/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:05:26 by radib             #+#    #+#             */
/*   Updated: 2026/05/01 00:00:05 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	wall_check(t_cube *c, float x, float y)
{
	if (c->map[(int)(x + 0.1)][(int)(y + 0.1)] == '1')
		return (1);
	if (c->map[(int)(x + 0.1)][(int)(y - 0.1)] == '1')
		return (1);
	if (c->map[(int)(x - 0.1)][(int)(y + 0.1)] == '1')
		return (1);
	if (c->map[(int)(x - 0.1)][(int)(y - 0.1)] == '1')
		return (1);
	return (0);
}

static void	moving_calculator(t_cube **c, int angle)
{
	float	x;
	float	y;

	x = 0.5f * sin(deg_to_rad(angle));
	y = -(0.5f * cos(deg_to_rad(angle)));
	if (!wall_check(*c, (*c)->pos_x + x, (*c)->pos_y + y))
	{
		(*c)->pos_x += x;
		(*c)->pos_y += y;
	}
	else if (!wall_check(*c, (*c)->pos_x + x, (*c)->pos_y))
		(*c)->pos_x += x;
	else if (!wall_check(*c, (*c)->pos_x, (*c)->pos_y + y))
		(*c)->pos_y += y;
	raycast(c, 0, (*c)->angle);
}

void	moving(t_cube **c, int key)
{
	if (key == 122)
		moving_calculator(c, fmodf((*c)->angle, 360.00f));
	if (key == 113)
		moving_calculator(c, fmodf(270 + (*c)->angle, 360.00f));
	if (key == 115)
		moving_calculator(c, fmodf(180 + (*c)->angle, 360.00f));
	if (key == 100)
		moving_calculator(c, fmodf(90 + (*c)->angle, 360.00f));
}
//115 bas
//100 droite
//113 gauche
//122 avant