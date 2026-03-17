/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:49 by radib             #+#    #+#             */
/*   Updated: 2026/03/17 16:28:47 by radib            ###   ########.fr       */
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

void	top_left_rec(t_cube	*c, t_ray **r, float angles)
{
	float	opp;
	float	adj;
	float	hyp_w;
	float	hyp_n;

	opp = len_to_hit_grid_vertical(r);
	adj = len_to_hit_grid_horizontal(r);
	printf("opp : %f adj : %f ", opp, adj);
	hyp_w = opp / (sin(deg_to_rad(angles)));
	hyp_n = adj / (cos(deg_to_rad(angles)));
	if (hyp_n < hyp_w)
	{
		(*r)->cur_rpos_x += (float)sqrt((hyp_n * hyp_n) - (adj * adj));
		(*r)->cur_rpos_y = (int)(*r)->cur_rpos_y + 1;
		if (c->map[(int)(*r)->cur_rpos_x][(int)(*r)->cur_rpos_y] == 0)
			return (top_left_rec(c, r, angles), NULL);
		else
			return ((*r)->wall_pixel = fmodf((*r)->cur_rpos_x, 1.00f), NULL);
	}
	(*r)->cur_rpos_y += (float)sqrt((hyp_w * hyp_w) - (opp * opp));
	(*r)->cur_rpos_x = (int)(*r)->cur_rpos_x;
	if (c->map[(int)(*r)->cur_rpos_x][(int)(*r)->cur_rpos_y] == 0)
		return (top_left_rec(c, r, angles), NULL);
	else
		return ((*r)->wall_pixel = fmodf((*r)->cur_rpos_x, 1.00f), NULL);
}

t_ray	*top_left(t_cube **c, float adj, float opp, float angles)
{
	float			hyp_w;
	float			hyp_n;
	t_ray				*raydata;

	raydata = malloc(sizeof(t_cube));
	// opp = len_to_hit_grid_vertical((*c));
	// adj = len_to_hit_grid_horizontal((*c));
	// printf("opp : %f adj : %f ", opp, adj);
	// hyp_w = opp / (sin(deg_to_rad(angles)));
	// printf("tl%f\n", angles);
	// angles = 90 - angles;
	// printf("tl%f\n", angles);
	// hyp_n = adj / (cos(deg_to_rad(angles)));
	if (hyp_n > hyp_w)
	{
		printf("dist W:%f\n",hyp_w);
		return (raydata->dist = hyp_w, raydata->wall = 'n', raydata);
	}
	printf("dist N:%f\n",hyp_n);
	return (raydata->dist = hyp_n, raydata->wall = 'w', raydata);
}
t_ray	*top_right(t_cube **c, float adj, float opp, float angles)
{
	t_cube		*p;
	float	hyp_e;
	float	hyp_n;
	t_ray		*raydata;

	raydata = malloc(sizeof(t_cube));
	p = *c;
	opp = len_to_hit_grid_horizontal(p);
	adj = len_to_hit_grid_vertical(p);
	hyp_n = adj / (cos(deg_to_rad(angles)));
	// printf("tr%f\n", angles);
	printf("opp : %f adj : %f ", opp, adj);
	// angles = 90 - angles;
	// printf("tr%f\n", angles);
	hyp_e = opp / (sin(deg_to_rad(angles)));
	if (hyp_n > hyp_e)
	{
		printf("dist E:%f\n",hyp_e);
		return (raydata->dist = hyp_e, raydata->wall = 'e', raydata);
	}
	printf("dist N:%f\n",hyp_n);
	return (raydata->dist = hyp_n, raydata->wall = 'n', raydata);
}
t_ray	*bottom_left(t_cube **c, float adj, float opp, float angles)
{
	t_cube		*p;
	float	hyp_w;
	float	hyp_s;
	t_ray		*raydata;

	raydata = malloc(sizeof(t_cube));
	p = *c;
	opp = len_to_hit_grid_horizontal(p);
	adj = len_to_hit_grid_vertical(p);
	printf("opp : %f adj : %f ", opp, adj);
	hyp_s = adj / (cos(deg_to_rad(angles)));
	// printf("bl%f\n", angles);
	// angles = 90 - angles;
	// printf("bl%f\n", angles);
	hyp_w = opp / (sin(deg_to_rad(angles)));
	if (hyp_s > hyp_w)
	{
		printf("dist W:%f\n",hyp_w);
		return (raydata->dist = hyp_w, raydata->wall = 'w', raydata);
	}
	printf("dist S:%f\n",hyp_s);
	return (raydata->dist = hyp_s, raydata->wall = 's', raydata);
}
t_ray	*bottom_right(t_cube **c, float adj, float opp, float angles)
{
	t_cube		*p;
	float	hyp_e;
	float	hyp_s;
	t_ray		*raydata;

	raydata = malloc(sizeof(t_cube));
	p = *c;
	// printf("br%f\n", angles);
	opp = len_to_hit_grid_vertical(p);
	adj = len_to_hit_grid_horizontal(p);
	printf("opp : %f adj : %f ", opp, adj);
	hyp_e = 1 / (sin(deg_to_rad(angles)) / opp);
	// printf("br%f\n", angles);
	// angles = 90 - angles;
	// printf("br%f\n", angles);
	hyp_s = 1 / (cos(deg_to_rad(angles)) / adj);
	if (hyp_s > hyp_e)
	{
		printf("dist E:%f\n",hyp_e);
		return (raydata->dist = hyp_e, raydata->wall = 's', raydata);
	}
	printf("dist S:%f\n",hyp_s);
	return (raydata->dist = hyp_s, raydata->wall = 'e', raydata);
}

