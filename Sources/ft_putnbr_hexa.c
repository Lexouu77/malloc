/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 04:43:33 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/28 16:59:10 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		ft_putnbr_hexa(void *ptr, size_t line_feed)
{
	char			str[14];
	int				size;
	unsigned long	nb;

	nb = (unsigned long long)ptr;
	size = 3;
	while (nb /= 16)
		++size;
	if (line_feed)
	{
		str[size] = '\n';
		str[size + 1] = 0;
	}
	else
		str[size] = 0;
	nb = (unsigned long long)ptr;
	while (--size >= 0)
	{
		str[size] = HEXATABLE[nb % 16];
		nb /= 16;
	}
	str[0] = '0';
	str[1] = 'x';
	ft_putstr(str);
}

void		ft_putnbr_hexa_fd(int fd, void *ptr, size_t line_feed)
{
	char			str[14];
	int				size;
	unsigned long	nb;

	nb = (unsigned long long)ptr;
	size = 3;
	while (nb /= 16)
		++size;
	if (line_feed)
	{
		str[size] = '\n';
		str[size + 1] = 0;
	}
	else
		str[size] = 0;
	nb = (unsigned long long)ptr;
	while (--size >= 0)
	{
		str[size] = HEXATABLE[nb % 16];
		nb /= 16;
	}
	str[0] = '0';
	str[1] = 'x';
	ft_putstr_fd(fd, str);
}