/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhanuise <fhanuise@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:38:44 by fhanuise          #+#    #+#             */
/*   Updated: 2026/04/09 11:40:31 by fhanuise         ###   ########.fr       */
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
		free(parse);
	}
}

void	free_img(t_cube **c)
{
	(void)*c;
	return ;
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
