/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:49 by radib             #+#    #+#             */
/*   Updated: 2026/03/23 15:38:07 by radib            ###   ########.fr       */
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
		return (1 - fmodf(raydata->cur_rpos_x, 1.00));
	else if (fmodf(raydata->cur_rpos_x, 1.00) == 0)
		return (1);
	return (fmodf(raydata->cur_rpos_x, 1.00));
}

float	len_to_hit_grid_horizontal(t_ray *raydata, int dir)
{
	if (dir == 1)
		return (1 - fmodf(raydata->cur_rpos_y, 1.00));
	else if (fmodf(raydata->cur_rpos_y, 1.00) == 0)
		return (1);
	return (fmodf(raydata->cur_rpos_y, 1.00));
}

	// int	top_left_rec(t_cube	*c, t_ray **r, float angles, int depth)
	// {
	// float	opp;
	// float	adj;
	// float	hyp_w;
	// float	hyp_n;

	// if (depth > 30)
	// 	return (42);
	// opp = len_to_hit_grid_vertical(*r, 'w');
	// adj = len_to_hit_grid_horizontal(*r, 'n');
	// // printf("opp : %f adj : %f ", opp, adj);
	// hyp_w = opp / (sin(deg_to_rad(angles)));
	// hyp_n = adj / (cos(deg_to_rad(angles)));
	// if (hyp_n < hyp_w)
	// {
	// 	(*r)->cur_rpos_x -= (float)sqrt((hyp_n * hyp_n) - (adj * adj));
	// 	(*r)->cur_rpos_y -= adj;
	// 	if (c->map[(int)(*r)->cur_rpos_x - 1][(int)(*r)->cur_rpos_y - 1] == '0')
	// 		return (top_left_rec(c, r, angles, depth + 1), 1);
	// 	return ((*r)->wall_pixel = fmodf((*r)->cur_rpos_x, 1.00f),
	// 		(*r)->wall = 'w', 1);
	// }
	// (*r)->cur_rpos_y -= (float)sqrt((hyp_w * hyp_w) - (opp * opp));
	// (*r)->cur_rpos_x = round_or_minus((*r)->cur_rpos_y);
	// if (c->map[(int)(*r)->cur_rpos_x - 1][(int)(*r)->cur_rpos_y - 1] == '0')
	// 	return (top_left_rec(c, r, angles, depth + 1), 1);
	// return ((*r)->wall_pixel = fmodf((*r)->cur_rpos_x, 1.00f),
	// 	(*r)->wall = 'n', 1);
	// }

	// t_ray	*top_left(t_cube **c, float angles)
	// {
	// t_ray	*raydata;
	// float	a;
	// float	b;

	// raydata = malloc(sizeof(t_cube));
	// raydata->cur_rpos_x = (*c)->pos_x;
	// raydata->cur_rpos_y = (*c)->pos_y;
	// top_left_rec((*c), &raydata, angles, 0);
	// a = fabs(raydata->cur_rpos_x - (*c)->pos_x);
	// b = fabs(raydata->cur_rpos_y - (*c)->pos_y);
	// raydata->dist = (float)sqrt(a * a + b * b);
	// return (raydata);
	// }
	// int top_right_rec(t_cube *c, t_ray **r, float angles, char depth)
	// {
	// float   opp;
	// float   adj;
	// float   hyp_e;
	// float   hyp_n;
	// if (depth > 30)
	// 	return (42);
	// opp = len_to_hit_grid_vertical(*r, 'e');
	// adj = len_to_hit_grid_horizontal(*r, 'n');
	// hyp_e = opp / (sin(deg_to_rad(angles)));
	// hyp_n = adj / (cos(deg_to_rad(angles)));
	// if (hyp_e < hyp_n)
	// {
	// 	(*r)->cur_rpos_y -= sqrt((hyp_e * hyp_e) - (opp * opp));
	// 	(*r)->cur_rpos_x = round_or_minus((*r)->cur_rpos_x);
	// 	if (c->map[(int)(*r)->cur_rpos_x - 1][(int)(*r)->cur_rpos_y - 1] == '0')
	// 		return (top_right_rec(c, r, angles, depth + 1), 1);
	// 	return ((*r)->wall_pixel = fmodf((*r)->cur_rpos_x, 1.00f),
	// 		(*r)->wall = 'n', 1);
	// }
	// (*r)->cur_rpos_x += sqrt((hyp_n * hyp_n) - (adj * adj));
	// (*r)->cur_rpos_y = round_or_minus((*r)->cur_rpos_y);
	// if (c->map[(int)(*r)->cur_rpos_x - 1][(int)(*r)->cur_rpos_y - 1] == '0')
	// 	return (top_right_rec(c, r, angles, depth + 1), 1);
	// return ((*r)->wall_pixel = fmodf((*r)->cur_rpos_x, 1.00f),
	// 	(*r)->wall = 'e', 1);
	// }
	// t_ray	*top_right(t_cube **c, float angles)
	// {
	// t_ray	*raydata;
	// float	a;
	// float	b;

	// raydata = malloc(sizeof(t_cube));
	// raydata->cur_rpos_x = (*c)->pos_x;
	// raydata->cur_rpos_y = (*c)->pos_y;
	// top_right_rec((*c), &raydata, angles, 0);
	// a = fabs(raydata->cur_rpos_x - (*c)->pos_x);
	// b = fabs(raydata->cur_rpos_y - (*c)->pos_y);
	// raydata->dist = (float)sqrt(a * a + b * b);
	// return (raydata);
	// }
	// int	bottom_left_rec(t_cube	*c, t_ray **r, float angles, char depth)
	// {
	// float	opp;
	// float	adj;
	// float	hyp_w;
	// float	hyp_s;

	// if (depth > 30)
	// 	return (42);
	// opp = len_to_hit_grid_vertical(*r, 'w');
	// adj = len_to_hit_grid_horizontal(*r, 's');
	// // printf("opp : %f adj : %f ", opp, adj);
	// hyp_w = opp / (sin(deg_to_rad(angles)));
	// hyp_s = adj / (cos(deg_to_rad(angles)));
	// if (hyp_s < hyp_w)
	// {
	// 	(*r)->cur_rpos_x -= (float)sqrt((hyp_s * hyp_s) - (adj * adj));
	// 	(*r)->cur_rpos_y = (int)(*r)->cur_rpos_y + 1;
	// 	if (c->map[(int)(*r)->cur_rpos_x][(int)(*r)->cur_rpos_y] == '0')
	// 		return (bottom_left_rec(c, r, angles, depth + 1), 1);
	// 	return ((*r)->wall_pixel = fmodf((*r)->cur_rpos_x, 1.00f),
	// 		(*r)->wall = 's', 1);
	// }
	// (*r)->cur_rpos_y += (float)sqrt((hyp_w * hyp_w) - (opp * opp));
	// (*r)->cur_rpos_x = (int)(*r)->cur_rpos_x;
	// if (c->map[(int)(*r)->cur_rpos_x][(int)(*r)->cur_rpos_y] == '0')
	// 	return (bottom_left_rec(c, r, angles, depth + 1), 1);
	// return ((*r)->wall_pixel = fmodf((*r)->cur_rpos_x, 1.00f),
	// 	(*r)->wall = 'w', 1);
	// }
	// t_ray	*bottom_left(t_cube **c, float angles)
	// {
	// t_ray	*raydata;
	// float	a;
	// float	b;

	// raydata = malloc(sizeof(t_cube));
	// raydata->cur_rpos_x = (*c)->pos_x;
	// raydata->cur_rpos_y = (*c)->pos_y;
	// bottom_left_rec((*c), &raydata, angles, 0);
	// a = fabs(raydata->cur_rpos_x - (*c)->pos_x);
	// b = fabs(raydata->cur_rpos_y - (*c)->pos_y);
	// raydata->dist = (float)sqrt(a * a + b * b);
	// return (raydata);
	// }
