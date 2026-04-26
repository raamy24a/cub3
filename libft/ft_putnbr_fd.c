/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:04:42 by radib             #+#    #+#             */
/*   Updated: 2026/04/26 10:27:53 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ten_pow(int pow)
{
	int	i;

	i = 1;
	while (pow - 1 > 0)
	{
		i *= 10;
		pow--;
	}
	return (i);
}

static int	nbr_len(int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		i;
	int		x;

	if (n == -2147483648)
		write(fd, "2147483648", 10);
	if (n < 0)
	{
		n *= -1;
		write(fd, "-", 1);
	}
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}	
	i = nbr_len(n);
	while (i > 0)
	{
		x = ten_pow(i);
		c = (n / x) + 48;
		n = (n % x);
		write(fd, &c, 1);
		i--;
	}
}
/*
int	main(void)
{
	ft_putnbr_fd(-2147483648, 0);
}
*/
