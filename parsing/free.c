/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:38:44 by fhanuise          #+#    #+#             */
/*   Updated: 2026/05/19 17:37:28 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	free_parse(t_parse *parse)
{
	if (parse)
	{
		if (parse->floor)
			free(parse->floor);
		if (parse->ceiling)
			free(parse->ceiling);
		if (parse->map)
			free_tab(parse->map);
		free_img(parse);
		free(parse);
	}
}

void	free_img(t_parse *parse)
{
	if (parse->ea_wall)
		free(parse->ea_wall);
	if (parse->no_wall)
		free(parse->no_wall);
	if (parse->so_wall)
		free(parse->so_wall);
	if (parse->we_wall)
		free(parse->we_wall);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	free_img_to_struct( t_cube *c)
{
	free_parse(c->parsing);
	if (c->wall_e)
	{
		mlx_destroy_image(c->m_ptr, c->wall_e->img);
		free(c->wall_e);
	}
	if (c->wall_n)
	{
		mlx_destroy_image(c->m_ptr, c->wall_n->img);
		free(c->wall_n);
	}
	if (c->wall_w)
	{
		mlx_destroy_image(c->m_ptr, c->wall_w->img);
		free(c->wall_w);
	}
	if (c->wall_s)
	{
		mlx_destroy_image(c->m_ptr, c->wall_s->img);
		free(c->wall_s);
	}
	mlx_destroy_display(c->m_ptr);
	free(c);
}

int	free_struct(t_cube *c)
{
	free_parse(c->parsing);
	mlx_destroy_image(c->m_ptr, c->wall_e->img);
	free(c->wall_e);
	mlx_destroy_image(c->m_ptr, c->wall_n->img);
	free(c->wall_n);
	mlx_destroy_image(c->m_ptr, c->wall_w->img);
	free(c->wall_w);
	mlx_destroy_image(c->m_ptr, c->wall_s->img);
	free(c->wall_s);
	free(c->raydata);
	mlx_destroy_image(c->m_ptr, c->roof_and_ground->img);
	free(c->roof_and_ground);
	mlx_clear_window(c->m_ptr, c->w_ptr);
	mlx_destroy_window(c->m_ptr, c->w_ptr);
	mlx_destroy_display(c->m_ptr);
	free(c->m_ptr);
	free(c);
	exit (0);
}
