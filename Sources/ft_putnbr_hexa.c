/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 04:43:33 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/14 21:47:49 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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