/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:17:40 by fhanuise          #+#    #+#             */
/*   Updated: 2026/05/19 16:38:40 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

int	valid_parse(t_parse *parse)
{
	if (!parse->no_wall)
		return (print_error("ERROR\nMissing NO texture\n"));
	if (!parse->so_wall)
		return (print_error("ERROR\nMissing SO texture\n"));
	if (!parse->we_wall)
		return (print_error("ERROR\nMissing WE texture\n"));
	if (!parse->ea_wall)
		return (print_error("ERROR\nMissing EA texture\n"));
	if (!parse->floor)
		return (print_error("ERROR\nMissing or invalid F color\n"));
	if (!parse->ceiling)
		return (print_error("ERROR\nMissing or invalid C color\n"));
	if (!parse->map)
		return (print_error("ERROR\nMissing map\n"));
	return (0);
}
