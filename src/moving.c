/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:05:26 by radib             #+#    #+#             */
/*   Updated: 2026/04/26 14:00:57 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	wall_check(t_cube *c, int angle)
{
	if (c->map[(int)(c->pos_x + 1.2f * sin(deg_to_rad(angle)))] \
	[(int)(c->pos_y - (1.2f * cos(deg_to_rad(angle))))] == '1')
		return (1);
	return (0);
}

static void	moving_calculator(t_cube **c, int angle)
{
	if (wall_check(*c, angle))
		return ;
	(*c)->pos_x = (*c)->pos_x + 0.5f * sin(deg_to_rad(angle));
	(*c)->pos_y = (*c)->pos_y - 0.5f * cos(deg_to_rad(angle));
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