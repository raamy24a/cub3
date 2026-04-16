/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhanuise <fhanuise@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:17:40 by fhanuise          #+#    #+#             */
/*   Updated: 2026/04/09 12:55:12 by fhanuise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

int	valid_parse(t_parse *parse)
{
	if (!parse->NO_wall)
		return (print_error("ERROR\nMissing NO texture\n"));
	if (!parse->SO_wall)
		return (print_error("ERROR\nMissing SO texture\n"));
	if (!parse->WE_wall)
		return (print_error("ERROR\nMissing WE texture\n"));
	if (!parse->EA_wall)
		return (print_error("ERROR\nMissing EA texture\n"));
	if (!parse->floor)
		return (print_error("ERROR\nMissing or invalid F color\n"));
	if (!parse->ceiling)
		return (print_error("ERROR\nMissing or invalid C color\n"));
	if (!parse->map)
		return (print_error("ERROR\nMissing map\n"));
	return (0);
}
