/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:49 by radib             #+#    #+#             */
/*   Updated: 2026/04/04 15:02:44 by radib            ###   ########.fr       */
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

int pos_cor(float pos, int mult)
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
		if (c->map[(int)(*r)->cur_rpos_x - pos_cor((*r)->cur_rpos_x, (*r)->x_mult)][(int)(*r)->cur_rpos_y - pos_cor((*r)->cur_rpos_y, (*r)->y_mult)] != '1')
			return (bottom_right_rec(c, r, angles, depth + 1), 1);
		return ((wall_hit(2 + (*r)->y_mult, r, c,  fmodf((*r)->cur_rpos_x, 1.00f)), 1));
	}
	(*r)->cur_rpos_y += sqrt((hyp_e * hyp_e) - (opp * opp)) * (*r)->y_mult;
	(*r)->cur_rpos_x += opp * (*r)->x_mult;
	if (c->map[(int)(*r)->cur_rpos_x - pos_cor((*r)->cur_rpos_x, (*r)->x_mult)][(int)(*r)->cur_rpos_y - pos_cor((*r)->cur_rpos_y, (*r)->y_mult)] != '1')
		return (bottom_right_rec(c, r, angles, depth + 1), 1);
	return (wall_hit(1 + (*r)->x_mult, r, c,  fmodf((*r)->cur_rpos_y, 1.00f)), 1);
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

	raydata = malloc(sizeof(t_ray));
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
	
	if (angles > 0 && angles < 90)
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
	if (!angles) {
		if (direction == 1 || direction == 3)
			angles = 89.999f;
		else
			angles = 0.001f;
	}
	return (bottom_right(c, angles, direction));
}

// int	find_color(int a)
// {
// 	if (a == 3)
// 		return (0xff0000);
// 	else if (a == 1)
// 		return (0xffff00);
// 	else if (a == 0)
// 		return (0xffffff);
// 	else if (a == 2)
// 		return (0x00ffff);
// 	return (0);
// }
int	get_pixel_from_image(t_img *img, int x, int y)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(int *)pixel);
}

void draw_wall_height_line(t_ray *r, t_img **img, t_cube *p, int x)
{
    float   proj_dist;
    int     wall_size;
    int     wall_end;
    float   y;
    int     color;

    proj_dist = (p->width / 2.0f) / tanf(deg_to_rad(p->fov / 2)); // ← same angle as raycast
    wall_size = (int)(proj_dist / r->dist);

	// wall_size = p->height / raydata->dist;
	wall_end = p->height - (p->height - wall_size) / 2;
	y = (p->height - wall_size) / 2;
	if (y < 0)
		y = 0;
	while (y < wall_end && y < p->height)
	{
		color = get_pixel_from_image(r->wall, 128 * r->wall_pixel, (int)((128.00f / wall_size) * (y - (p->height - wall_size) / 2)));
		put_pixel_to_image(*img, x, (int)y, color);
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
        angles = angle_calc(p->angle, atan((i - p->width/2.0f) / (p->width/2.0f) * tan(p->fov / 2 * M_PI/180.0f)) * 180.0f/M_PI);
		if (i == 100)
			printf("prout\n");
        p->raydata[i] = angle_choser(c, angles);
        if (!p->raydata[i])
            printf("angle : %f, width pixel : %d ray error\n", angles, i);
        corrected_dist = p->raydata[i]->dist * cos(deg_to_rad(p->angle -angles));
		printf("raw dist :%f, corrected dist : %f,angle :%f\n", p->raydata[i]->dist, corrected_dist , angles);
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