t_ray	*angle_choser(t_cube **c, float angles)
{
	// printf("%f\n", angles);
	if (angles >= 0 && angles < 90)
		return (top_right(c, 0, 0, angles));
	if (angles >= 90 && angles < 180)
		return (bottom_right(c, 0, 0, fmod(angles, 90.00)));
	if (angles >= 180 && angles < 270)
		return (bottom_left(c, 0, 0, fmod(angles, 90.00)));
	if (angles >= 270 && angles < 360)
		return (top_left(c, 0, 0, fmod(angles, 90.00)));
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

t_img	*duplicate_image(t_img *to_dup, t_img *dest)
{
	dest = to_dup;
	return (dest);
}

int	wall_change_pixel(t_cube **c, int	i)
{
	t_cube		*p;
	int		j;

	p = *c;
	j = i;
	while(i + 1 < p->width && p->raydata[j]->wall == p->raydata[i]->wall)
	{
		i++;
	}
	return (i);
}

void	un_fish_eye(t_cube **c, int left_side_pixel, int right_side_pixel)
{
	int 	i;
	t_cube		*p;
	float	temp;

	p = *c;
	i = 0;
	while (i < p->width)
	{
		left_side_pixel = i;
		right_side_pixel = wall_change_pixel(c, i);
		temp = p->raydata[left_side_pixel]->dist + p->raydata[right_side_pixel]->dist;
		temp = (temp / 2) / (right_side_pixel - left_side_pixel);
		while (i <= right_side_pixel)
		{
			p->raydata[i]->dist = p->raydata[left_side_pixel]->dist + temp;
			i++;
		}
	}
}

// void	raycast(t_c **c, int i, float angles)
// {
// t_c		*p;

// p = *c;
// while (i < p->width)
// {
// 	angles = angle_calc(p->angle, 90.00 / (float)p->width * i);
// 	// printf("angle : %f\n", angles); //anglepring
// 	p->raydata[i] = angle_choser(c, angles);
// 	if (!p->raydata[i])
// 		printf("angle : %f, width pixel : %d ray error\n", angles, i);
// 	i++;
// }
// i = 0;
// render_roof(10000 * 0 + 100 * 20 + 20, c);
// render_floor(300 * 10000 + 100 * 100 + 50, c);
// p->displayed_img = p->roof_and_ground;
// un_fish_eye(c, 0, 0);
// while (i < p->width)
// {
// 	// printf("%f\n", p->raydata[i]->dist); //distprint 
// 	draw_wall_height_line(p->raydata[i], &p->displayed_img, p, i);
// 	i++;
// }
// mlx_clear_window(p->m_ptr, p->w_ptr);
// mlx_put_image_to_window(p->m_ptr, p->w_ptr, p->displayed_img->img, 0, 0);
// }
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