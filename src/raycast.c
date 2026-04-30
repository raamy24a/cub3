/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:49 by radib             #+#    #+#             */
/*   Updated: 2026/04/30 23:45:49 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	raycast_recursive(t_cube	*c, t_ray **r, float angles)
{
	float	opp;
	float	adj;
	float	hyp_e;
	float	hyp_s;

	opp = len_to_hit_grid_vertical(*r, (*r)->x_mult);
	adj = len_to_hit_grid_horizontal(*r, (*r)->y_mult);
	hyp_e = opp / (sin(deg_to_rad(angles)));
	hyp_s = adj / (cos(deg_to_rad(angles)));
	if (hyp_s < hyp_e)
	{
		(*r)->rpos_x += sqrt((hyp_s * hyp_s) - (adj * adj)) * (*r)->x_mult;
		(*r)->rpos_y += adj * (*r)->y_mult;
		if (c->map[(int)(*r)->rpos_x - pos_cor((*r)->rpos_x, (*r)->x_mult)]
			[(int)(*r)->rpos_y - pos_cor((*r)->rpos_y, (*r)->y_mult)] != '1')
			return (raycast_recursive(c, r, angles), 1);
		return ((wall_hit(2 + (*r)->y_mult, r, c,
					fmodf((*r)->rpos_x, 1.00f)), 1));
	}
	(*r)->rpos_y += sqrt((hyp_e * hyp_e) - (opp * opp)) * (*r)->y_mult;
	(*r)->rpos_x += opp * (*r)->x_mult;
	if (c->map[(int)(*r)->rpos_x - pos_cor((*r)->rpos_x, (*r)->x_mult)]
		[(int)(*r)->rpos_y - pos_cor((*r)->rpos_y, (*r)->y_mult)] != '1')
		return (raycast_recursive(c, r, angles), 1);
	return (wall_hit(1 + (*r)->x_mult, r, c, fmodf((*r)->rpos_y, 1.00f)), 1);
}

t_ray	*init_recursion(t_cube **c, float angles
	, char direction, t_ray *raydata)
{
	float	a;
	float	b;

	init_ray(raydata, direction, c);
	raycast_recursive((*c), &raydata, angles);
	a = fabs(raydata->rpos_x - (*c)->pos_x);
	b = fabs(raydata->rpos_y - (*c)->pos_y);
	raydata->dist = (float)sqrt(a * a + b * b);
	return (raydata);
}

t_ray	*angle_choser(t_cube **c, float angles, t_ray *raydata)
{
	char	direction;

	if (angles >= 0 && angles < 90)
		direction = 0;
	if (angles >= 90 && angles < 180)
		direction = 1;
	if (angles >= 180 && angles < 270)
		direction = 2;
	if (angles >= 270 && angles < 360)
		direction = 3;
	angles = fmod(angles, 90.00f);
	if ((direction == 1 || direction == 3))
		angles = 90.0f - angles;
	angles = fmod(angles, 90.00f);
	if (!angles)
	{
		if (direction == 1 || direction == 3)
			angles = 89.999f;
		else
			angles = 0.001f;
	}
	return (init_recursion(c, angles, direction, raydata));
}

void	raycast(t_cube **c, int i, float angles)
{
	float	corr_dist;
	t_cube	*p;
	t_ray	*raydata;

	p = *c;
	raydata = ft_calloc(1, sizeof(t_ray));
	render_roof((*c)->roof, c);
	render_floor((*c)->floor, c);
	p->displayed_img = p->roof_and_ground;
	while (i < p->width)
	{
		angles = angle_calc(p->angle, \
		atan((i - p->width / 2.0f) / (p->width / 2.0f) * \
		tan(p->fov / 2 * M_PI / 180.0f)) * 180.0f / M_PI);
		raydata = angle_choser(c, angles, raydata);
		corr_dist = raydata->dist * cos(deg_to_rad(p->angle - angles));
		raydata->dist = corr_dist;
		draw_wall_height_line(raydata, &p->displayed_img, p, i);
		i++;
	}
	mlx_clear_window(p->m_ptr, p->w_ptr);
	p->displayed_img = p->roof_and_ground;
	mlx_put_image_to_window(p->m_ptr, p->w_ptr, p->displayed_img->img, 0, 0);
}
