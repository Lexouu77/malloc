/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 21:01:52 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/28 16:27:54 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		ft_putnbr(size_t nb)
{
	if (nb <= 9)
		ft_putchar((char)(nb + 48));
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
}

void		ft_putnbr_fd(int fd, size_t nb)
{
	if (nb <= 9)
		ft_putchar_fd(fd, (char)(nb + 48));
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
}