int	pos_cor(int x)
{
	if (x == 1)
		return (0);
	return (1);
}

int	bottom_right_rec(t_cube	*c, t_ray **r, float angles, int depth)
{
	float	opp;
	float	adj;
	float	hyp_e;
	float	hyp_s;

	if (depth > 30)
		return (42);
	opp = len_to_hit_grid_vertical(*r, (*r)->x_mult);
	adj = len_to_hit_grid_horizontal(*r, (*r)->y_mult);
	// printf("opp : %f adj : %f ", opp, adj);
	hyp_e = opp / (sin(deg_to_rad(angles)));
	hyp_s = adj / (cos(deg_to_rad(angles)));
	if (hyp_s < hyp_e)
	{
		(*r)->cur_rpos_x += sqrt((hyp_s * hyp_s) - (adj * adj)) * (*r)->x_mult;
		(*r)->cur_rpos_y += adj * (*r)->y_mult;
		if (c->map[(int)(*r)->cur_rpos_x - pos_cor((*r)->x_mult)][(int)(*r)->cur_rpos_y - pos_cor((*r)->y_mult)] == '0')
			return (bottom_right_rec(c, r, angles, depth + 1), 1);
		return ((*r)->wall_pixel = fmodf((*r)->cur_rpos_x, 1.00f),
			(*r)->wall = 2 + (*r)->y_mult, 1);
	}
	(*r)->cur_rpos_y += sqrt((hyp_e * hyp_e) - (opp * opp)) * (*r)->y_mult;
	(*r)->cur_rpos_x += opp * (*r)->x_mult;
	if (c->map[(int)(*r)->cur_rpos_x - pos_cor((*r)->x_mult)][(int)(*r)->cur_rpos_y - pos_cor((*r)->y_mult)] == '0')
		return (bottom_right_rec(c, r, angles, depth + 1), 1);
	return ((*r)->wall_pixel = fmodf((*r)->cur_rpos_x, 1.00f),
		(*r)->wall = 1 + (*r)->x_mult, 1);
}

