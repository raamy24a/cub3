/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhanuise <fhanuise@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:19:38 by fhanuise          #+#    #+#             */
/*   Updated: 2026/04/08 14:21:02 by fhanuise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

t_img	*init_image(t_cube *p, int height, int width)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	img->img = mlx_new_image(p->m_ptr, height, width);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (img);
}

t_img	*init_image_xpm(t_cube **c, char *path_to_image)
{
	t_img	*img;
	int		height;
	int		width;
	t_cube		*p;

	p = *c;
	//a fix avec fonction mlx pour avoir res de texture
	height = 128;
	width = 128;
	img = malloc(sizeof(t_img));
	img->img = mlx_xpm_file_to_image(p->m_ptr, path_to_image, &width, &height);
	if (!img->img)
	{
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (img);
}

int	put_wall_images_to_struct(t_cube **c, t_parse *parse)
{
	t_cube	*p;

	p = (*c);
	p->wall_e = init_image_xpm(c, parse->EA_wall);
	if (!p->wall_e)
		return (free_parse(parse), free_img(c), 1);
	p->wall_s = init_image_xpm(c, parse->SO_wall);
	if (!p->wall_s)
		return (free_parse(parse), free_img(c), 1);
	p->wall_w = init_image_xpm(c, parse->WE_wall);
	if (!p->wall_w)
		return (free_parse(parse), free_img(c), 1);
	p->wall_n = init_image_xpm(c, parse->NO_wall);
	if (!p->wall_n)
		return (free_parse(parse), free_img(c), 1);
	return (0);
}

t_parse	*init_parse(void)
{
	t_parse	*p;

	p = malloc(sizeof(t_parse) * 1);
	p->ceiling = NULL;
	p->floor = NULL;
	p->map = NULL;
	p->player = 0;
	p->NO_wall = NULL;
	p->EA_wall = NULL;
	p->SO_wall = NULL;
	p->WE_wall = NULL;
	return (p);
}

int	init_cube(t_cube **c, char angle, char **map, t_parse *parse)
{
	t_cube	*p;

	p = (*c);
	p->width = 1080;
	p->height = 1080;
	(void)angle;
	// p->angle = angle_calculator(angle);
	p->angle = 0;
	p->fps = 60;
	p->m_ptr = mlx_init();
	if (put_wall_images_to_struct(c, parse))
		return (print_error("Error:\nUnable to load texture\n"));
	p->fov = 66.00f;
	p->pos_x = 2.5;
	p->pos_y = 3.5;
	p->w_ptr = mlx_new_window(p->m_ptr, p->width, p->height, "Cube");
	p->raydata = malloc(sizeof(t_ray *) * p->width);
	p->map = map;
	return (0);
}
