/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:05:26 by radib             #+#    #+#             */
/*   Updated: 2026/03/23 20:10:29 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	moving_calculator(t_cube **c, int angle)
{
	(*c)->pos_x = (*c)->pos_x + sin(deg_to_rad(angle));
	(*c)->pos_y = (*c)->pos_y - cos(deg_to_rad(angle));
	raycast(c, 0, (*c)->angle);
}

void	moving(t_cube **c, int key)
{
	if (key == 119)
		moving_calculator(c, fmodf((*c)->angle, 360.00f));
	if (key == 97)
		moving_calculator(c, fmodf(270 + (*c)->angle, 360.00f));
	if (key == 115)
		moving_calculator(c, fmodf(180 + (*c)->angle, 360.00f));
	if (key == 100)
		moving_calculator(c, fmodf(90 + (*c)->angle, 360.00f));
}