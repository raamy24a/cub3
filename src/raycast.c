/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:49 by radib             #+#    #+#             */
/*   Updated: 2026/03/18 15:11:29 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

float	deg_to_rad(float deg)
{
	return (deg * M_PI / 180.0);
}

float	angle_calc(float angle, float calc)
{
	angle = angle + calc - 33.33;
	if (angle < 0)
		angle = 360 - angle * -1;
	else if (angle >= 360)
		angle = fmodf(angle, 360.00);
	return (angle);
}

float	len_to_hit_grid_vertical(t_ray *raydata)
{
	return (1 - fmodf(raydata->cur_rpos_y, 1.00));
}

float	len_to_hit_grid_horizontal(t_ray *raydata)
{
	return (1 - fmodf(raydata->cur_rpos_x, 1.00));
}

int	top_left_rec(t_cube	*c, t_ray **r, float angles, int depth)
{
	float	opp;
	float	adj;
	float	hyp_w;
	float	hyp_n;

	if (depth > 30)
		return (42);
	opp = len_to_hit_grid_vertical(*r);
	adj = len_to_hit_grid_horizontal(*r);
	// printf("opp : %f adj : %f ", opp, adj);
	hyp_w = opp / (sin(deg_to_rad(angles)));
	hyp_n = adj / (cos(deg_to_rad(angles)));
	if (hyp_n < hyp_w)
	{
		(*r)->cur_rpos_x -= (float)sqrt((hyp_n * hyp_n) - (adj * adj));
		(*r)->cur_rpos_y = (int)(*r)->cur_rpos_y - 1;
		if (c->map[(int)(*r)->cur_rpos_x][(int)(*r)->cur_rpos_y] == '0')
			return (top_left_rec(c, r, angles, depth + 1), 1);
		return ((*r)->wall_pixel = fmodf((*r)->cur_rpos_x, 1.00f),
			(*r)->wall = 'n', 1);
	}
	(*r)->cur_rpos_y -= (float)sqrt((hyp_w * hyp_w) - (opp * opp));
	(*r)->cur_rpos_x = (int)(*r)->cur_rpos_x;
	if (c->map[(int)(*r)->cur_rpos_x][(int)(*r)->cur_rpos_y] == '0')
		return (top_left_rec(c, r, angles, depth + 1), 1);
	return ((*r)->wall_pixel = fmodf((*r)->cur_rpos_x, 1.00f),
		(*r)->wall = 'w', 1);
}

t_ray	*top_left(t_cube **c, float angles)
{
	t_ray	*raydata;
	float	a;
	float	b;

	raydata = malloc(sizeof(t_cube));
	raydata->cur_rpos_x = (*c)->pos_x;
	raydata->cur_rpos_y = (*c)->pos_y;
	top_left_rec((*c), &raydata, angles, 0);
	a = fabs(raydata->cur_rpos_x - (*c)->pos_x);
	b = fabs(raydata->cur_rpos_y - (*c)->pos_y);
	raydata->dist = (float)sqrt(a * a + b * b);
	return (raydata);
}
int	top_right_rec(t_cube *c, t_ray **r, float angles, char depth)
{
	float	opp;
	float	adj;
	float	hyp_e;
	float	hyp_n;

	if (depth > 30)
		return (42);
	opp = len_to_hit_grid_vertical(*r);
	adj = len_to_hit_grid_horizontal(*r);
	// printf("opp : %f adj : %f ", opp, adj);
	hyp_e = opp / (sin(deg_to_rad(angles)));
	hyp_n = adj / (cos(deg_to_rad(angles)));
	if (hyp_n < hyp_e)
	{
		(*r)->cur_rpos_x += (float)sqrt((hyp_n * hyp_n) - (adj * adj));
		(*r)->cur_rpos_y = (int)(*r)->cur_rpos_y - 1;
		if (c->map[(int)(*r)->cur_rpos_x][(int)(*r)->cur_rpos_y] == '0')
			return (top_right_rec(c, r, angles, depth + 1), 1);
		return ((*r)->wall_pixel = fmodf((*r)->cur_rpos_x, 1.00f),
			(*r)->wall = 'n', 1);
	}
	(*r)->cur_rpos_y -= (float)sqrt((hyp_e * hyp_e) - (opp * opp));
	(*r)->cur_rpos_x = (int)(*r)->cur_rpos_x;
	if (c->map[(int)(*r)->cur_rpos_x][(int)(*r)->cur_rpos_y] == '0')
		return (top_right_rec(c, r, angles, depth + 1), 1);
	return ((*r)->wall_pixel = fmodf((*r)->cur_rpos_x, 1.00f),
		(*r)->wall = 'e', 1);
}
t_ray	*top_right(t_cube **c, float angles)
{
	t_ray	*raydata;
	float	a;
	float	b;

	raydata = malloc(sizeof(t_cube));
	raydata->cur_rpos_x = (*c)->pos_x;
	raydata->cur_rpos_y = (*c)->pos_y;
	top_right_rec((*c), &raydata, angles, 0);
	a = fabs(raydata->cur_rpos_x - (*c)->pos_x);
	b = fabs(raydata->cur_rpos_y - (*c)->pos_y);
	raydata->dist = (float)sqrt(a * a + b * b);
	return (raydata);
}
int	bottom_left_rec(t_cube	*c, t_ray **r, float angles, char depth)
{
	float	opp;
	float	adj;
	float	hyp_w;
	float	hyp_s;

	if (depth > 30)
		return (42);
	opp = len_to_hit_grid_vertical(*r);
	adj = len_to_hit_grid_horizontal(*r);
	// printf("opp : %f adj : %f ", opp, adj);
	hyp_w = opp / (sin(deg_to_rad(angles)));
	hyp_s = adj / (cos(deg_to_rad(angles)));
	if (hyp_s < hyp_w)
	{
		(*r)->cur_rpos_x -= (float)sqrt((hyp_s * hyp_s) - (adj * adj));
		(*r)->cur_rpos_y = (int)(*r)->cur_rpos_y + 1;
		if (c->map[(int)(*r)->cur_rpos_x][(int)(*r)->cur_rpos_y] == '0')
			return (bottom_left_rec(c, r, angles, depth + 1), 1);
		return ((*r)->wall_pixel = fmodf((*r)->cur_rpos_x, 1.00f),
			(*r)->wall = 's', 1);
	}
	(*r)->cur_rpos_y += (float)sqrt((hyp_w * hyp_w) - (opp * opp));
	(*r)->cur_rpos_x = (int)(*r)->cur_rpos_x;
	if (c->map[(int)(*r)->cur_rpos_x][(int)(*r)->cur_rpos_y] == '0')
		return (bottom_left_rec(c, r, angles, depth + 1), 1);
	return ((*r)->wall_pixel = fmodf((*r)->cur_rpos_x, 1.00f),
		(*r)->wall = 'w', 1);
}
t_ray	*bottom_left(t_cube **c, float angles)
{
	t_ray	*raydata;
	float	a;
	float	b;

	raydata = malloc(sizeof(t_cube));
	raydata->cur_rpos_x = (*c)->pos_x;
	raydata->cur_rpos_y = (*c)->pos_y;
	bottom_left_rec((*c), &raydata, angles, 0);
	a = fabs(raydata->cur_rpos_x - (*c)->pos_x);
	b = fabs(raydata->cur_rpos_y - (*c)->pos_y);
	raydata->dist = (float)sqrt(a * a + b * b);
	return (raydata);
}

int	bottom_right_rec(t_cube	*c, t_ray **r, float angles, char depth)
{
	float	opp;
	float	adj;
	float	hyp_e;
	float	hyp_s;

	if (depth > 30)
		return (42);
	opp = len_to_hit_grid_vertical(*r);
	adj = len_to_hit_grid_horizontal(*r);
	// printf("opp : %f adj : %f ", opp, adj);
	hyp_e = opp / (sin(deg_to_rad(angles)));
	hyp_s = adj / (cos(deg_to_rad(angles)));
	if (hyp_s < hyp_e)
	{
		(*r)->cur_rpos_x += (float)sqrt((hyp_s * hyp_s) - (adj * adj));
		(*r)->cur_rpos_y = (int)(*r)->cur_rpos_y + 1;
		if (c->map[(int)(*r)->cur_rpos_x][(int)(*r)->cur_rpos_y] == '0')
			return (bottom_right_rec(c, r, angles, depth + 1), 1);
		return ((*r)->wall_pixel = fmodf((*r)->cur_rpos_x, 1.00f),
			(*r)->wall = 's', 1);
	}
	(*r)->cur_rpos_y += (float)sqrt((hyp_e * hyp_e) - (opp * opp));
	(*r)->cur_rpos_x = (int)(*r)->cur_rpos_x + 1;
	if (c->map[(int)(*r)->cur_rpos_x][(int)(*r)->cur_rpos_y] == '0')
		return (bottom_right_rec(c, r, angles, depth + 1), 1);
	return ((*r)->wall_pixel = fmodf((*r)->cur_rpos_x, 1.00f),
		(*r)->wall = 'e', 1);
}

t_ray	*bottom_right(t_cube **c, float angles)
{
	t_ray	*raydata;
	float	a;
	float	b;

	raydata = malloc(sizeof(t_cube));
	raydata->cur_rpos_x = (*c)->pos_x;
	raydata->cur_rpos_y = (*c)->pos_y;
	bottom_right_rec((*c), &raydata, angles, 0);
	a = fabs(raydata->cur_rpos_x - (*c)->pos_x);
	b = fabs(raydata->cur_rpos_y - (*c)->pos_y);
	raydata->dist = (float)sqrt(a * a + b * b);
	return (raydata);
}

t_ray	*angle_choser(t_cube **c, float angles)
{
	// printf("%f\n", angles);
	if (angles >= 0 && angles < 90)
		return (top_right(c, angles));
	if (angles >= 90 && angles < 180)
		return (bottom_right(c, fmod(angles, 90.00)));
	if (angles >= 180 && angles < 270)
		return (bottom_left(c, fmod(angles, 90.00)));
	if (angles >= 270 && angles < 360)
		return (top_left(c, fmod(angles, 90.00)));
	return (0);
}

int	find_color(int a)
{
	if (a == 'n')
		return (0xff0000);
	else if (a == 's')
		return (0xffff00);
	else if (a == 'e')
		return (0xffffff);
	else if (a == 'w')
		return (0x00ffff);
	return (0);
}

void	draw_wall_height_line(t_ray *raydata, t_img **displayed_img, t_cube *p, int x)
{
	int		i;
	float	y;
	int		color;
	int		wall_size;

	wall_size = p->height / raydata->dist;
	color = find_color(raydata->wall);
	i = p->height - (p->height - wall_size) / 2;
	y = (p->height - wall_size) / 2;
	if (y < 0)
		y = 0;
	//temp fix to fix later
	while (y < i && y < p->height)
	{
		put_pixel_to_image((*displayed_img), x, (int)y, color);
		y++;
	}
}

void    raycast(t_cube **c, int i, float angles)
{
    t_cube      *p;
    float    corrected_dist;

    p = *c;
    while (i < p->width)
    {
        angles = angle_calc(p->angle, 66.66 / (float)p->width * i);
        p->raydata[i] = angle_choser(c, angles);
        if (!p->raydata[i])
            printf("angle : %f, width pixel : %d ray error\n", angles, i);
        corrected_dist = p->raydata[i]->dist * cos(deg_to_rad(p->angle -angles));
        p->raydata[i]->dist = corrected_dist;
        i++;
    }
    i = 0;
    render_roof(10000 * 0 + 100 * 20 + 20, c);
    render_floor(300 * 10000 + 100 * 100 + 50, c);
    p->displayed_img = p->roof_and_ground;
    while (i < p->width)
    {
        draw_wall_height_line(p->raydata[i], &p->displayed_img, p, i);
        i++;
    }
    mlx_clear_window(p->m_ptr, p->w_ptr);
    mlx_put_image_to_window(p->m_ptr, p->w_ptr, p->displayed_img->img, 0, 0);
}