void	init_ray(t_ray *ray, char dir, t_cube **c)
{
	ray->cur_rpos_x = (*c)->pos_x;
	ray->cur_rpos_y = (*c)->pos_y;
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

t_ray	*bottom_right(t_cube **c, float angles, char direction)
{
	t_ray	*raydata;
	float	a;
	float	b;

	raydata = malloc(sizeof(t_cube));

	init_ray(raydata, direction, c);
	bottom_right_rec((*c), &raydata, angles, 0);
	a = fabs(raydata->cur_rpos_x - (*c)->pos_x);
	b = fabs(raydata->cur_rpos_y - (*c)->pos_y);
	raydata->dist = (float)sqrt(a * a + b * b);
	return (raydata);
}

t_ray	*angle_choser(t_cube **c, float angles)
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
	return (bottom_right(c, fmod(angles, 90.00), direction));
}

int	find_color(int a)
{
	if (a == 3)
		return (0xff0000);
	else if (a == 1)
		return (0xffff00);
	else if (a == 0)
		return (0xffffff);
	else if (a == 2)
		return (0x00ffff);
	return (0);
}

void	draw_wall_height_line(t_ray *raydata, t_img **displayed_img, t_cube *p, int x)
{
	int		wall_end;
	float	y;
	int		color;
	int		wall_size;

	wall_size = p->height / raydata->dist;
	color = find_color(raydata->wall);
	wall_end = p->height - (p->height - wall_size) / 2;
	y = (p->height - wall_size) / 2;
	if (y < 0)
		y = 0;
	//temp fix to fix later
	while (y < wall_end && y < p->height)
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
        angles = angle_calc(p->angle, atan((i - p->width/2.0f) / (p->width/2.0f) * tan(45.0f * M_PI/180.0f)) * 180.0f/M_PI);
		if (i == 100)
			printf("prout\n");
        p->raydata[i] = angle_choser(c, angles);
        if (!p->raydata[i])
            printf("angle : %f, width pixel : %d ray error\n", angles, i);
		printf("raw dist :%f, angle :%f, wall color :%c\n", p->raydata[i]->dist, angles, p->raydata[i]->wall);
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