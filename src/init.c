/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:28 by radib             #+#    #+#             */
/*   Updated: 2026/04/26 14:35:42 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	angle_calculator(char angle)
{
	if (angle == 'N')
		return (0);
	else if (angle == 'E')
		return (90);
	else if (angle == 'S')
		return (180);
	else if (angle == 'W')
		return (270);
	return (0);
}

void	init_quadrants(t_quadrants **quad)
{
	(*quad)->top_rx = 1;
	(*quad)->top_ry = -1;
	(*quad)->bot_rx = 1;
	(*quad)->bot_ry = 1;
	(*quad)->bot_lx = -1;
	(*quad)->bot_ly = 1;
	(*quad)->top_lx = -1;
	(*quad)->top_ly = -1;
}
