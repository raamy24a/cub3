/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:21 by radib             #+#    #+#             */
/*   Updated: 2026/04/30 23:19:39 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	find_cub(char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = -1;
	while (str[++i] && i <= len - 4)
	{
		if (str[i] == '.' && str[i + 1] == 'c' && str[i + 2] == 'u'
			&& str[i + 3] == 'b' && str[i + 4] == '\0')
			return (1);
	}
	return (0);
}

void	moving_cam(t_cube **c, int key)
{
	if (key == 65361)
	{
		(*c)->angle -= 15.00;
		if ((*c)->angle < 0)
			(*c)->angle = 360 - ((*c)->angle * -1);
		raycast(c, 0, (*c)->angle);
	}
	else
	{
		(*c)->angle += 15.00;
		(*c)->angle = fmodf((*c)->angle, 360.00);
		raycast(c, 0, (*c)->angle);
	}
}

void	cleanup(t_cube **c)
{
	t_cube	*z;

	z = *c;
	mlx_clear_window(z->m_ptr, z->w_ptr);
	mlx_destroy_window(z->m_ptr, z->w_ptr);
	mlx_destroy_display(z->m_ptr);
	free(*c);
	exit(0);
}

int	handle_key(int key, t_cube *c)
{
	printf("%d\n", key);
	if (key == 65307)
		cleanup(&c);
	if (key == 122 || key == 115 || key == 113 || key == 100)
		moving(&c, key);
	if (key == 65361 || key == 65363)
		moving_cam(&c, key);
	return (0);
}

int	cleanup_exit(t_cube *c)
{
	mlx_clear_window(c->m_ptr, c->w_ptr);
	mlx_destroy_window(c->m_ptr, c->w_ptr);
	mlx_destroy_display(c->m_ptr);
	exit(0);
}

int	main(int ac, char **av)
{
	t_parse	*p;
	t_cube	*c;

	if (ac != 2)
		return (print_error("ERROR\nUsage :\n./cube3D [filename].cub\n"));
	if (!find_cub(av[1]))
		return (print_error("ERROR\nMake sure to use a valid .cub file\n"));
	p = init_parse();
	if (get_file_data(av[1], p))
		return (free_parse(p), 1);
	if (check_map(p->map, p))
		return (free_parse(p), 1);
	c = malloc(sizeof(t_cube) * 1);
	if (init_cube(&c, p->start, p->map, p))
		return (1);
	mlx_hook(c->w_ptr, 17, 1L >> 17, cleanup_exit, c);
	mlx_key_hook(c->w_ptr, handle_key, c);
	int i = 0;
	while (i < 3)
	{
		printf("%d\n", p->floor[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		printf("%d\n", p->ceiling[i]);
		i++;
	}
	printf("ceiling hex: %d\n", createRGB(p->ceiling[0], p->ceiling[1], p->ceiling[2]));
	printf("floor hex: %d\n", createRGB(p->floor[0], p->floor[1], p->floor[2]));
	render_roof(createRGB(p->ceiling[0], p->ceiling[1], p->ceiling[2]), &c);
	render_floor(createRGB(p->floor[0], p->floor[1], p->floor[2]), &c);
	mlx_put_image_to_window(c->m_ptr, c->w_ptr, c->roof_and_ground->img, 0, 0);
	c->displayed_img = init_image(c, c->height, c->width);
	raycast(&c, 0, c->angle);
	mlx_loop(c->m_ptr);
	free_struct(p, c);
	return (0);
}
