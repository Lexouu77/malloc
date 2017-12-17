/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_type_and_address.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 14:59:06 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/17 17:28:56 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		display_type_and_address(t_block *block, size_t b)
{
	if (!block->pages)
	{
		ft_putstr("LARGE : ");
		ft_putnbr_hexa(block, (b ? 0 : 1));
		return (LARGE);
	}
	else if (block->mapped_size == TINY_N_PAGE * (size_t)getpagesize())
	{
		ft_putstr("TINY  : ");
		ft_putnbr_hexa(block, (b ? 0 : 1));
		return (TINY);
	}
	ft_putstr("SMALL : ");
	ft_putnbr_hexa(block, (b ? 0 : 1));
	return (SMALL);
}
