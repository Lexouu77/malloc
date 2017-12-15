/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 04:43:33 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/15 20:00:10 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
/*
void		ft_putnbr_hexa(void *nb)
{
	if (nb <= (void*)16)
	{
		if (nb >= (void*)10) 
			ft_putchar((char)(65 + (char)nb - 10));
		else
			ft_putchar((char)((char)nb + 48));
	}
	else
	{
		ft_putnbr_hexa((void*)((size_t)nb / 16));
		ft_putnbr_hexa((void*)((size_t)nb % 16));
	}
}
//TODO change it for the old one. str[13]
static char	get_base_char(char c, char type)
{
	if (c >= 10 && c <= 15)
		return (type < 96) ? (65 + (c - 10)) : (97 + (c - 10));
	return (48 + c);
}*/

void		ft_putnbr_hexa(void *ptr)
{
	char			str[13];
	int				size;
	unsigned long	nb;

	nb = (unsigned long long)ptr;
	size = 1;
	while (nb /= 16)
		++size;
	str[size] = 0;
	str[0] = '0';
	str[1] = 'x';
	nb = (unsigned long long)ptr;
	while (--size >= 0)
	{
		str[size] = HEXATABLE[nb % 16];
		nb /= 16;
	}
	ft_putstr(str);
}
